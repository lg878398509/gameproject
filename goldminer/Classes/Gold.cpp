#include "Gold.h"

Gold* Gold::create(std::string type) {
	Gold *gold = new Gold();
	if (gold && gold->init(type)) {
		gold->autorelease();
		return gold;
	}
	else {
		CC_SAFE_DELETE(gold);
		gold = NULL;
		return NULL;
	}
}

bool Gold::init(std::string type) {
	if (type == "smallGold") {
		if (!initWithSpriteFrameName("gold-1-1.png")) {
			return false;
		}
		setScale(0.3);
		weight = 3;
		value = 50;
	} 
	else if (type == "moddleGold") {
		if (!initWithSpriteFrameName("gold-0-0.png")) {
			return false;
		}
		setScale(0.6);
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
		setScale(0.5);
		weight = 7;
		value = 10;
	}
	else if (type == "bigstone") {
		if (!initWithSpriteFrameName("stone-0.png")) {
			return false;
		}
		weight = 8;
		value = 20;
	}
	return true;
}

int Gold::getWeight() {
	return this->weight;
}

int Gold::getValue() {
	return this->value;
}