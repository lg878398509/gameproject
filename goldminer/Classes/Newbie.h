#ifndef __NEWBIE_H__
#define __NEWBIE_H__

#include "cocos2d.h"
#include "cocostudio\CocoStudio.h"

#include "ui/CocosGUI.h"
using namespace cocos2d::ui; 
USING_NS_CC;

class Newbie : public cocos2d::LayerColor
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    // implement the "static create()" method manually
    CREATE_FUNC(Newbie);
private:
	//�ر����ô��ڻص�
	void closeWindow(Ref *pSender, Widget::TouchEventType type);

	//��һ���л�ͼƬ
	void nextPic(Ref *pSender, Widget::TouchEventType type);


	Size win_size;

	Node *newbie;

	Layout *layout;

};

#endif // __NEWBIE_H__
