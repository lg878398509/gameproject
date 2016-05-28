#ifndef __GOLD_H__
#define __GOLD_H__

#include "cocostudio\CocoStudio.h"
#include "ui/CocosGUI.h"
#include "spine\spine-cocos2dx.h"
using namespace cocos2d::ui;
USING_NS_CC;
using namespace spine;

class Gold : public cocos2d::Sprite
{
public:
    virtual bool init(std::string type, Size size);

	static Gold* create(std::string type, Size size);

	int getWeight();

	int getValue();
private:
	/*
		��������
	*/
	int weight;
	/*
		�����
	*/
	int value;
	
};

#endif // __GOLD_H__
