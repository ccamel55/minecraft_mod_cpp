#pragma once

#include <jni.h>
#include <cassert>

namespace java::lang
{
    inline jclass class_loader_class = nullptr;

    namespace class_loader
    {
        inline jmethodID find_class_id = nullptr;
    }

    inline void init_class_loader(JNIEnv* jni)
    {
        class_loader_class = jni->FindClass("java/lang/ClassLoader");
        assert(class_loader_class);

        class_loader::find_class_id = jni->GetMethodID(class_loader_class, "findClass", "(Ljava/lang/String;)Ljava/lang/Class;");
        assert(class_loader::find_class_id);
    }

    inline void destroy_class_loader(JNIEnv* jni)
    {
        jni->DeleteLocalRef(class_loader_class);
        class_loader_class = nullptr;

        class_loader::find_class_id = nullptr;
    }
}