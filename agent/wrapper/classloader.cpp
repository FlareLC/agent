#include "classloader.h"

void classloader::add_url(jobject url)
{
	jmethodID add_url = env->GetMethodID(env->GetObjectClass(jclass_loader), "addURL", "(Ljava/net/URL;)V");
	env->CallVoidMethod(jclass_loader, add_url, url);
}

jclass classloader::load_class(const char* name) {
	jstring jname = env->NewStringUTF(name);
	jmethodID load_class = env->GetMethodID(env->GetObjectClass(jclass_loader), "loadClass", "(Ljava/lang/String;)Ljava/lang/Class;");
	return (jclass)env->CallObjectMethod(jclass_loader, load_class, jname);
}

jmethodID classloader::get_method_id(jclass klass, const char* name, const char* sig)
{
	return env->GetMethodID(klass, name, sig);
}
