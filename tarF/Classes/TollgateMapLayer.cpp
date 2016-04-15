#include "TollgateMapLayer.h"
#include "SimpleAudioEngine.h"

TollgateMapLayer::TollgateMapLayer() {
	m_iCurLevel = 1;
}

TollgateMapLayer::~TollgateMapLayer() {

}

bool TollgateMapLayer::init() {
	bool bRet = false;

	do {
		loadConfig();

		bRet = true;
	} while (0);

	return true;
}

void TollgateMapLayer::loadConfig() {
	Size size = Director::getInstance()->getVisibleSize();

	auto musicPath = StringUtils::format("music/tollgate_%d.mp3", m_iCurLevel).c_str();
	CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic(musicPath,true);

	std::string sBG = StringUtils::format("tollgate/level_%d.jpg", m_iCurLevel);
	Sprite *sprite = Sprite::create(sBG.c_str());
	sprite->setPosition(size.width/2, size.height/2);
	this->addChild(sprite, 1);

}