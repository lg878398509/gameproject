/*
    �ļ�����    TowerPos.h
    �衡����    �����������
    �����ˣ�    
*/

#ifndef _ENTITY_H_
#define _ENTITY_H_

#include "cocos2d.h"
USING_NS_CC;


class Entity : public Node {
public:
	Entity();
	~Entity();

	void setSprite(Sprite *sprite);

	Sprite* getSprite();

	void hurtMe(int iHurtValue);
	bool isDead();
protected:
	virtual void onDead();
	virtual void onBindSprite();
	virtual void onHurt(int iHurtValue);
private:
	Sprite *m_sprite;

	/*ʵ��id*/
	CC_SYNTHESIZE(int, m_id, Id);
	/*ʵ��ģ��id[��Դid]*/
	CC_SYNTHESIZE(int, m_model_id, ModelId);
	/*ʵ������*/
	CC_SYNTHESIZE(std::string, m_sname, Sname);
	/*ʵ��Ѫ��*/
	CC_SYNTHESIZE(int, m_hp, Hp);
	/*����*/
	CC_SYNTHESIZE(int, m_defense, Defense);
	/*�ٶ�*/
	CC_SYNTHESIZE(int, m_ispeed, iSpeed);
	/*�ȼ�*/
	CC_SYNTHESIZE(int, m_level, Level);

	bool m_isdead;
};

#endif