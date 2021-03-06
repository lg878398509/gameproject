#include "Miner.h"
#include "SimpleAudioEngine.h"
#include "GlobalDefine.h"
using namespace CocosDenshion;

Scene* Miner::createScene() {
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = Miner::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

bool Miner::init() {
	if (!Layer::init()) {
		return false;
	}

	isRopeSwaying = false;
	ropeHeight = 20.00;
	_gold = NULL;

	miner = SkeletonAnimation::createWithFile("drawable-hdpi/miner.json", "drawable-hdpi/miner.atlas",0.6);
	addChild(miner);

	auto claw = CSLoader::createNode("claw.csb");
	claw->setPosition(Vec2(-7, 52));
	addChild(claw);

	rope = static_cast<ImageView *>(Helper::seekWidgetByName(static_cast<Widget *>(claw), "rope"));
	clawAxis = static_cast<ImageView *>(Helper::seekWidgetByName(static_cast<Widget *>(claw), "clawAxis"));
		
	return true;
}

void Miner::runAppear() {
	miner->addAnimation(0, "miner-appear", true, 0);
	miner->addAnimation(0, "miner-wait", false, 2);
}

void Miner::runDisAppear() {
	miner->addAnimation(0, "miner-disappear", true, 0);
	miner->addAnimation(0, "miner-wait", false, 2);
}

void Miner::runShakeClaw() {
	//先定位旋转角度为 0
	rope->setRotation(0);

	auto seq = Sequence::create(RotateBy::create(1.2, -80), RotateBy::create(2.4, 160), RotateBy::create(1.2, -80), nullptr);
	rope->runAction(RepeatForever::create(seq));
	this->isRopeSwaying = true;
}

void Miner::stopShakeAction() {
	rope->stopAllActions();
}


void Miner::setRopeChanging(bool isChanging) {
	this->isRopeSwaying = isChanging;
}

bool Miner::getRopeChanging() {
	return this->isRopeSwaying;
}

//伸绳子操作
void Miner::runRopeThrow() {
	isRopeSwaying = false;
	unschedule(CC_SCHEDULE_SELECTOR(Miner::reduceRopeHeight));
	schedule(CC_SCHEDULE_SELECTOR(Miner::addRopeHeight),0.05);
	miner->addAnimation(0, "miner-throw", false, 0);
}

//增加绳子的长度
void Miner::addRopeHeight(float df) {
	
	ropeHeight += 20;
 	rope->setSize(Size(rope->getSize().width, ropeHeight));
	
}

//缩绳子操作
void Miner::runRopePull() {
	//拉绳子声音
	if (UserDefault::getInstance()->getBoolForKey(IS_PLAY_EFFECT)) {
		pullClawSound = SimpleAudioEngine::getInstance()->playEffect(PULL_CLAW_MUSIC, true);
	}

	unschedule(CC_SCHEDULE_SELECTOR(Miner::addRopeHeight));
	schedule(CC_SCHEDULE_SELECTOR(Miner::reduceRopeHeight), 0.05);

	if (_gold && (_gold->getWeight() >= 6)) {
		miner->addAnimation(0, "miner-pull-heavy", true, 0);
	}
	else {
		miner->addAnimation(0, "miner-pull-light", true, 0);
	}
}

//减少绳子的长度
void Miner::reduceRopeHeight(float df) {

	if (_gold) {
		ropeHeight -= (13 - _gold->getWeight());
	}
	else {
		ropeHeight -= 13;
		
	}
	if (ropeHeight <= 20) {
		unschedule(CC_SCHEDULE_SELECTOR(Miner::reduceRopeHeight));
		ropeHeight = 20;
			
		//开始钩子摇滚的动画
		runShakeClaw();

		//移除金块
		if (_gold) {
			if (UserDefault::getInstance()->getBoolForKey(IS_PLAY_EFFECT)) {
				SimpleAudioEngine::getInstance()->playEffect(GET_GOLD_MUSIC, false);
			}
			_eventDispatcher->dispatchCustomEvent("pullcomplete", String::createWithFormat("%d", _gold->getValue()));
			
			//恢复钩子原来的状态
			runClawOpen();
			_gold->removeFromParent();
			
			_gold = NULL;
		}

		miner->addAnimation(0, "miner-wait", false, 0);
		isRopeSwaying = true;
		SimpleAudioEngine::getInstance()->stopEffect(pullClawSound);
		
		
	}
	rope->setSize(Size(rope->getSize().width, ropeHeight));

	
}


//合拢钩子
void Miner::runClawClose() {
	auto leftClaw = Helper::seekWidgetByName(static_cast<Widget *>(clawAxis), "clawLeft");
	auto rightClaw = Helper::seekWidgetByName(static_cast<Widget *>(clawAxis), "clawRight");

	leftClaw->runAction(RotateBy::create(0.3, -15));
	rightClaw->runAction(RotateBy::create(0.3, 15));
}


//张开钩子
void Miner::runClawOpen() {
	auto leftClaw = Helper::seekWidgetByName(static_cast<Widget *>(clawAxis), "clawLeft");
	auto rightClaw = Helper::seekWidgetByName(static_cast<Widget *>(clawAxis), "clawRight");

	leftClaw->runAction(RotateBy::create(0.3, 15));
	rightClaw->runAction(RotateBy::create(0.3, -15));
}

//添加金块
void Miner::addGold(std::string type, Size size) {
	_gold = Gold::create(type, size);
	clawAxis->addChild(_gold);

	if (type == "smallGold") {
		_gold->setPosition(Vec2(6, -15));
	}
	else if (type == "moddleGold") {
		_gold->setPosition(Vec2(6, -25));
	}
	else if (type == "bigGold") {
		_gold->setPosition(Vec2(6, -46));
	}
	else if (type == "smallstone") {
		_gold->setAnchorPoint(Vec2(0.5, 1));
		_gold->setPosition(Vec2(6, 0));
	}
	else if (type == "bigstone") {
		_gold->setAnchorPoint(Vec2(0.5, 1));
		_gold->setPosition(Vec2(6, 0));
	}
}

Point Miner::getClawAxisPoint() {
	return clawAxis->getPosition();
}

//扔掉金块
void Miner::dropGold() {

	SimpleAudioEngine::getInstance()->stopAllEffects();

	unschedule(CC_SCHEDULE_SELECTOR(Miner::addRopeHeight));
	unschedule(CC_SCHEDULE_SELECTOR(Miner::reduceRopeHeight));
	
	if (_gold) {
		_gold->removeFromParent();
		_gold = NULL;
	}

	//绳子缩短
	rope->setSize(Size(rope->getSize().width, 20));
}

bool Miner::isAddGold() {
	return NULL != _gold ? true : false;
}

void Miner::setClawAxisToPhysics() {
	PhysicsBody *body = PhysicsBody::createCircle(15);
	body->setCategoryBitmask(11);
	body->setContactTestBitmask(11);
	body->setCollisionBitmask(11);
	clawAxis->setPhysicsBody(body);
}