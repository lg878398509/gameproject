#ifndef __GAMESETTING_H__
#define __GAMESETTING_H__

#include "cocos2d.h"
#include "cocostudio\CocoStudio.h"
#include "Newbie.h"

#include "ui/CocosGUI.h"
using namespace cocos2d::ui; 
USING_NS_CC;

class GameSetting : public cocos2d::LayerColor
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    // implement the "static create()" method manually
    CREATE_FUNC(GameSetting);
private:
	//关闭设置窗口回调
	void closeWindow(Ref *pSender, Widget::TouchEventType type);
	//碰撞声音设置
	void closeEffect(Ref *pSender, Widget::TouchEventType type);
	//背景音乐设置
	void closeBgMusic(Ref *pSender, Widget::TouchEventType type);
	//新手教程
	void newbie(Ref *pSender, Widget::TouchEventType type);
	//关于我们
	void about(Ref *pSender, Widget::TouchEventType type);

	void removeSeft(Ref *pSender);
private:
	Size visiableSize;
	Node *menuSetting;
	Button *btnEffect;
	Button *btnBgMusic;

};

#endif // __GAMESETTING_H__
