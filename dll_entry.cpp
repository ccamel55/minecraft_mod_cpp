#include <iostream>
#include <cassert>
#include <thread>
#include <atomic>

#include <Windows.h>
#include <instance.hpp>

#include <core_sdk/logger.hpp>

namespace
{
    void mod_thread(void* module_handle)
    {
        std::atomic<bool> should_exit = false;

        const auto attatch = [&]()
        {
            // create a console and map out and err to it
            {
                assert(AllocConsole() == true);

                freopen_s(reinterpret_cast<_iobuf**>(stdout), "CONOUT$", "w", stdout);
                freopen_s(reinterpret_cast<_iobuf**>(stderr), "CONOUT$", "w", stderr);

                SetConsoleTitleA("Debug Console");
            }

            char process_name[512] = {};
            GetModuleFileName(nullptr, process_name, 256);

            lib_log_d("injected into: {}", process_name);

            instance::get().attatch();
        };

        const auto detatch = [&]()
        {
            instance::get().remove();

            // unmap out and err
            {
                fclose(stdout);
                fclose(stderr);

                FreeConsole();
            }
        };

        attatch();

        // register panic/deatch key
        instance::get().input_handler->register_callback(
            lib::input::keyboard, [&](const lib::input::input_handler& input)
        {
            if (input.get_key_state(lib::input::key_button::delete_key).has(lib::input::pressed))
            {
                should_exit = true;
            }
        });

        while (!should_exit)
        {
            // maybe this is too long?
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }

        detatch();

        FreeLibraryAndExitThread(static_cast<HMODULE>(module_handle), EXIT_SUCCESS);
    }
}

BOOL APIENTRY DllMain(HMODULE module_handle, DWORD call_reason, LPVOID reserved)
{
    (void)reserved;

    if (call_reason == DLL_PROCESS_ATTACH)
    {
        DisableThreadLibraryCalls(module_handle);
        std::thread(mod_thread, module_handle).detach();
    }

    return TRUE;
}