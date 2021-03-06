#include "Gold.h"

Gold* Gold::create(std::string type, Size size) {
	Gold *gold = new Gold();
	if (gold && gold->init(type, size)) {
		gold->autorelease();
		return gold;
	}
	else {
		CC_SAFE_DELETE(gold);
		gold = NULL;
		return NULL;
	}
}

bool Gold::init(std::string type, Size size) {
	if (type == "smallGold") {
		if (!initWithSpriteFrameName("gold-1-1.png")) {
			return false;
		}
		weight = 3;
		value = 50;
	} 
	else if (type == "moddleGold") {
		if (!initWithSpriteFrameName("gold-0-0.png")) {
			return false;
		}
		weight = 4;
		value = 250;
	}
	else if (type == "bigGold") {
		if (!initWithSpriteFrameName("gold-0-0.png")) {
			return false;
		}
		weight = 5;
		value = 500;
	}
	else if (type == "smallstone") {
		if (!initWithSpriteFrameName("stone-0.png")) {
			return false;
		}
		weight = 7;
		value = 10;
	}
	else if (type == "bigstone") {
		if (!initWithSpriteFrameName("stone-1.png")) {
			return false;
		}
		weight = 8;
		value = 20;
	}
	
	setScale(size.width / this->getContentSize().width);
	return true;
}

int Gold::getWeight() {
	return this->weight;
}

int Gold::getValue() {
	return this->value;
}