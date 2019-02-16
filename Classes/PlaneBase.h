
#ifndef _PlaneBase_H_
#define _PlaneBase_H_

#include "cocos2d.h"
using namespace cocos2d;

class PlaneBase : public Sprite
{
public:
	//攻击
	virtual void attack() = 0;
	//受伤
	virtual void hurt(int value) = 0;
	//生命
	virtual int hp() = 0;
	//死亡
	virtual void death() = 0;
	//碰撞范围
	virtual Rect collideRect() = 0;
	//获取对象 0:英雄 1:敌机 3:boss
	virtual int isObject() = 0;
	//获取攻击力
	virtual int getAKT() = 0;
	//分数
	virtual int getScoreValue() = 0;
	//碰撞伤害
	virtual int getCollideValue() = 0;
};
#endif // !_PlaneBase_H_
