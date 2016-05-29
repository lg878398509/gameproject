#include "GamePause.h"
#include "SimpleAudioEngine.h"
#include "GlobalDefine.h"
using namespace CocosDenshion;

Scene* GamePause::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = GamePause::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool GamePause::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !LayerColor::initWithColor(Color4B(0, 0, 0, 100)))
    {
        return false;
    }

	visiableSize = Director::getInstance()->getVisibleSize();
	gamePause = CSLoader::createNode("gamepause.csb");
	gamePause->setAnchorPoint(Vec2(0.5, 0.5));
	gamePause->setPosition(Point(-200, visiableSize.height / 2));

	//添加动画
	auto enterAction = MoveTo::create(0.5, Vec2(visiableSize.width/2, visiableSize.height/2));
	gamePause->runAction(EaseBackInOut::create(enterAction));
	this->addChild(gamePause);

	//关闭窗口
	auto btnClose = static_cast<Button *>(Helper::seekWidgetByName(static_cast<Button *>(gamePause), "btnClose"));
	btnClose->addTouchEventListener(CC_CALLBACK_2(GamePause::closeWindow, this));
	

	//碰撞声音设置
	btnEffect = static_cast<Button *>(Helper::seekWidgetByName(static_cast<Button *>(gamePause), "btnEffect"));
	btnEffect->addTouchEventListener(CC_CALLBACK_2(GamePause::closeEffect, this));
	if (UserDefault::getInstance()->getBoolForKey(IS_PLAY_EFFECT)) {
		btnEffect->loadTextureNormal("sound-on-btn-0.png", TextureResType::PLIST);
	}
	else {
		btnEffect->loadTextureNormal("sound-off-btn-0.png", TextureResType::PLIST);
	}

	//背景音乐设置
	btnBgMusic = static_cast<Button *>(Helper::seekWidgetByName(static_cast<Button *>(gamePause), "btnBgMusic"));
	btnBgMusic->addTouchEventListener(CC_CALLBACK_2(GamePause::closeBgMusic, this));
	if (UserDefault::getInstance()->getBoolForKey(IS_PLAY_BG_MUSIC)) {
		btnBgMusic->loadTextureNormal("music-on-btn-0.png", TextureResType::PLIST);
	}
	else {
		btnBgMusic->loadTextureNormal("music-off-btn-0.png", TextureResType::PLIST);
	}

	//退出游戏
	auto btnExit = static_cast<Button *>(Helper::seekWidgetByName(static_cast<Button *>(gamePause), "btnExit"));
	btnExit->addTouchEventListener(CC_CALLBACK_2(GamePause::btnExit, this));
	
	//下一关
	btnNextLevel = static_cast<Button *>(Helper::seekWidgetByName(static_cast<Button *>(gamePause), "btnNextLevel"));
	btnNextLevel->addTouchEventListener(CC_CALLBACK_2(GamePause::nextLevel, this));

	//新手教程
	auto btnNewbie = static_cast<Button *>(Helper::seekWidgetByName(static_cast<Button *>(gamePause), "btnNewbie"));
	btnNewbie->addTouchEventListener(CC_CALLBACK_2(GamePause::newbie, this));
    return true;
}


void GamePause::closeWindow(Ref *pSender, Widget::TouchEventType type) {
	
	if (type == Widget::TouchEventType::ENDED)
	{
		auto moveBack = MoveTo::create(0.5, Vec2(2*visiableSize.width, visiableSize.height/2));
		auto seq = Sequence::create(moveBack, CallFuncN::create(CC_CALLBACK_1(GamePause::removeSeft, this)), nullptr);
		gamePause->runAction(seq);
		_eventDispatcher->dispatchCustomEvent("gamePause");
	}
}

void GamePause::removeSeft(Ref *pSender) {
	removeFromParentAndCleanup(true);
}

//碰撞声音设置
void GamePause::closeEffect(Ref *pSender, Widget::TouchEventType type) {
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
void GamePause::closeBgMusic(Ref *pSender, Widget::TouchEventType type) {
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
void GamePause::newbie(Ref *pSender, Widget::TouchEventType type) {
	if (type == Widget::TouchEventType::ENDED) {
		auto moveBack = MoveTo::create(0.5, Vec2(2 * visiableSize.width, visiableSize.height / 2));
		auto seq = Sequence::create(moveBack, CallFuncN::create(CC_CALLBACK_1(GamePause::removeSeft, this)), nullptr);
		gamePause->runAction(seq);
		Director::getInstance()->getRunningScene()->addChild(Newbie::create());
	}
}
//下一关
void GamePause::nextLevel(Ref *pSender, Widget::TouchEventType type) {
	if (type == Widget::TouchEventType::ENDED) {
		if (btnNextLevel->isEnabled()) {
			_eventDispatcher->dispatchCustomEvent("nextLevel");
			removeFromParentAndCleanup(true);
		}
	}
}

//退出游戏
void GamePause::btnExit(Ref *pSender, Widget::TouchEventType type) {
	if (type == Widget::TouchEventType::ENDED)
	{
		auto moveBack = MoveTo::create(0.5, Vec2(2 * visiableSize.width, visiableSize.height / 2));
		auto seq = Sequence::create(moveBack, CallFuncN::create([=](Node *node) {
			_eventDispatcher->dispatchCustomEvent("exitLevel");
			removeFromParentAndCleanup(true);
		}), nullptr);
		gamePause->runAction(seq);
		
	}
}

void GamePause::setNextDisabled() {
	btnNextLevel->setEnabled(false);
	btnNextLevel->loadTextureNormal("btn-2.png", TextureResType::PLIST);
}
