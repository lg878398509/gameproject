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
		创建动画
		end_x: x轴结束位置
		end_y: y轴结束位置
	*/
	auto createMove(float end_x, float end_y);

	//将金块,石头设置成刚体
	void setGoldStoneToBody(Vector<Node *> goldVector);
	//退出当前关卡
	void exitLevel();

private:
	int goalCoin;//目标分数
	int curLevel;//当前关卡
	Size size;
	Miner* miner;
	//控制矿工第一次进入时和墙壁的碰撞检测
	int control = -1;
	Text *textcurCoin;
	int curGold;

};

#endif // __GAMEMAIN_H__
