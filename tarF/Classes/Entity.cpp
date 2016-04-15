#include "Entity.h"

Entity::Entity() {
	m_sprite = NULL;
	m_sname = "";
	m_hp = 1;
	m_defense = 1;
	m_ispeed = 1;
	m_level = 1;

	m_isdead = false;

}
Entity::~Entity() {

}

void Entity::setSprite(Sprite *sprite) {
	if (this->m_sprite != NULL)
	{
		m_sprite->removeFromParentAndCleanup(true);
	}

	this->m_sprite = sprite;
	this->addChild(m_sprite);

	Size size = m_sprite->getContentSize();
	this->setContentSize(size);

	onBindSprite();
}

Sprite* Entity::getSprite() {
	return this->m_sprite;
}

void Entity::hurtMe(int iHurtValue) {
	if (m_isdead)
	{
		return;
	}

	if (iHurtValue <= getDefense()) {
		iHurtValue = 1;
	}

	int curHp = getHp();
	int afterHp = curHp - iHurtValue;
	
	onHurt(iHurtValue);

	if (afterHp > 0)
	{
		setHp(afterHp);
	}
	else {
		m_isdead = true;
		onDead();
	}

}

bool Entity::isDead() {
	return this->m_isdead;
}


void Entity::onDead() {

}
void Entity::onBindSprite() {

}
void Entity::onHurt(int iHurtValue) {

}
