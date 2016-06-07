#include "GDTAD.h"
#include "cocos2d.h"
USING_NS_CC;

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include "platform/android/jni/JniHelper.h"
#include <jni.h>

const char* AppActivityCalssName = "org/cocos2dx/cpp/AppActivity";

void GDTAD::showAd(int what) {
	cocos2d::JniMethodInfo jniShowAd;
	if (cocos2d::JniHelper::getStaticMethodInfo(jniShowAd, AppActivityCalssName, "showAd", "(I)V")) {
		jniShowAd.env->CallStaticVoidMethod(jniShowAd.classID, jniShowAd.methodID, what);
	}
	else {
		log("jni:showAD false");
	}
}

#else
void GDTAD::showAd(int what) {
	log("jni:showAD");
	return;
}

#endif
