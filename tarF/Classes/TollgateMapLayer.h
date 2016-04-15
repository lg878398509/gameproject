/*
    文件名：    TollgateMapLayer.h
    描　述：    
    创建人：    
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
	/*当前关卡*/
	int m_iCurLevel;
	/*读取关卡配置文件*/
	void loadConfig();
};


#endif