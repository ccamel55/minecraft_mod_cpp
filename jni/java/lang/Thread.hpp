#pragma once

#include <jni.h>
#include <cassert>

namespace java::lang
{
    inline jclass thread_class = nullptr;

    namespace thread
    {
        inline jmethodID get_all_stack_traces = nullptr;
        inline jmethodID get_context_class_loader_id = nullptr;
    }

    inline void init_thread(JNIEnv* jni)
    {
        thread_class = jni->FindClass("java/lang/Thread");
        assert(thread_class);

        thread::get_all_stack_traces = jni->GetStaticMethodID(thread_class, "getAllStackTraces", "()Ljava/util/Map;");
        assert(thread::get_all_stack_traces);

        thread::get_context_class_loader_id = jni->GetMethodID(thread_class, "getContextClassLoader", "()Ljava/lang/ClassLoader;");
        assert(thread::get_context_class_loader_id);
    }

    inline void destroy_thread(JNIEnv* jni)
    {
        jni->DeleteLocalRef(thread_class);
        thread_class = nullptr;

        thread::get_all_stack_traces = nullptr;
        thread::get_context_class_loader_id = nullptr;
    }
}