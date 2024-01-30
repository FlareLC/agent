#include <Windows.h>
#include <thread>
#include <jni.h>
#include <jvmti.h>
#include "wrapper/classloader.h"
#include "wrapper/url.h"
#include <filesystem>

namespace fs = std::filesystem;

JNIEnv* env;
jvmtiEnv* jvmti;
JavaVM* vm;

bool init() {
	if (JNI_GetCreatedJavaVMs(&vm, 1, nullptr) != JNI_OK)
		return false;
	if(vm->AttachCurrentThread((void**)&env, nullptr) != JNI_OK)
		return false;
	if (vm->GetEnv((void**)&jvmti, JVMTI_VERSION_1_2) != JNI_OK)
		return false;
	return true;
}



void main() {
	if(!init())
		return;

	char* appdata;
	size_t len;
	_dupenv_s(&appdata, &len, "APPDATA");
	std::string path = std::string(appdata) + "\\flarelc\\";

	classloader loader = classloader(env, jvmti);
	jobject jurl = url((path + "modloader.jar").c_str(), env).to_url();
	loader.add_url(jurl);
	jclass clazz = loader.load_class("dev.flarelc.modloader.FlareLoader");
	jmethodID method = env->GetStaticMethodID(clazz, "run", "()V");
	env->CallStaticVoidMethod(clazz, method);


	for (const auto& entry : fs::directory_iterator(path + "remapped")) {
		jobject jurl = url(entry.path().string().c_str(), env).to_url();
		loader.add_url(jurl);
	}
	method = env->GetStaticMethodID(clazz, "end", "()V");
	env->CallStaticVoidMethod(clazz, method);
}

BOOL APIENTRY DllMain(HMODULE mod, DWORD reason, LPVOID reserved)
{
	if (reason == DLL_PROCESS_ATTACH) {
		std::thread{main}.detach();
	}
	
	return TRUE;
}
