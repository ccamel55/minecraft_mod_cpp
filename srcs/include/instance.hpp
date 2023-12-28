#pragma once

#include <memory>
#include <jnihook.h>

#include <core_sdk/singleton.hpp>
#include <lib_input/lib_input.hpp>
#include <lib_rendering/lib_rendering.hpp>

class instance: public lib::singleton<instance>
{
public:
    void attatch();
    void remove();

private:
    static void attatch_native_hooks();
    static void attatch_jni_hooks();

    static void remove_native_hooks();
    static void remove_jni_hooks();

public:
    std::shared_ptr<lib::input::input_handler> input_handler = nullptr;
    std::shared_ptr<lib::rendering::renderer> renderer = nullptr;

    JavaVM* jvm = nullptr;
    JNIEnv* jni_env = nullptr;

};
