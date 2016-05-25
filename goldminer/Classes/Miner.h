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
	//����ͷ
	ImageView* rope;
private:
	SkeletonAnimation* miner;
	ImageView* clawAxis;
	//�����Ƿ������Ұڶ�
	bool isRopeSwaying;
	//���Ӹ߶�
	float ropeHeight;
	Gold *_gold;

	int pullClawSound;

public:
    static cocos2d::Scene* createScene();

    virtual bool init();
	//���ֶ���
	void runAppear();
	//���ֶ���
	void runDisAppear();
	//���Ұڶ�
	void runShakeClaw();

	//ֹͣ��ת����
	void stopShakeAction();
    
    // implement the "static create()" method manually
    CREATE_FUNC(Miner);
	//���ù����Ƿ�ڶ�����
	void setRopeChanging(bool isChanging);
	//��ȡ�����Ƿ�ڶ�����
	bool getRopeChanging();
	//�����쳤����
	void runRopeThrow();
	//�����Ӳ���
	void runRopePull();
	//��£����
	void runClawClose();
	//�ſ�����
	void runClawOpen();
	//��ӽ��
	void addGold(std::string type);
	//�õ��������λ��
	Point getClawAxisPoint();

	//�ӵ����
	void dropGold();

	bool isAddGold();
private:
	//�������ӵĳ���
	void addRopeHeight(float df);
	//�������ӵĳ���
	void reduceRopeHeight(float df);
};

#endif // __MINER_H__
