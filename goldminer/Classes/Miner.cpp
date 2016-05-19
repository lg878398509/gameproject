#include "Miner.h"

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
	
	PhysicsBody *body = PhysicsBody::createCircle(20);
	body->setCategoryBitmask(10);
	body->setCollisionBitmask(10);
	body->setContactTestBitmask(10);
	clawAxis->setPhysicsBody(body);
	
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
	//�ȶ�λ��ת�Ƕ�Ϊ 0
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

//�����Ӳ���
void Miner::runRopeThrow() {
	isRopeSwaying = false;
	unschedule(CC_SCHEDULE_SELECTOR(Miner::reduceRopeHeight));
	schedule(CC_SCHEDULE_SELECTOR(Miner::addRopeHeight),0.05);
	miner->addAnimation(0, "miner-throw", false, 0);
}

//�������ӵĳ���
void Miner::addRopeHeight(float df) {
	ropeHeight += 10;
 	rope->setSize(Size(rope->getSize().width, ropeHeight));
}

//�����Ӳ���
void Miner::runRopePull() {
	unschedule(CC_SCHEDULE_SELECTOR(Miner::addRopeHeight));
	schedule(CC_SCHEDULE_SELECTOR(Miner::reduceRopeHeight), 0.05);

	if (_gold && (_gold->getWeight() >= 6)) {
		miner->addAnimation(0, "miner-pull-heavy", true, 0);
	}
	else {
		miner->addAnimation(0, "miner-pull-light", true, 0);
	}
}

//�������ӵĳ���
void Miner::reduceRopeHeight(float df) {

	if (_gold) {
		ropeHeight -= (10 - _gold->getWeight());
	}
	else {
		ropeHeight -= 10;
		
	}

	
	if (ropeHeight <= 20) {
		unschedule(CC_SCHEDULE_SELECTOR(Miner::reduceRopeHeight));
		ropeHeight = 20;
			
		//��ʼ����ҡ���Ķ���
		runShakeClaw();

		//�Ƴ����
		if (_gold) {
			_eventDispatcher->dispatchCustomEvent("pullcomplete", String::createWithFormat("%d", _gold->getValue()));

			//�ָ�����ԭ����״̬
			runClawOpen();
			_gold->removeFromParent();
			_gold = NULL;
		}

		miner->addAnimation(0, "miner-wait", false, 0);
		isRopeSwaying = true;
		
	}
	rope->setSize(Size(rope->getSize().width, ropeHeight));

	
}


//��£����
void Miner::runClawClose() {
	auto leftClaw = Helper::seekWidgetByName(static_cast<Widget *>(clawAxis), "clawLeft");
	auto rightClaw = Helper::seekWidgetByName(static_cast<Widget *>(clawAxis), "clawRight");

	leftClaw->runAction(RotateBy::create(0.3, -15));
	rightClaw->runAction(RotateBy::create(0.3, 15));
}


//�ſ�����
void Miner::runClawOpen() {
	auto leftClaw = Helper::seekWidgetByName(static_cast<Widget *>(clawAxis), "clawLeft");
	auto rightClaw = Helper::seekWidgetByName(static_cast<Widget *>(clawAxis), "clawRight");

	leftClaw->runAction(RotateBy::create(0.3, 15));
	rightClaw->runAction(RotateBy::create(0.3, -15));
}

//��ӽ��
void Miner::addGold(std::string type) {
	_gold = Gold::create(type);
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

//�ӵ����
void Miner::dropGold() {
	if (_gold) {
		_gold->removeFromParent();
		_gold = NULL;
		runClawOpen();
	}
}