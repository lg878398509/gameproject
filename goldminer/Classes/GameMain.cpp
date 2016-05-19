#include "GameMain.h"
#include "GameMenu.h"
#include "GamePause.h"

#define WORLDTAG 100

MoveTo* GameMain::createMove(float end_x, float end_y) {
	return MoveTo::create(1, Vec2(end_x, end_y));
}

Scene* GameMain::createScene() {
	// 'scene' is an autorelease object
	auto scene = Scene::createWithPhysics();

	//��������������
	PhysicsWorld *world = scene->getPhysicsWorld();
	world->setGravity(Vec2::ZERO);

	Size size = Director::getInstance()->getWinSize();
	PhysicsBody *body = PhysicsBody::createEdgeBox(size);
	body->setCategoryBitmask(10);
	body->setCategoryBitmask(10);
	body->setContactTestBitmask(10);

	Node *node = Node::create();
	node->setPosition(size/2);
	node->setPhysicsBody(body);
	node->setTag(WORLDTAG);
	scene->addChild(node);
	// 'layer' is an autorelease object
	auto layer = GameMain::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

bool GameMain::init() {
	if (!Layer::init()) {
		return false;
	}

	if (UserDefault::getInstance()->getBoolForKey(IS_PLAY_BG_MUSIC) && !SimpleAudioEngine::getInstance()->isBackgroundMusicPlaying()) {
		SimpleAudioEngine::getInstance()->playBackgroundMusic(LEVEL_BG_MUSIC, true);
	}

	size = Director::getInstance()->getVisibleSize();

	leftTime = 60;


	//auto level_1 = CSLoader::createNode("level_1.csb");
	Data data = FileUtils::getInstance()->getDataFromFile("Level_1.csb");
	Node* level_1 = CSLoader::createNode(data);
	//���ö���
	Vector<Node*> vectorGold = Helper::seekWidgetByName(static_cast<Layout *>(level_1), "panelGold")->getChildren();
	
	setGoldStoneToBody(vectorGold);

	curLevel = UserDefault::getInstance()->getIntegerForKey(CUR_LEVEL);
	curGold = UserDefault::getInstance()->getIntegerForKey(CUR_GOLD);

	goalCoin = GOAL_COIN(curLevel);

	//��ʾ��ǰ�ؿ�
	auto leveltop = CSLoader::createNode("leveltop.csb");
	levelDown = CSLoader::createTimeline("leveltop.csb");
	leveltop->runAction(levelDown);
	levelDown->gotoFrameAndPause(0);


	auto textCurLevel = static_cast<Text *>(Helper::seekWidgetByName(static_cast<Layout *> (leveltop), "curLevel"));
	textCurLevel->setText(StringUtils::toString(curLevel));
	//��ʾĿ���ҷ���
	auto textgoalCoin = static_cast<Text *>(Helper::seekWidgetByName(static_cast<Layout *> (leveltop), "goalCoin"));
	textgoalCoin->setText(StringUtils::toString(goalCoin));

	//��ʾ��ǰ�����
	textcurCoin = static_cast<Text *>(Helper::seekWidgetByName(static_cast<Layout *> (leveltop), "curCoin"));
	textcurCoin->setText(String::createWithFormat("%d", curGold)->getCString());

	//����ʱ��
	timeDownText = static_cast<Text *>(Helper::seekWidgetByName(static_cast<Layout *> (leveltop), "timeDown"));
	timeDownText->setText(StringUtils::toString(leftTime));

	addChild(level_1);

	addChild(leveltop);

	//��ӿ�
	miner = Miner::create();
	miner->setPosition(size.width+100, size.height - 210);
	addChild(miner);

	//��ʼ�ؿ���ʾ������ �������ص�������Ϸ����
	startTrips(levelDown);
	

	//������ײ�����¼�
	auto physicsListener = EventListenerPhysicsContact::create();
	physicsListener->onContactBegin = [=](PhysicsContact& contact) {
		if (-1 != control) {
			//�ж���ײ��������߽绹�ǽ��
			auto shapeB = contact.getShapeB()->getBody()->getNode();
			if (WORLDTAG != shapeB->getTag()) {
				//��£����
				miner->runClawClose();
				miner->addGold(shapeB->getName());
				//�Ƴ���Ļ�еĽ��
				shapeB->removeFromParent();

			}
			//�����Ӳ���
			miner->runRopePull();
		}
		control++;
		return true;
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(physicsListener, this);


	//��������ӽ����Ļص�
	_eventDispatcher->addCustomEventListener("pullcomplete", [=](EventCustom *evn) {
		String *strValue = (String*) (evn->getUserData());
		int addGold = strValue->intValue();
		curGold += addGold;
		//textcurCoin->setString(String::createWithFormat("%d", curGold)->getCString());

		auto lbsAddGold = LabelTTF::create();
		lbsAddGold->setString(String::createWithFormat("%d", curGold)->getCString());
		lbsAddGold->setFontSize(20);
		lbsAddGold->setColor(Color3B(250, 250, 0));
		addChild(lbsAddGold);

		lbsAddGold->setPosition(miner->rope->convertToWorldSpace(Vec2(miner->getClawAxisPoint().x, miner->getClawAxisPoint().y)));
		auto actionSpawn = Spawn::create(MoveTo::create(0.5, textcurCoin->getPosition()), 
			Sequence::create(ScaleTo::create(0.25, 0.1), nullptr), nullptr);
		auto seq = Sequence::create(actionSpawn, CallFuncN::create([=](Node* node) {
			lbsAddGold->removeFromParent();
			textcurCoin->setString(String::createWithFormat("%d", curGold)->getCString());
		}), nullptr);
		lbsAddGold->runAction(seq);
	});



	//�����Ϸ��ͣ����
	auto btnPause = static_cast<Button *>(Helper::seekWidgetByName(static_cast<Layout *> (leveltop), "btnPause"));
	btnPause->addTouchEventListener([=](Ref *psender, Widget::TouchEventType type) {
		if (type == Widget::TouchEventType::ENDED) {
			onExit();
			auto gamePause = GamePause::create();
			if (curGold < goalCoin) {
				gamePause->setNextDisabled();
			}
			//this->addChild(gamePause);
			Director::getInstance()->getRunningScene()->addChild(gamePause);
			
		}
	});

	//�ָ���ͣ����Ϸ
	_eventDispatcher->addCustomEventListener("gamePause", [=](EventCustom *evn) {
		onEnter();
	});

	//�˳���Ϸ����
	_eventDispatcher->addCustomEventListener("exitLevel", [=](EventCustom *evn) {
		onEnter();
		exitLevel();
	});


	return true;
}

void GameMain::startTrips(ActionTimeline* timeD) {
	//�����Ϸ�ؿ���ʾ
	auto startTrips = CSLoader::createNode("starttrips.csb");
	addChild(startTrips);
	//���õ�ǰ�ؿ���Ŀ�����
	auto tripsCurLevel = static_cast<Text *>(Helper::seekWidgetByName(static_cast<Layout *> (startTrips), "levelNum"));
	tripsCurLevel->setText(StringUtils::toString(curLevel));
	auto tripsgoalCoin = static_cast<Text *>(Helper::seekWidgetByName(static_cast<Layout *> (startTrips), "goalNum"));
	tripsgoalCoin->setText(StringUtils::toString(goalCoin));

	//��ǰ�ؿ�����
	auto levelNode = static_cast<Text *>(Helper::seekWidgetByName(static_cast<Layout *> (startTrips), "levelNode"));
	auto nodeMove = createMove(size.width / 2, levelNode->getPosition().y);
	auto levelSquence = Sequence::create(EaseBackInOut::create(createMove(size.width / 2, levelNode->getPosition().y)), 
		DelayTime::create(1), EaseBackInOut::create(createMove(size.width + levelNode->getSize().width, levelNode->getPosition().y)), nullptr);
	levelNode->runAction(levelSquence);

	//ͼ�궯��
	auto goalSymbol = static_cast<ImageView *> (Helper::seekWidgetByName(static_cast<Layout *> (startTrips), "goalSymbol"));
	auto symbolSquence = Sequence::create(EaseBackInOut::create(createMove(size.width / 2 - 150, goalSymbol->getPosition().y)),
		DelayTime::create(1), EaseBackInOut::create(createMove(size.width / 2 - 150, -100)), nullptr);
	goalSymbol->runAction(symbolSquence);

	//Ŀ���������
	auto goalNode = static_cast<Text *> (Helper::seekWidgetByName(static_cast<Layout *> (startTrips), "goalNode"));
	auto goalNodeSquence = Sequence::create(EaseBackInOut::create(createMove(size.width / 2 + 10, goalNode->getPosition().y)),
		DelayTime::create(1), EaseBackInOut::create(createMove(size.width / 2 + 10, -100)), 
		CCCallFuncN::create([=](Node* node) {
		startTrips->removeFromParentAndCleanup(true);
		miner->runAppear();
		miner->runAction(Sequence::create(MoveTo::create(2, Vec2(size.width / 2, size.height - 210)), CCCallFuncN::create([=](Ref *ref) {
			//����ʱ������
			timeD->gotoFrameAndPlay(0, false);

			//��ʼ�ڶ�����
			miner->runShakeClaw();

			//�����Ļ����¼�[�Ź����¼�]
			auto listener = EventListenerTouchOneByOne::create();

			
			listener->onTouchBegan = [=](Touch* touch, Event* event) {
				if (miner->getRopeChanging()) {
					miner->stopShakeAction();
					miner->runRopeThrow();
				}

				return true;

			};
			_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

			//����ʱ��ʼ
			schedule(CC_SCHEDULE_SELECTOR(GameMain::timeDownCount), 1, 59, 0);
			
		}), nullptr));

	}), nullptr);
	goalNode->runAction(goalNodeSquence);

}

//�����,ʯͷ���óɸ���
void GameMain::setGoldStoneToBody(Vector<Node *> goldVector) {
	for (int i = 0; i < goldVector.size(); i++) {
		auto gold = goldVector.at(i);
		Size goldSize = gold->getContentSize();
		if ("smallGold" == gold->getName()) {//С���
			goldSize = 0.3 * goldSize;
		}
		else if ("moddleGold" == gold->getName()) {//�н��
			goldSize = 0.6 * goldSize;
		}
		else if ("bigGold" == gold->getName()) {//����

		}
		else if ("smallstone" == gold->getName()) {//ʯͷ

		}

		
		auto body = PhysicsBody::createBox(goldSize);
		body->setCategoryBitmask(10);
		body->setCollisionBitmask(10);
		body->setContactTestBitmask(10);
		gold->setPhysicsBody(body);
	}
}


void GameMain::exitLevel() {
	
	//�������
	miner->dropGold();

	levelDown->gotoFrameAndPlay(0, -30, false);
	
	//���볡ʱ���Ӷ���
	miner->runDisAppear();

	auto disAppearSeq = Sequence::create(MoveTo::create(0.5, Vec2(size.width + 100, size.height - 210)),
		CallFuncN::create([=](Ref *ref) {
			auto exitLeveltips = CSLoader::createNode("gameresult.csb");
			addChild(exitLeveltips);
			auto gameExit = static_cast<Text *>(Helper::seekWidgetByName(static_cast<Widget *>(exitLeveltips), "gameExit"));

			//��ʾ���
			auto seq = Sequence::create(EaseBackInOut::create(MoveTo::create(0.5, size / 2)),
				DelayTime::create(1),
				EaseBackInOut::create(MoveTo::create(0.5, Vec2(size.width + 300, size.height / 2))),
				CallFuncN::create([=](Ref *ref) {
				Director::getInstance()->replaceScene(GameMenu::createScene());
			}),
				nullptr);
			gameExit->runAction(seq);
	}), nullptr);
	miner->runAction(disAppearSeq);
}

void GameMain::timeDownCount(float df) {
	leftTime--;
	timeDownText->setText(StringUtils::toString(leftTime));
	if (leftTime <= 0) {
		gameResult();
	}
}

void GameMain::gameResult() {
	levelDown->gotoFrameAndPlay(30, 0, false);

	//���볡ʱ���Ӷ���
	miner->runDisAppear();

	auto disAppearSeq = Sequence::create(MoveTo::create(0.5, Vec2(size.width + 100, size.height - 210)),
		CallFuncN::create([=](Ref *ref) {
		auto exitLeveltips = CSLoader::createNode("gameresult.csb");
		addChild(exitLeveltips);
		auto gameFail = static_cast<Text *>(Helper::seekWidgetByName(static_cast<Widget *>(exitLeveltips), "gameFail"));
		auto userDef = UserDefault::getInstance();
		if (curGold < goalCoin) {
			//��ʾ���
			auto seq = Sequence::create(EaseBackInOut::create(MoveTo::create(0.5, Vec2(size.width/2, gameFail->getPosition().y))),
				DelayTime::create(1),
				EaseBackInOut::create(MoveTo::create(0.5, Vec2(size.width + 300, gameFail->getPosition().y))),
				CallFuncN::create([=](Ref *ref) {
				userDef->setIntegerForKey(CUR_LEVEL, 1);
				userDef->setIntegerForKey(CUR_GOLD, 0);
				Director::getInstance()->replaceScene(GameMenu::createScene());
			}),
				nullptr);
			gameFail->runAction(seq);
		}
		else {
			auto gameSuccess = static_cast<Text *>(Helper::seekWidgetByName(static_cast<Widget *>(exitLeveltips), "gameSuccess"));
			auto nodeCoin = static_cast<Text *>(Helper::seekWidgetByName(static_cast<Widget *>(exitLeveltips), "nodeCoin"));
			auto gainCoinText = static_cast<Text *>(Helper::seekWidgetByName(static_cast<Widget *>(exitLeveltips), "gainCoin"));
			int gainCoinNum = curGold - userDef->getIntegerForKey(CUR_GOLD);
			userDef->setIntegerForKey(CUR_LEVEL, userDef->getIntegerForKey(CUR_LEVEL)+1);
			userDef->setIntegerForKey(CUR_GOLD, curGold);
			gainCoinText->setString(String::createWithFormat("%d", gainCoinNum)->getCString());

			
			//��ʾ���
			auto seq = Sequence::create(EaseBackInOut::create(MoveTo::create(0.5, Vec2(size.width/2, gameSuccess->getPosition().y))),
				DelayTime::create(1),
				EaseBackInOut::create(MoveTo::create(0.5, Vec2(size.width + 300, gameSuccess->getPosition().y))),
				CallFuncN::create([=](Ref *ref) {
					//��ת����һ��
					Director::getInstance()->replaceScene(GameMain::createScene());
				}),
				nullptr);
			gameSuccess->runAction(seq);

			//��ʾ���
			auto nodeCoinSeq = Sequence::create(EaseBackInOut::create(MoveTo::create(0.5, Vec2(size.width / 2, nodeCoin->getPosition().y))),
				DelayTime::create(1),
				EaseBackInOut::create(MoveTo::create(0.5, Vec2(size.width + 300, nodeCoin->getPosition().y))), nullptr);
			nodeCoin->runAction(nodeCoinSeq);
		}
		
	}), nullptr);
	miner->runAction(disAppearSeq);
}

GameMain::~GameMain() {
	_eventDispatcher->removeCustomEventListeners("pullcomplete");
	_eventDispatcher->removeCustomEventListeners("gamePause"); 
	_eventDispatcher->removeCustomEventListeners("exitLevel");  
}
