#ifndef __GAMESETTING_H__
#define __GAMESETTING_H__

#include "cocos2d.h"
#include "cocostudio\CocoStudio.h"

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
	//�ر����ô��ڻص�
	void closeWindow(Ref *pSender, Widget::TouchEventType type);
	//��ײ��������
	void closeEffect(Ref *pSender, Widget::TouchEventType type);
	//������������
	void closeBgMusic(Ref *pSender, Widget::TouchEventType type);
	//���ֽ̳�
	void newbie(Ref *pSender, Widget::TouchEventType type);
	//��������
	void about(Ref *pSender, Widget::TouchEventType type);

	void removeSeft(Ref *pSender);
private:
	Size visiableSize;
	Node *menuSetting;
	Button *btnEffect;
	Button *btnBgMusic;

};

#endif // __GAMESETTING_H__
