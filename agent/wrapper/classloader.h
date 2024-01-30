#pragma once
#include <jni.h>
#include <jvmti.h>
#include <string>
class classloader {
private:
    JNIEnv* env;
    jvmtiEnv* jvmti;
    jobject jclass_loader;

public:
    classloader(JNIEnv* env, jvmtiEnv* jvmti) {
        this->env = env;
        this->jvmti = jvmti;
        this->jclass_loader = nullptr;
        jint threadsCount;
        jthread* threads;
        jvmti->GetAllThreads(&threadsCount, &threads);
        jobject class_loader = nullptr;
        for (int i = 0; i < threadsCount; i++) {
            jthread thread = threads[i];
            jvmtiThreadInfo info;
            jvmti->GetThreadInfo(thread, &info);

            if (std::string(info.name).compare("Client thread") == 0) {
                jclass_loader = info.context_class_loader;
            }
        }
    }

    void add_url(jobject url);
    jclass load_class(const char* name);
    jmethodID get_method_id(jclass klass, const char* name, const char* sig);
};