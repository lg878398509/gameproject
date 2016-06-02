#include "Newbie.h"
#include "SimpleAudioEngine.h"
#include "GlobalDefine.h"
using namespace CocosDenshion;

Scene* Newbie::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = Newbie::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool Newbie::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !LayerColor::initWithColor(Color4B(0, 0, 0, 100)))
    {
        return false;
    }
	//初始化变量
	win_size = Director::getInstance()->getVisibleSize();


	//加载 新手教程 界面
	newbie = CSLoader::createNode("newbie.csb");
	newbie->setPosition(-300, win_size.height/2);
	newbie->setAnchorPoint(Point(0.5, 0.5));
	addChild(newbie);

	auto moveCenter = MoveTo::create(0.5, Vec2(win_size.width / 2, win_size.height / 2));
	newbie->runAction(EaseBackInOut::create(moveCenter));

	//关闭按钮
	auto btnClose = static_cast<Button *>(Helper::seekWidgetByName(static_cast<Widget *>(newbie), "btnClose"));
	btnClose->addTouchEventListener(CC_CALLBACK_2(Newbie::closeWindow, this));

	//下一步
	auto btnNext = static_cast<Button *>(Helper::seekWidgetByName(static_cast<Widget *>(newbie), "btnNext"));
	btnNext->addTouchEventListener(CC_CALLBACK_2(Newbie::nextPic, this));

	/*ImageView *imageView = ImageView::create("instruction1.png");
	imageView->setScale9Enabled(true);
	imageView->setAnchorPoint(Point(0.5, 0.5));
	imageView->setTag(100);
	imageView->setPosition(convertToWorldSpace(layout->getPosition()));
	imageView->setContentSize(layout->getContentSize());
	layout->addChild(imageView);*/
    return true;
}

//关闭设置窗口回调
void Newbie::closeWindow(Ref *pSender, Widget::TouchEventType type) {
	auto closeMove = MoveTo::create(0.5, Vec2(win_size.width / 2, - win_size.height / 2));
	newbie->runAction(EaseBackInOut::create(Sequence::create(closeMove, CallFuncN::create([=](Ref *pSender) {
		_eventDispatcher->dispatchCustomEvent("setting_over");
		_eventDispatcher->dispatchCustomEvent("gamePause");
		removeFromParentAndCleanup(true);
	}), nullptr)));
}

//下一步切换图片
void Newbie::nextPic(Ref *pSender, Widget::TouchEventType type) {
	if (type == Widget::TouchEventType::ENDED) {
		/*if (layout->getChildByName("instruction2") != NULL) {
			closeWindow(pSender, type);
			return;
		}
		ImageView *imageView = ImageView::create("instruction2.png");
		imageView->setName("instruction2");
		imageView->setScale9Enabled(true);
		imageView->setAnchorPoint(Point(0.5, 0.5));
		imageView->setPosition(convertToWorldSpace(layout->getPosition()));
		layout->removeChildByTag(100);
		layout->addChild(imageView);*/
		

		auto img = static_cast<ImageView *>(Helper::seekWidgetByName(static_cast<Widget *>(newbie), "newbie_img"));
		if (0 == img->getTag()) {
			closeWindow(pSender, type);
			return;
		}
		img->loadTexture("drawable-hdpi/instruction2.png", TextureResType::LOCAL);
		img->setTag(0);
	}
}
