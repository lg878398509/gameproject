#ifndef __MINER_H__
#define __MINER_H__

#include "cocostudio\CocoStudio.h"
#include "ui/CocosGUI.h"
#include "spine\spine-cocos2dx.h"
#include "Gold.h"
using namespace cocos2d::ui;
USING_NS_CC;
using namespace spine;

class Miner : public cocos2d::Layer
{
public:
	//绳子头
	ImageView* rope;
private:
	SkeletonAnimation* miner;
	ImageView* clawAxis;
	//钩子是否在左右摆动
	bool isRopeSwaying;
	//绳子高度
	float ropeHeight;
	Gold *_gold;

	int pullClawSound;

public:
    static cocos2d::Scene* createScene();

    virtual bool init();
	//出现动画
	void runAppear();
	//出现动画
	void runDisAppear();
	//左右摆动
	void runShakeClaw();

	//停止旋转动画
	void stopShakeAction();
    
    // implement the "static create()" method manually
    CREATE_FUNC(Miner);
	//设置钩子是否摆动方法
	void setRopeChanging(bool isChanging);
	//获取钩子是否摆动方法
	bool getRopeChanging();
	//绳子伸长方法
	void runRopeThrow();
	//缩绳子操作
	void runRopePull();
	//合拢钩子
	void runClawClose();
	//张开钩子
	void runClawOpen();
	//添加金块
	void addGold(std::string type);
	//得到钩子轴承位置
	Point getClawAxisPoint();

	//扔掉金块
	void dropGold();

	bool isAddGold();
private:
	//增加绳子的长度
	void addRopeHeight(float df);
	//减少绳子的长度
	void reduceRopeHeight(float df);
};

#endif // __MINER_H__
