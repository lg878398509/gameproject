#ifndef __GAMEMENU_H__
#define __GAMEMENU_H__

#include "cocos2d.h"
#include "GameMain.h"
#include "cocostudio\CocoStudio.h"
#include "GameSetting.h"

#include "ui/CocosGUI.h"
using namespace cocos2d::ui; 

class GameMenu : public cocos2d::Layer
{
public:
	~GameMenu();

    static cocos2d::Scene* createScene();

    virtual bool init();
    
    // implement the "static create()" method manually
    CREATE_FUNC(GameMenu);

	//点击回掉显示动画
	void showSetting(Ref *pSender, Widget::TouchEventType type);

	//设置点击回掉
	void showOption(Ref *pSender, Widget::TouchEventType type);
private:
	bool isBtnSettingOption;
	Button *btnOption;
};

#endif // __GAMEMENU_H__
