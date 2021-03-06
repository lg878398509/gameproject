#include "GameMain.h"
#include "GameMenu.h"
#include "GamePause.h"
#include "GDTAD.h"

#define WORLDTAG 100

MoveTo* GameMain::createMove(float end_x, float end_y) {
	return MoveTo::create(1, Vec2(end_x, end_y));
}

Scene* GameMain::createScene() {
	// 'scene' is an autorelease object
	auto scene = Scene::createWithPhysics();

	//设置物理刚体相关
	PhysicsWorld *world = scene->getPhysicsWorld();
	world->setGravity(Vec2::ZERO);

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 originSizeS = Director::getInstance()->getVisibleOrigin();

	PhysicsBody *body = PhysicsBody::createEdgeBox(visibleSize);
	body->setCategoryBitmask(1);
	body->setContactTestBitmask(10);
	body->setCollisionBitmask(1);

	Node *node = Node::create();
	node->setPosition(SCREEN_MIDDLE(visibleSize.width, originSizeS.x), visibleSize.height / 2 + originSizeS.y);
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

	if (UserDefault::getInstance()->getBoolForKey(IS_PLAY_BG_MUSIC)) {
		SimpleAudioEngine::getInstance()->playBackgroundMusic(LEVEL_BG_MUSIC, true);
	}

	size = Director::getInstance()->getVisibleSize();
	originSize = Director::getInstance()->getVisibleOrigin();

	curLevel = UserDefault::getInstance()->getIntegerForKey(CUR_LEVEL);
	curGold = UserDefault::getInstance()->getIntegerForKey(CUR_GOLD);
	goalCoin = GOAL_COIN(curLevel);

	//auto level_1 = CSLoader::createNode("level_1.csb");
	Data data = FileUtils::getInstance()->getDataFromFile(String::createWithFormat("Level_%d.csb", (curLevel % 7))->getCString());
	Node* level_1 = CSLoader::createNode(data);
	//设置动画
	Vector<Node*> vectorGold = Helper::seekWidgetByName(static_cast<Layout *>(level_1), "panelGold")->getChildren();
	
	setGoldStoneToBody(vectorGold);

	//显示当前关卡
	auto leveltop = CSLoader::createNode("leveltop.csb");
	levelDown = CSLoader::createTimeline("leveltop.csb");
	leveltop->runAction(levelDown);
	levelDown->gotoFrameAndPause(0);


	auto textCurLevel = static_cast<Text *>(Helper::seekWidgetByName(static_cast<Layout *> (leveltop), "curLevel"));
	textCurLevel->setText(StringUtils::toString(curLevel));
	//显示目标金币分数
	auto textgoalCoin = static_cast<Text *>(Helper::seekWidgetByName(static_cast<Layout *> (leveltop), "goalCoin"));
	textgoalCoin->setText(StringUtils::toString(goalCoin));

	//显示当前金币数
	textcurCoin = static_cast<Text *>(Helper::seekWidgetByName(static_cast<Layout *> (leveltop), "curCoin"));
	textcurCoin->setText(String::createWithFormat("%d", curGold)->getCString());

	//倒计时牌
	timeDownText = static_cast<Text *>(Helper::seekWidgetByName(static_cast<Layout *> (leveltop), "timeDown"));
	timeDownText->setText(StringUtils::toString(GAME_LEFT_TIME(curLevel)));

	addChild(level_1);

	addChild(leveltop);

	//添加矿工
	miner = Miner::create();
	miner->setPosition(size.width + size.width/4, size.height - 210);
	addChild(miner);

	//开始关卡提示动画， 及动画回掉进入游戏界面
	startTrips(levelDown);
	

	//创建碰撞监听事件
	auto physicsListener = EventListenerPhysicsContact::create();
	physicsListener->onContactBegin = [=](PhysicsContact& contact) {
		//判断碰撞的是世界边界还是金块
		auto shapeB = contact.getShapeB()->getBody()->getNode();
		//钩子碰撞到金币的声音
		if (UserDefault::getInstance()->getBoolForKey(IS_PLAY_EFFECT) && !miner->isAddGold()) {
			if (shapeB->getName() == "smallGold" || shapeB->getName() == "moddleGold") {
				SimpleAudioEngine::getInstance()->playEffect(CONTACT_GOLD_NORMAL_MUSIC);
			}
			else if (shapeB->getName() == "bigGold") {
				SimpleAudioEngine::getInstance()->playEffect(CONTACT_GOLD_BIG_MUSIC);
			}
			else if (shapeB->getName() == "bigstone" || shapeB->getName() == "smallstone") {
				SimpleAudioEngine::getInstance()->playEffect(CONTACT_STONE_MUSIC);
			}
		}

		if (WORLDTAG != shapeB->getTag() && !miner->isAddGold()) {
			//合拢钩子
			miner->runClawClose();
			miner->addGold(shapeB->getName(), shapeB->getBoundingBox().size);
			//移除屏幕中的金块
			shapeB->removeFromParent();

		}
		//拉绳子操作
		miner->runRopePull();
		return true;
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(physicsListener, this);


	pullcompleteListener = EventListenerCustom::create("pullcomplete", [=](EventCustom* event) {
		String *strValue = (String*)(event->getUserData());
		int addGold = strValue->intValue();
		curGold += addGold;
		//textcurCoin->setString(String::createWithFormat("%d", curGold)->getCString());

		auto lbsAddGold = LabelTTF::create();
		lbsAddGold->setString(String::createWithFormat("%d", curGold)->getCString());
		lbsAddGold->setFontSize(20);
		lbsAddGold->setColor(Color3B(250, 250, 0));
		addChild(lbsAddGold);

		//加入金币的声音
		if (UserDefault::getInstance()->getBoolForKey(IS_PLAY_EFFECT)) {
			SimpleAudioEngine::getInstance()->playEffect(ADD_SCORE_MUSIC, false);
		}
		

		lbsAddGold->setPosition(miner->rope->convertToWorldSpace(Vec2(miner->getClawAxisPoint().x, miner->getClawAxisPoint().y)));
		auto actionSpawn = Spawn::create(MoveTo::create(0.5, textcurCoin->getPosition()),
			Sequence::create(ScaleTo::create(0.25, 0.1), nullptr), nullptr);
		auto seq = Sequence::create(actionSpawn, CallFuncN::create([=](Node* node) {
			lbsAddGold->removeFromParent();
			textcurCoin->setString(String::createWithFormat("%d", curGold)->getCString());
		}), nullptr);
		lbsAddGold->runAction(seq);
	});

	_eventDispatcher->addEventListenerWithFixedPriority(pullcompleteListener, 1);


	nextLevelListener = EventListenerCustom::create("nextLevel", [=](EventCustom* event) {
		onEnter();
		gameResult();
	});
	_eventDispatcher->addEventListenerWithFixedPriority(nextLevelListener, 2);



	////添加拉绳子结束的回掉
	//_eventDispatcher->addCustomEventListener("pullcomplete", [=](EventCustom *evn) {
	//	String *strValue = (String*)(evn->getUserData());
	//	int addGold = strValue->intValue();
	//	curGold += addGold;
	//	//textcurCoin->setString(String::createWithFormat("%d", curGold)->getCString());

	//	auto lbsAddGold = LabelTTF::create();
	//	lbsAddGold->setString(String::createWithFormat("%d", curGold)->getCString());
	//	lbsAddGold->setFontSize(20);
	//	lbsAddGold->setColor(Color3B(250, 250, 0));
	//	addChild(lbsAddGold);

	//	lbsAddGold->setPosition(miner->rope->convertToWorldSpace(Vec2(miner->getClawAxisPoint().x, miner->getClawAxisPoint().y)));
	//	auto actionSpawn = Spawn::create(MoveTo::create(0.5, textcurCoin->getPosition()),
	//		Sequence::create(ScaleTo::create(0.25, 0.1), nullptr), nullptr);
	//	auto seq = Sequence::create(actionSpawn, CallFuncN::create([=](Node* node) {
	//		lbsAddGold->removeFromParent();
	//		textcurCoin->setString(String::createWithFormat("%d", curGold)->getCString());
	//	}), nullptr);
	//	lbsAddGold->runAction(seq);
	//});


	//添加游戏暂停监听
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

	//恢复暂停的游戏
	_eventDispatcher->addCustomEventListener("gamePause", [=](EventCustom *evn) {
		onEnter();
	});

	//退出游戏监听
	_eventDispatcher->addCustomEventListener("exitLevel", [=](EventCustom *evn) {
		onEnter();

		//显示插屏广告
		GDTAD::showAd(1);
		exitLevel();
	});

	return true;
}

void GameMain::startTrips(ActionTimeline* timeD) {
	//添加游戏关卡提示
	auto startTrips = CSLoader::createNode("starttrips.csb");
	addChild(startTrips);
	//设置当前关卡和目标分数
	auto tripsCurLevel = static_cast<Text *>(Helper::seekWidgetByName(static_cast<Layout *> (startTrips), "levelNum"));
	tripsCurLevel->setText(StringUtils::toString(curLevel));
	auto tripsgoalCoin = static_cast<Text *>(Helper::seekWidgetByName(static_cast<Layout *> (startTrips), "goalNum"));
	tripsgoalCoin->setText(StringUtils::toString(goalCoin));

	//当前关卡动画
	auto levelNode = static_cast<Text *>(Helper::seekWidgetByName(static_cast<Layout *> (startTrips), "levelNode"));
	auto nodeMove = createMove(SCREEN_MIDDLE(size.width, originSize.x), levelNode->getPosition().y);
	auto levelSquence = Sequence::create(EaseBackInOut::create(createMove(SCREEN_MIDDLE(size.width, originSize.x), levelNode->getPosition().y)),
		DelayTime::create(1), EaseBackInOut::create(createMove(size.width + levelNode->getSize().width, levelNode->getPosition().y)), nullptr);
	levelNode->runAction(levelSquence);

	//图标动画
	auto goalSymbol = static_cast<ImageView *> (Helper::seekWidgetByName(static_cast<Layout *> (startTrips), "goalSymbol"));
	auto symbolSquence = Sequence::create(EaseBackInOut::create(createMove(SCREEN_MIDDLE(size.width, originSize.x) - 170, goalSymbol->getPosition().y)),
		DelayTime::create(1), EaseBackInOut::create(createMove(SCREEN_MIDDLE(size.width, originSize.x) - 170, -100)), nullptr);
	goalSymbol->runAction(symbolSquence);

	//目标分数动画
	auto goalNode = static_cast<Text *> (Helper::seekWidgetByName(static_cast<Layout *> (startTrips), "goalNode"));
	auto goalNodeSquence = Sequence::create(EaseBackInOut::create(createMove(SCREEN_MIDDLE(size.width, originSize.x) + 30, goalNode->getPosition().y)),
		DelayTime::create(1), EaseBackInOut::create(createMove(SCREEN_MIDDLE(size.width, originSize.x) + 30, -100)),
		CCCallFuncN::create([=](Node* node) {
		startTrips->removeFromParentAndCleanup(true);
		miner->runAppear();
		miner->runAction(Sequence::create(MoveTo::create(2, Vec2(SCREEN_MIDDLE(size.width, originSize.x), size.height - 210)), CCCallFuncN::create([=](Ref *ref) {
			//倒计时牌下来
			timeD->gotoFrameAndPlay(0, false);

			//将钩子设置为刚体
			miner->setClawAxisToPhysics();

			//开始摆动钩子
			miner->runShakeClaw();

			//添加屏幕点击事件[放钩子事件]
			auto listener = EventListenerTouchOneByOne::create();

			
			listener->onTouchBegan = [=](Touch* touch, Event* event) {
				if (miner->getRopeChanging()) {
					miner->stopShakeAction();
					miner->runRopeThrow();
					//伸绳子声音
					if (UserDefault::getInstance()->getBoolForKey(IS_PLAY_EFFECT)) {
						SimpleAudioEngine::getInstance()->playEffect(PUSH_CLAW_MUSIC);
					}
				}

				return true;

			};
			_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

			//倒计时开始
			schedule(CC_SCHEDULE_SELECTOR(GameMain::timeDownCount), 1, GAME_LEFT_TIME(curLevel) - 1, 0);
			
		}), nullptr));

	}), nullptr);
	goalNode->runAction(goalNodeSquence);

}

//将金块,石头设置成刚体
void GameMain::setGoldStoneToBody(Vector<Node *> goldVector) {
	for (int i = 0; i < goldVector.size(); i++) {
		auto gold = goldVector.at(i);
		Size goldSize = gold->getContentSize();
		if ("smallGold" == gold->getName()) {//小金块
			goldSize = 0.4 * goldSize;
		
		}
		else if ("moddleGold" == gold->getName()) {//中金块
			goldSize = 0.6 * goldSize;
			
		}
		else if ("bigGold" == gold->getName()) {//大金块
			
		}
		else if ("smallstone" == gold->getName()) {//石头
			
		}
		else if ("bigstone" == gold->getName()) {//石头
		
		}
		auto body = PhysicsBody::createBox(goldSize);
		body->setCategoryBitmask(10);
		body->setContactTestBitmask(10);
		body->setCollisionBitmask(10);
		
		gold->setPhysicsBody(body);
	}
}


void GameMain::exitLevel() {
	
	//丢弃金币
	miner->dropGold();

	levelDown->gotoFrameAndPlay(30, 0, false);
	
	//矿工离场时轮子动画
	miner->runDisAppear();

	auto disAppearSeq = Sequence::create(MoveTo::create(0.5, Vec2(size.width + 100, size.height - 210)),
		CallFuncN::create([=](Ref *ref) {
			auto exitLeveltips = CSLoader::createNode("gameresult.csb");
			addChild(exitLeveltips);
			auto gameExit = static_cast<Text *>(Helper::seekWidgetByName(static_cast<Widget *>(exitLeveltips), "gameExit"));

			//提示语句
			auto seq = Sequence::create(EaseBackInOut::create(MoveTo::create(0.5, size / 2)),
				DelayTime::create(1),
				EaseBackInOut::create(MoveTo::create(0.5, Vec2(1.5 * size.width, size.height / 2))),
				CallFuncN::create([=](Ref *ref) {
				Director::getInstance()->replaceScene(GameMenu::createScene());
			}),
				nullptr);
			gameExit->runAction(seq);
	}), nullptr);
	miner->runAction(disAppearSeq);
}

void GameMain::timeDownCount(float df) {
	GAME_LEFT_TIME(curLevel)--;
	timeDownText->setText(StringUtils::toString(GAME_LEFT_TIME(curLevel)));
	if (GAME_LEFT_TIME(curLevel) <= 0) {

		//显示插屏广告
		GDTAD::showAd(1);

		gameResult();
		return;
	}
}

void GameMain::gameResult() {

	//丢弃金币
	miner->dropGold();

	levelDown->gotoFrameAndPlay(30, 0, false);

	//矿工离场时轮子动画
	miner->runDisAppear();

	auto disAppearSeq = Sequence::create(MoveTo::create(0.5, Vec2(size.width + 100, size.height - 210)),
		CallFuncN::create([=](Ref *ref) {
		auto exitLeveltips = CSLoader::createNode("gameresult.csb");
		addChild(exitLeveltips);
		auto gameFail = static_cast<Text *>(Helper::seekWidgetByName(static_cast<Widget *>(exitLeveltips), "gameFail"));
		auto userDef = UserDefault::getInstance();
		if (curGold < goalCoin) {
			//提示语句
			auto seq = Sequence::create(EaseBackInOut::create(MoveTo::create(0.5, Vec2(SCREEN_MIDDLE(size.width, originSize.x), gameFail->getPosition().y))),
				DelayTime::create(1),
				EaseBackInOut::create(MoveTo::create(0.5, Vec2(1.5 * size.width, gameFail->getPosition().y))),
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

			
			//提示语句
			auto seq = Sequence::create(EaseBackInOut::create(MoveTo::create(0.5, Vec2(size.width/2, gameSuccess->getPosition().y))),
				DelayTime::create(1),
				EaseBackInOut::create(MoveTo::create(0.5, Vec2(1.5 * size.width, gameSuccess->getPosition().y))),
				CallFuncN::create([=](Ref *ref) {
					//跳转到下一关
					Director::getInstance()->replaceScene(GameMain::createScene());
				}),
				nullptr);
			gameSuccess->runAction(seq);

			//提示语句
			auto nodeCoinSeq = Sequence::create(EaseBackInOut::create(MoveTo::create(0.5, Vec2(SCREEN_MIDDLE(size.width, originSize.x), nodeCoin->getPosition().y))),
				DelayTime::create(1),
				EaseBackInOut::create(MoveTo::create(0.5, Vec2(1.5 * size.width, nodeCoin->getPosition().y))), nullptr);
			nodeCoin->runAction(nodeCoinSeq);
		}
		
	}), nullptr);
	miner->runAction(disAppearSeq);
}

GameMain::~GameMain() {
	SimpleAudioEngine::getInstance()->stopAllEffects();
	_eventDispatcher->removeEventListener(pullcompleteListener);
	_eventDispatcher->removeEventListener(nextLevelListener);
	
	/*_eventDispatcher->removeCustomEventListeners("pullcomplete");*/
	_eventDispatcher->removeCustomEventListeners("gamePause"); 
	_eventDispatcher->removeCustomEventListeners("exitLevel");
}
