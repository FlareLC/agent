#include <jni.h>
#pragma once
class url
{
private:
	const char* path;
	JNIEnv* env;
public:
	url(const char* mpath, JNIEnv* menv) : path(mpath), env(menv) {};
	jobject to_file();
	jobject to_uri();
	jobject to_url();
};

