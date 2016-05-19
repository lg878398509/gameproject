#ifndef __GAMEPAUSE_H__
#define __GAMEPAUSE_H__

#include "cocos2d.h"
#include "cocostudio\CocoStudio.h"

#include "ui/CocosGUI.h"
using namespace cocos2d::ui; 
USING_NS_CC;

class GamePause : public cocos2d::LayerColor
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    // implement the "static create()" method manually
    CREATE_FUNC(GamePause);
	//禁用“下一关”按钮
	void setNextDisabled();
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
	//退出关卡
	void btnExit(Ref *pSender, Widget::TouchEventType type);
	//移除自己
	void removeSeft(Ref *pSender);
	
private:
	Size visiableSize;
	Node *gamePause;
	Button *btnEffect;
	Button *btnBgMusic;
	Button *btnNextLevel;//下一关

};

#endif // __GAMEPAUSE_H__
