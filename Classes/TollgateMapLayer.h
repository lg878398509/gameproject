/*
    �ļ�����    TollgateMapLayer.h
    �衡����    
    �����ˣ�    
*/
#ifndef _TOLLGATEMAPLAYER_H_
#define _TOLLGATEMAPLAYER_H_

#include "cocos2d.h"
USING_NS_CC;

class TollgateMapLayer : public Layer {
public:
	TollgateMapLayer();
	~TollgateMapLayer();

	CREATE_FUNC(TollgateMapLayer);
	virtual bool init();

private:
	/*��ǰ�ؿ�*/
	int m_iCurLevel;
	/*��ȡ�ؿ������ļ�*/
	void loadConfig();
};


#endif