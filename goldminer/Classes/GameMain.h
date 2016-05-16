#ifndef __GAMEMAIN_H__
#define __GAMEMAIN_H__

#include "cocostudio\CocoStudio.h"
#include "ui/CocosGUI.h"
#include "Miner.h"
#include "SimpleAudioEngine.h"
#include "GlobalDefine.h"
#include "cocostudio\ActionTimeline\CCActionTimeline.h"
using namespace CocosDenshion;
using namespace cocos2d::ui;
using namespace cocostudio::timeline;
USING_NS_CC;


class GameMain : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    // implement the "static create()" method manually
    CREATE_FUNC(GameMain);
private:
	void startTrips(ActionTimeline* timeDown);
	/*
		��������
		end_x: x�����λ��
		end_y: y�����λ��
	*/
	auto createMove(float end_x, float end_y);

	//�����,ʯͷ���óɸ���
	void setGoldStoneToBody(Vector<Node *> goldVector);
	//�˳���ǰ�ؿ�
	void exitLevel();

private:
	int goalCoin;//Ŀ�����
	int curLevel;//��ǰ�ؿ�
	Size size;
	Miner* miner;
	//���ƿ󹤵�һ�ν���ʱ��ǽ�ڵ���ײ���
	int control = -1;
	Text *textcurCoin;
	int curGold;

};

#endif // __GAMEMAIN_H__
