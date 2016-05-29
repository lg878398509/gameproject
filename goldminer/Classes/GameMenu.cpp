#include "GameMenu.h"
#include "SimpleAudioEngine.h"
#include "GlobalDefine.h"

using namespace CocosDenshion;

USING_NS_CC;

Scene* GameMenu::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = GameMenu::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool GameMenu::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }

	isBtnSettingOption = false;

	if (UserDefault::getInstance()->getBoolForKey(IS_PLAY_BG_MUSIC)) {
		SimpleAudioEngine::getInstance()->playBackgroundMusic(BG_MUSIC, true);
	}

	auto sysMenu = CSLoader::createNode("menu.csb");
	auto aniEnterMenu = CSLoader::createTimeline("menu.csb");
	aniEnterMenu->gotoFrameAndPlay(0, 100, false);
	aniEnterMenu->gotoFrameAndPlay(101, 145, true);
	aniEnterMenu->gotoFrameAndPlay(151, 180, true);
	aniEnterMenu->gotoFrameAndPlay(101, 200, true);
	sysMenu->runAction(aniEnterMenu);
	this->addChild(sysMenu);

	//设置动画
	auto btnSetting = static_cast<Button *>(Helper::seekWidgetByName(static_cast<Layout *>(sysMenu), "menuSetting"));
	btnOption = static_cast<Button *>(Helper::seekWidgetByName(static_cast<Layout *>(sysMenu), "menuOption"));
	
	btnSetting->addTouchEventListener(CC_CALLBACK_2(GameMenu::showSetting, this));
	btnOption->addTouchEventListener(CC_CALLBACK_2(GameMenu::showOption, this));
    
	//开始游戏
	auto gameStart = static_cast<Button *>(Helper::seekWidgetByName(static_cast<Layout *>(sysMenu), "gameStart"));
	gameStart->addTouchEventListener([=](Ref *psender, Widget::TouchEventType type) {
		if (type == Widget::TouchEventType::ENDED) {
			Director::getInstance()->replaceScene(GameMain::createScene());
		}
	});

	_eventDispatcher->addCustomEventListener("newbie", [=](Ref *pSender) {
		onEnter();
		onExit();
		Director::getInstance()->getRunningScene()->addChild(Newbie::create());
	});

	_eventDispatcher->addCustomEventListener("setting_over", [=](Ref *pSender) {
		onEnter();
	});
	return true;
}

void GameMenu::showSetting(Ref *pSender, Widget::TouchEventType type) {
	Point point = btnOption->getPosition();
	if (type == Widget::TouchEventType::ENDED) {
		if (isBtnSettingOption)  //设置按钮显示状态
		{
			auto moveAction = MoveTo::create(0.2, Vec2(point.x, point.y - btnOption->getContentSize().height));
			btnOption->runAction(EaseBackInOut::create(moveAction));
		} else {
			auto moveAction = MoveTo::create(0.2, Vec2(point.x, point.y + btnOption->getContentSize().height));
			btnOption->runAction(EaseBackInOut::create(moveAction));
		}

		isBtnSettingOption = !isBtnSettingOption;
	}
}


void GameMenu::showOption(Ref *pSender, Widget::TouchEventType type) {
	if (type == Widget::TouchEventType::ENDED) {
		onExit();
		auto gameSetting = GameSetting::create();
		//this->addChild(gameSetting);
		Director::getInstance()->getRunningScene()->addChild(gameSetting);
	}
}

GameMenu::~GameMenu() {
	_eventDispatcher->removeCustomEventListeners("newbie");
	_eventDispatcher->removeCustomEventListeners("setting_over");
}