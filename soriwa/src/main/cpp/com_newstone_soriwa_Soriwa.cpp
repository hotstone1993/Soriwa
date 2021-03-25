/* DO NOT EDIT THIS FILE - it is machine generated */
#include <jni.h>
#include <string>
/* Header for class com_newstone_soriwa_Soriwa */
#include "include/com_newstone_soriwa_Soriwa.h"
#include "include/Soriwa.h"
#include "common_header.h"

const char* const INSTANCE = "instance";

#ifdef __cplusplus
extern "C" {
#endif


#define GET_MEMBER(env, obj, member_cls, type1, type2, type3, member_name) \
    jfieldID member_name##_id1 = env->GetFieldID(member_cls, #member_name, type3);  \
    type1 member_name = env->Get##type2##Field(obj, member_name##_id1);

#define GET_CONFIGURATION(env, configObj, configCls) \
    GET_MEMBER(env, configObj, configCls, jint, Int, "I", playMode) \
    GET_MEMBER(env, configObj, configCls, jint, Int, "I", sharingMode) \
    GET_MEMBER(env, configObj, configCls, jint, Int, "I", frameSize) \
    Configuration temp; \
    temp.sharingMode = playMode; \
    temp.playMode = sharingMode; \
    temp.frameSize = frameSize;

Soriwa* getInstance(JNIEnv* env, const jobject& obj) {
    jclass cls = env->GetObjectClass(obj);
    jfieldID id = env->GetFieldID(cls, INSTANCE, "J");
    jlong instancePointer = env->GetLongField(obj, id);
    return reinterpret_cast<Soriwa*>(instancePointer);
}

void renderer(float* input, float* output) {

}

JNIEXPORT void JNICALL Java_com_newstone_soriwa_Soriwa_init(JNIEnv *env, jobject obj) {
    Soriwa* newInstance = new Soriwa();
    newInstance->init();

    jclass cls = env->GetObjectClass(obj);
    jfieldID id = env->GetFieldID(cls, INSTANCE, "J");
    env->SetLongField(obj, id, reinterpret_cast<jlong>(newInstance));
}

JNIEXPORT void JNICALL Java_com_newstone_soriwa_Soriwa_deinit(JNIEnv *env, jobject obj) {
    Soriwa* instance = getInstance(env, obj);
    instance->deinit();
    delete instance;

    jclass cls = env->GetObjectClass(obj);
    jfieldID id = env->GetFieldID(cls, INSTANCE, "J");
    env->SetLongField(obj, id, 0);
}

JNIEXPORT jint JNICALL Java_com_newstone_soriwa_Soriwa_addAudio(JNIEnv *env, jobject obj, jobject config, jstring filePath) {
    Soriwa* instance = getInstance(env, obj);
    jclass cls = env->GetObjectClass(config);
    std::string path = env->GetStringUTFChars(filePath, NULL);
    GET_CONFIGURATION(env, config, cls)
    int id = instance->addAudio(temp, path);
    instance->setRenderer(id, renderer);

    return id;
}

JNIEXPORT jint JNICALL Java_com_newstone_soriwa_Soriwa_deleteAudioById(JNIEnv *env, jobject obj, jint id) {
    int result = 0;
    Soriwa* instance = getInstance(env, obj);
    result = instance->deleteAudioById(id);
    return result;
}

JNIEXPORT jint JNICALL Java_com_newstone_soriwa_Soriwa_play(JNIEnv *env, jobject obj, jint id) {
    int result = 0;
    Soriwa* instance = getInstance(env, obj);
    result = instance->play(id);
    return result;
}

JNIEXPORT jint JNICALL Java_com_newstone_soriwa_Soriwa_stop(JNIEnv *env, jobject obj, jint id) {
    int result = 0;
    Soriwa* instance = getInstance(env, obj);
    result = instance->stop(id);
    return result;
}
#ifdef __cplusplus
}
#endif