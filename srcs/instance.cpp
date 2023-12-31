#include <instance.hpp>
#include <menu.hpp>
#include <utils.hpp>
#include <minecraft_sdk.hpp>

#include <cassert>
#include <java.hpp>
#include <thread>

#include <Windows.h>
#include <windowsx.h>
#include <MinHook.h>

#include <glad/glad.hpp>

#include <core_sdk/logger.hpp>

namespace
{
    HWND window_handle = nullptr;
    WNDPROC original_wndproc = nullptr;

    LRESULT wndproc_hook(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
    {
        lib::input::input_t input = {};

        switch (msg)
        {
        case WM_MOUSEMOVE:
            {
                input.type = lib::input::mouse;
                input.key = lib::input::key_button::mouse_move;

                input.state = lib::point2Di{
                    static_cast<int>(GET_X_LPARAM(lParam)),
                    static_cast<int>(GET_Y_LPARAM(lParam))};

                instance::get().input_handler->add_input(input);
                break;
            }
        case WM_MOUSEWHEEL:
            {
                input.type = lib::input::mouse;
                input.key = lib::input::key_button::mouse_scroll;

                input.state = lib::point2Di{
                    0,
                    GET_WHEEL_DELTA_WPARAM(wParam) / WHEEL_DELTA};

                instance::get().input_handler->add_input(input);
                break;
            }
        case WM_KEYDOWN:
        case WM_SYSKEYDOWN:
            {
                input.type = lib::input::keyboard;
                input.key = utils::win32_to_input_key(static_cast<UINT>(wParam));
                input.state = true;

                instance::get().input_handler->add_input(input);
                break;
            }
        case WM_KEYUP:
        case WM_SYSKEYUP:
            {
                input.type = lib::input::keyboard;
                input.key = utils::win32_to_input_key(static_cast<UINT>(wParam));
                input.state = false;

                instance::get().input_handler->add_input(input);
                break;
            }
        case WM_LBUTTONDOWN:
        case WM_LBUTTONUP:
            {
                input.type = lib::input::mouse;
                input.key = lib::input::key_button::mouseleft;

                input.state = msg == WM_LBUTTONDOWN;
                instance::get().input_handler->add_input(input);
                break;
            }
        case WM_RBUTTONDOWN:
        case WM_RBUTTONUP:
            {
                input.type = lib::input::mouse;
                input.key = lib::input::key_button::mouseright;

                input.state = msg == WM_RBUTTONDOWN;
                instance::get().input_handler->add_input(input);
                break;
            }
        case WM_MBUTTONDOWN:
        case WM_MBUTTONUP:
            {
                input.type = lib::input::mouse;
                input.key = lib::input::key_button::mousemiddle;

                input.state = msg == WM_MBUTTONDOWN;
                instance::get().input_handler->add_input(input);
                break;
            }
        default:
            break;
        }

        if (menu::get().is_open())
        {
            // enable cursor, if we are in game the cursor is disable dy default
            if (msg == WM_SETCURSOR && LOWORD(lParam) == HTCLIENT)
            {
                SetCursor(LoadCursor(nullptr, IDC_ARROW));
            }

            return true;
        }

        return CallWindowProcA(original_wndproc, hWnd, msg, wParam, lParam);
    }

    using swap_buffers_fn = bool(__stdcall*)(HDC hDc);
    swap_buffers_fn original_swap_buffers = nullptr;

    HGLRC new_context = nullptr;

    GLint viewport[4] = {};
    GLint last_viewport[4] = {};

    auto last_frame_time = std::chrono::high_resolution_clock::now();

    bool __stdcall swap_buffers_hook(HDC hDc)
    {
        const auto original_context = wglGetCurrentContext();
        const auto& render = instance::get().renderer;

        // get window handle
        if (const auto current_window_handle = WindowFromDC(hDc);
            current_window_handle != window_handle) [[unlikely]]
        {
            lib_log_d("rehooking wndproc");

            window_handle = current_window_handle;
            assert(window_handle);

            original_wndproc = reinterpret_cast<WNDPROC>(
                SetWindowLongPtrW(window_handle, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(wndproc_hook)));
        }

        // update render context if we fullscreen/alt tab
        if (new_context == nullptr) [[unlikely]]
        {
            lib_log_d("creating new render context");

            // twe need to make a new contex to render stuff too
            new_context = wglCreateContext(hDc);
            wglMakeCurrent(hDc, new_context);
            {
                render->bind_api(nullptr);
                render->build_texture();
            }
            wglMakeCurrent(hDc, original_context);
            return original_swap_buffers(hDc);
        }

        // we need to get our viewport before binding our new context as we want to get the games viewport
        glGetIntegerv(GL_VIEWPORT, viewport);

        // rebind our context to draw our stuff onto it
        wglMakeCurrent(hDc, new_context);
        {
            if (viewport[2] != last_viewport[2] || viewport[3] != last_viewport[3]) [[unlikely]]
            {
                // update screen size
                lib_log_d("screen size changed to: {} x {}", viewport[2], viewport[3]);

                last_viewport[2] = viewport[2];
                last_viewport[3] = viewport[3];

                instance::get().renderer->set_window_size({last_viewport[2], last_viewport[3]});
                menu::update_screen_size({last_viewport[2], last_viewport[3]});
            }

            render->draw_frame();
            render->set_frame_time(
                static_cast<float>(std::chrono::duration_cast<std::chrono::milliseconds>(
                    std::chrono::high_resolution_clock::now() - last_frame_time).count()));

            last_frame_time = std::chrono::high_resolution_clock::now();
        }
        wglMakeCurrent(hDc, original_context);
        return original_swap_buffers(hDc);
    }
}

void instance::attatch()
{
    input_handler = std::make_shared<lib::input::input_handler>();
    renderer = std::make_shared<lib::rendering::renderer>();

    auto& jvm = instance::get().jvm;
    auto& jni_env = instance::get().jni_env;

    assert(JNI_GetCreatedJavaVMs(&jvm, 1, nullptr) == JNI_OK);
    assert(jvm->AttachCurrentThread(reinterpret_cast<void**>(&jni_env), nullptr) == JNI_OK);

    lib_log_d("found jvm: {}", reinterpret_cast<uintptr_t>(jvm));
    lib_log_d("found jni instance: {}", reinterpret_cast<uintptr_t>(jni_env));

    java::init(jni_env);
    sdk::init_sdk(jni_env);

    menu::get().init();

    attatch_native_hooks();
    attatch_jni_hooks();
}

void instance::remove()
{
    sdk::destroy_sdk(jni_env);
    java::destroy(jni_env);
    menu::get().destroy();

    remove_native_hooks();
    remove_jni_hooks();

    renderer->unbind_api();
    new_context = nullptr;

    jvm = nullptr;
    jni_env = nullptr;

    input_handler.reset();
    renderer.reset();
}

// native hooks are used to hook non JVM functions (ie: any function that is exported by a C api or byte scanned)
void instance::attatch_native_hooks()
{
    lib_log_d("attatching native hooks");

    assert(MH_Initialize() == MH_OK);

    // we should be able to get swapBuffers from the opengl32.dll, i think this does crash sometimes when the
    // render context changes (or what ever they call it in opengl)
    {
        const auto swap_buffers_ptr = reinterpret_cast<void*>(
            GetProcAddress(GetModuleHandle("Gdi32.dll"), "SwapBuffers"));

        assert(swap_buffers_ptr != nullptr);

        assert(MH_CreateHook(
            swap_buffers_ptr,
            reinterpret_cast<LPVOID*>(&swap_buffers_hook),
            reinterpret_cast<LPVOID*>(&original_swap_buffers)) == MH_OK);
    }

    assert(MH_EnableHook(nullptr) == MH_OK);
}

// JNI hooks rely on detouring functions in the JVM rather than raw virtual memory. This is the hard and annoying part
// since the JVM doens't guarentee what calltype a function is (native, interpreted, or compiled). I havn't tested
// much with the new jnihook library but from the onset it seems much more stable than what I was doing before.
void instance::attatch_jni_hooks()
{
    lib_log_d("attatching jni hooks");

    JNIHook_Init(instance::get().jvm);
}

void instance::remove_native_hooks()
{
    lib_log_d("removing native hooks");

    SetWindowLongPtrW(window_handle, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(original_wndproc));

    MH_DisableHook(nullptr);
    MH_RemoveHook(nullptr);
}

void instance::remove_jni_hooks()
{
    lib_log_d("removing jni hooks");

    assert(instance::get().jvm->DetachCurrentThread() == JNI_OK);

    JNIHook_Shutdown();
}