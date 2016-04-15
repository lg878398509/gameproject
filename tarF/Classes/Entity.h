/*
    文件名：    TowerPos.h
    描　述：    炮塔坐标对象
    创建人：    
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

	/*实体id*/
	CC_SYNTHESIZE(int, m_id, Id);
	/*实体模型id[资源id]*/
	CC_SYNTHESIZE(int, m_model_id, ModelId);
	/*实体名称*/
	CC_SYNTHESIZE(std::string, m_sname, Sname);
	/*实体血量*/
	CC_SYNTHESIZE(int, m_hp, Hp);
	/*防御*/
	CC_SYNTHESIZE(int, m_defense, Defense);
	/*速度*/
	CC_SYNTHESIZE(int, m_ispeed, iSpeed);
	/*等级*/
	CC_SYNTHESIZE(int, m_level, Level);

	bool m_isdead;
};

#endif