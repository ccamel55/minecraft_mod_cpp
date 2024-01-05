#pragma once

#include <java/lang/ClassLoader.hpp>
#include <java/lang/Thread.hpp>

#include <java/util/Map.hpp>
#include <java/util/Set.hpp>

namespace java
{
    inline void init(JNIEnv* jni)
    {
        lang::init_class_loader(jni);
        lang::init_thread(jni);

        util::init_map(jni);
        util::init_set(jni);
    }

    inline void destroy(JNIEnv* jni)
    {
        lang::destroy_class_loader(jni);
        lang::destroy_thread(jni);

        util::destroy_map(jni);
        util::destroy_set(jni);
    }
}