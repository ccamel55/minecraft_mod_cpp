#pragma once

#include <jni.h>
#include <cassert>

namespace java::util
{
    inline jclass set_class = nullptr;

    namespace set
    {
        inline jmethodID to_array_id = nullptr;
    }

    inline void init_set(JNIEnv* jni)
    {
        set_class = jni->FindClass("java/util/Set");
        assert(set_class);

        set::to_array_id = jni->GetMethodID(set_class, "toArray", "()[Ljava/lang/Object;");
        assert(set::to_array_id);
    }

    inline void destroy_set(JNIEnv* jni)
    {
        jni->DeleteLocalRef(set_class);
        set_class = nullptr;

        set::to_array_id = nullptr;
    }
}