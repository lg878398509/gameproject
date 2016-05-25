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
	//析构函数
	~GameMain();
private:
	void startTrips(ActionTimeline* timeDown);
	/*
		创建动画
		end_x: x轴结束位置
		end_y: y轴结束位置
	*/
	MoveTo* createMove(float end_x, float end_y);

	//将金块,石头设置成刚体
	void setGoldStoneToBody(Vector<Node *> goldVector);
	//退出当前关卡
	void exitLevel();

	//倒计时方法
	void timeDownCount(float df);
	//游戏结束的处理
	void gameResult();

private:
	int goalCoin;//目标分数
	int curLevel;//当前关卡
	Size size;
	Miner* miner;
	//控制矿工第一次进入时和墙壁的碰撞检测
	int control = -1;
	Text *textcurCoin;
	int curGold;//当前分数
	ActionTimeline* levelDown;

	Text *timeDownText;
	Node *leveltop;

	//抓取到金块并且绳子缩回后自定义事件监听
	EventListenerCustom *pullcompleteListener;

};

#endif // __GAMEMAIN_H__
