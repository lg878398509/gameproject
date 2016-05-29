#include "GameSetting.h"
#include "SimpleAudioEngine.h"
#include "GlobalDefine.h"
using namespace CocosDenshion;

Scene* GameSetting::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = GameSetting::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool GameSetting::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !LayerColor::initWithColor(Color4B(0, 0, 0, 100)))
    {
        return false;
    }

	visiableSize = Director::getInstance()->getVisibleSize();
	menuSetting = CSLoader::createNode("menuSetting.csb");
	menuSetting->setAnchorPoint(Vec2(0.5, 0.5));
	menuSetting->setPosition(Point(-200, visiableSize.height / 2));

	//添加动画
	auto enterAction = MoveTo::create(0.5, Vec2(visiableSize.width/2, visiableSize.height/2));
	menuSetting->runAction(EaseBackInOut::create(enterAction));
	this->addChild(menuSetting);

	//关闭窗口
	auto btnClose = static_cast<Button *>(Helper::seekWidgetByName(static_cast<Button *>(menuSetting), "btnClose"));
	btnClose->addTouchEventListener(CC_CALLBACK_2(GameSetting::closeWindow, this));
	

	//碰撞声音设置
	btnEffect = static_cast<Button *>(Helper::seekWidgetByName(static_cast<Button *>(menuSetting), "btnEffect"));
	btnEffect->addTouchEventListener(CC_CALLBACK_2(GameSetting::closeEffect, this));
	if (UserDefault::getInstance()->getBoolForKey(IS_PLAY_EFFECT)) {
		btnEffect->loadTextureNormal("sound-on-btn-0.png", TextureResType::PLIST);
	}
	else {
		btnEffect->loadTextureNormal("sound-off-btn-0.png", TextureResType::PLIST);
	}

	//背景音乐设置
	btnBgMusic = static_cast<Button *>(Helper::seekWidgetByName(static_cast<Button *>(menuSetting), "btnBgMusic"));
	btnBgMusic->addTouchEventListener(CC_CALLBACK_2(GameSetting::closeBgMusic, this));
	if (UserDefault::getInstance()->getBoolForKey(IS_PLAY_BG_MUSIC)) {
		btnBgMusic->loadTextureNormal("music-on-btn-0.png", TextureResType::PLIST);
	}
	else {
		btnBgMusic->loadTextureNormal("music-off-btn-0.png", TextureResType::PLIST);
	}

	//新手教程
	auto btnNewbie = static_cast<Button *>(Helper::seekWidgetByName(static_cast<Button *>(menuSetting), "btnNewbie"));
	btnNewbie->addTouchEventListener(CC_CALLBACK_2(GameSetting::newbie, this));

	//关于我们
	auto btnAbout = static_cast<Button *>(Helper::seekWidgetByName(static_cast<Button *>(menuSetting), "btnAbout"));
	btnAbout->addTouchEventListener(CC_CALLBACK_2(GameSetting::about, this));

    return true;
}


void GameSetting::closeWindow(Ref *pSender, Widget::TouchEventType type) {
	
	if (type == Widget::TouchEventType::ENDED)
	{
		auto moveBack = MoveTo::create(0.5, Vec2(2*visiableSize.width, visiableSize.height/2));
		auto seq = Sequence::create(moveBack, CallFuncN::create(CC_CALLBACK_1(GameSetting::removeSeft, this)), nullptr);
		menuSetting->runAction(seq);
	}
}

void GameSetting::removeSeft(Ref *pSender) {
	_eventDispatcher->dispatchCustomEvent("setting_over");
	removeFromParentAndCleanup(true);
	
}

//碰撞声音设置
void GameSetting::closeEffect(Ref *pSender, Widget::TouchEventType type) {
	if (type == Widget::TouchEventType::ENDED) {
		if (UserDefault::getInstance()->getBoolForKey(IS_PLAY_EFFECT, false)) {
			UserDefault::getInstance()->setBoolForKey(IS_PLAY_EFFECT, false);
			btnEffect->loadTextureNormal("sound-off-btn-0.png", TextureResType::PLIST);
			btnEffect->loadTexturePressed("sound-off-btn-1.png", TextureResType::PLIST);
		}
		else {
			UserDefault::getInstance()->setBoolForKey(IS_PLAY_EFFECT, true);
			btnEffect->loadTextureNormal("sound-on-btn-0.png", TextureResType::PLIST);
			btnEffect->loadTexturePressed("sound-on-btn-1.png", TextureResType::PLIST);
		}
	}
}
//背景音乐设置
void GameSetting::closeBgMusic(Ref *pSender, Widget::TouchEventType type) {
	if (type == Widget::TouchEventType::ENDED) {
		if (UserDefault::getInstance()->getBoolForKey(IS_PLAY_BG_MUSIC, false)) {
			UserDefault::getInstance()->setBoolForKey(IS_PLAY_BG_MUSIC, false);
			SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
			btnBgMusic->loadTextureNormal("music-off-btn-0.png", TextureResType::PLIST);
			btnBgMusic->loadTexturePressed("music-off-btn-1.png", TextureResType::PLIST);
		} else {
			UserDefault::getInstance()->setBoolForKey(IS_PLAY_BG_MUSIC, true);
			SimpleAudioEngine::getInstance()->playBackgroundMusic(BG_MUSIC, true);
			btnBgMusic->loadTextureNormal("music-on-btn-0.png", TextureResType::PLIST);
			btnBgMusic->loadTexturePressed("music-on-btn-1.png", TextureResType::PLIST);
		}
	}
}
//新手教程
void GameSetting::newbie(Ref *pSender, Widget::TouchEventType type) {
	if (type == Widget::TouchEventType::ENDED) {
		//关闭设置框
		auto moveBack = MoveTo::create(0.5, Vec2(2 * visiableSize.width, visiableSize.height / 2));
		auto seq = Sequence::create(moveBack, CallFuncN::create([=](Ref *pSender) {
			_eventDispatcher->dispatchCustomEvent("newbie");
			removeFromParentAndCleanup(true);
		}), nullptr);
		menuSetting->runAction(seq);
	}


}
//关于我们
void GameSetting::about(Ref *pSender, Widget::TouchEventType type) {
	if (type == Widget::TouchEventType::ENDED) {
		Director::getInstance()->end();
	}
}
