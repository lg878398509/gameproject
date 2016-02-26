#include <stdio.h>
#include <jni.h>

/**
 * 调用jni方法，返回广告id, secretkey,banner, interstitial, appWall
 */
jstring Java_com_longer_playdoudou_LongerApplication_getAdConfig(JNIEnv *env, jobject obj){

	return (*env)->NewStringUTF(env, "100029609,e60b472acfd6f958840fc27544b7986b,e2675c90627be52922306f2c1e93137e,8d541d771baf216959450b328fc5b0eb,3010dea21b42f68180d9d7ce0c25b759");
}
