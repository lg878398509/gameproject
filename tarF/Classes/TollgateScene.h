/*
    �ļ�����    TollgateScene.h
    �衡����    
    �����ˣ�    
*/
#ifndef _TOLLGATESCENE_H_
#define _TOLLGATESCENE_H_

#include "cocos2d.h"
USING_NS_CC;

#define TAG_MAP_LAYER  1   //��ͼtag
#define TAG_DATA_LAYER  2  //���ݲ�tag

class TollgateScene : public Layer {
public:
	static Scene *createScene();
	virtual bool init();
	CREATE_FUNC(TollgateScene);
};


#endif