#include "url.h"

jobject url::to_file()
{
    jclass klass = env->FindClass("java/io/File");
    jstring str = env->NewStringUTF(this->path);
    jmethodID constructor = env->GetMethodID(klass, "<init>", "(Ljava/lang/String;)V");
    return env->NewObject(klass, constructor, str);
}

jobject url::to_uri()
{
    jclass klass = env->FindClass("java/io/File");
    jmethodID to_uri = env->GetMethodID(klass, "toURI", "()Ljava/net/URI;");
    return env->CallObjectMethod(this->to_file(), to_uri);
}

jobject url::to_url()
{
    jclass klass = env->FindClass("java/net/URI");
    jmethodID to_url = env->GetMethodID(klass, "toURL", "()Ljava/net/URL;");
    return env->CallObjectMethod(this->to_uri(), to_url);
}
