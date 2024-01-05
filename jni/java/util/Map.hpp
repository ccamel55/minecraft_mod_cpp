#pragma once

#include <jni.h>
#include <cassert>

namespace java::util
{
    inline jclass map_class = nullptr;

    namespace map
    {
        inline jmethodID key_set_id = nullptr;
    }

    inline void init_map(JNIEnv* jni)
    {
        map_class = jni->FindClass("java/util/Map");
        assert(map_class);

        map::key_set_id = jni->GetMethodID(map_class, "keySet", "()Ljava/util/Set;");
        assert(map::key_set_id);
    }

    inline void destroy_map(JNIEnv* jni)
    {
        jni->DeleteLocalRef(map_class);
        map_class = nullptr;

        map::key_set_id = nullptr;
    }
}