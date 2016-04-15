/*
    文件名：    TollgateScene.h
    描　述：    
    创建人：    
*/
#ifndef _TOLLGATESCENE_H_
#define _TOLLGATESCENE_H_

#include "cocos2d.h"
USING_NS_CC;

#define TAG_MAP_LAYER  1   //地图tag
#define TAG_DATA_LAYER  2  //数据层tag

class TollgateScene : public Layer {
public:
	static Scene *createScene();
	virtual bool init();
	CREATE_FUNC(TollgateScene);
};


#endif