/* DO NOT EDIT THIS FILE - it is machine generated */
#include <jni.h>
/* Header for class com_newstone_soriwa_Soriwa */

#ifndef _Included_com_newstone_soriwa_Soriwa
#define _Included_com_newstone_soriwa_Soriwa
#ifdef __cplusplus
extern "C" {
#endif
/*
 * Class:     com_newstone_soriwa_Soriwa
 * Method:    init
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_com_newstone_soriwa_Soriwa_init
  (JNIEnv *, jobject);

/*
 * Class:     com_newstone_soriwa_Soriwa
 * Method:    deinit
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_com_newstone_soriwa_Soriwa_deinit
  (JNIEnv *, jobject);

/*
 * Class:     com_newstone_soriwa_Soriwa
 * Method:    addAudio
 * Signature: (Lcom/newstone/soriwa/Configuration;Ljava/lang/String;)I
 */
JNIEXPORT jint JNICALL Java_com_newstone_soriwa_Soriwa_addAudio
  (JNIEnv *, jobject, jobject, jstring);

/*
 * Class:     com_newstone_soriwa_Soriwa
 * Method:    deleteAudioById
 * Signature: (I)I
 */
JNIEXPORT jint JNICALL Java_com_newstone_soriwa_Soriwa_deleteAudioById
  (JNIEnv *, jobject, jint);

/*
 * Class:     com_newstone_soriwa_Soriwa
 * Method:    play
 * Signature: (II)I
 */
JNIEXPORT jint JNICALL Java_com_newstone_soriwa_Soriwa_play
  (JNIEnv *, jobject, jint, jint);

#ifdef __cplusplus
}
#endif
#endif
