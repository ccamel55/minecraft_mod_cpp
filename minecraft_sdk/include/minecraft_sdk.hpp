#pragma once

#include <jni.h>

namespace sdk
{
    inline jobject minecraft = nullptr;

    //! Find a game class
    jclass find_class(JNIEnv* jni, const char* class_name);

    void init_sdk(JNIEnv* jni);
    void destroy_sdk(JNIEnv* jni);
}
