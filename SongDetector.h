#ifndef SONGDETECTOR_H
#define SONGDETECTOR_H

#include <jni.h>

#ifdef __cplusplus
extern "C" {
#endif

JNIEXPORT jstring JNICALL Java_me_lyrica_utils_system_NativeMusicInfo_getCurrentSong(JNIEnv *, jclass);

#ifdef __cplusplus
}
#endif

#endif // SONGDETECTOR_H 