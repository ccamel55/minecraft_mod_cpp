#include <minecraft_sdk.hpp>
#include <java.hpp>

#include <cassert>

#include <core_sdk/logger.hpp>

using namespace sdk;

namespace
{
    bool init = false;

    jobject class_loader_object = nullptr;

    // this function should work with any version of the game since it searches all threads for the correct class loader
    void find_class_loader(JNIEnv* jni)
    {
        const auto get_all_stack_traces =
            jni->CallStaticObjectMethod(java::lang::thread_class, java::lang::thread::get_all_stack_traces);

        const auto thread_set =
            jni->CallObjectMethod(get_all_stack_traces, java::util::map::key_set_id);

        const auto thread_array =
            reinterpret_cast<jobjectArray>(jni->CallObjectMethod(thread_set, java::util::set::to_array_id));

        // for each running thread, try load a known class, if successful then that is our 'main' thread
        const auto num_threads = jni->GetArrayLength(thread_array);

        for (size_t i = 0; i < num_threads; i++)
        {
            const auto thread_array_val = jni->GetObjectArrayElement(thread_array, static_cast<int>(i));

            if (const auto class_loader = jni->CallObjectMethod(thread_array_val,
                java::lang::thread::get_context_class_loader_id);
                class_loader)
            {
                const auto find_class_string = jni->NewStringUTF("net/minecraft/client/Minecraft");
                const auto minecraft_class =
                    reinterpret_cast<jclass>(jni->CallObjectMethod(class_loader,
                    java::lang::class_loader::find_class_id, find_class_string));

                jni->DeleteLocalRef(find_class_string);

                if (minecraft_class)
                {
                    lib_log_d("found class loader, thread: {}", i);
                    class_loader_object = class_loader;

                    jni->DeleteLocalRef(minecraft_class);
                    break;
                }
            }

            jni->DeleteLocalRef(thread_array_val);

            if (i == num_threads - 1)
            {
                lib_log_e("could not find class loader, {} threads searched", num_threads);
                assert(false);
            }
        }

        jni->DeleteLocalRef(get_all_stack_traces);
        jni->DeleteLocalRef(thread_set);
        jni->DeleteLocalRef(thread_array);
    }
}

jclass sdk::find_class(JNIEnv* jni, const char* class_name)
{
    const auto find_class_string = jni->NewStringUTF(class_name);
    const auto found_class =
        jni->CallObjectMethod(class_loader_object, java::lang::class_loader::find_class_id, find_class_string);

    jni->DeleteLocalRef(find_class_string);

    if (!found_class)
    {
        lib_log_e("could not load class: {}", class_name);
        assert(false);
    }

    return reinterpret_cast<jclass>(found_class);
}

void sdk::init_sdk(JNIEnv* jni)
{
    assert(!init);
    init = true;

    // find the game's class loader
    find_class_loader(jni);

    const auto minecraft_class = find_class(jni, "net/minecraft/client/Minecraft");

    // retrieve the game instance
    {
        const auto instance =
            jni->GetStaticFieldID(minecraft_class, "field_71432_P", "Lnet/minecraft/client/Minecraft;");

        minecraft = jni->GetStaticObjectField(minecraft_class, instance);

        lib_log_d("found minecraft instance: {}", reinterpret_cast<uintptr_t>(minecraft));
        assert(minecraft);
    }

    jni->DeleteLocalRef(minecraft_class);
}

void sdk::destroy_sdk(JNIEnv* jni)
{
    assert(init);
    init = false;

    // we need to find minecraft's main thread with it's class loader
    jni->DeleteLocalRef(class_loader_object);
    jni->DeleteLocalRef(minecraft);
}