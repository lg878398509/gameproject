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
	//���á���һ�ء���ť
	void setNextDisabled();
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
	//�˳��ؿ�
	void btnExit(Ref *pSender, Widget::TouchEventType type);
	//�Ƴ��Լ�
	void removeSeft(Ref *pSender);
	
private:
	Size visiableSize;
	Node *gamePause;
	Button *btnEffect;
	Button *btnBgMusic;
	Button *btnNextLevel;//��һ��

};

#endif // __GAMEPAUSE_H__
