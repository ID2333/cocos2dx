
#ifndef _Enemy_H_
#define _Enemy_H_

#include "cocos2d.h"
#include "PlaneBase.h"
#include "Config.h"
USING_NS_CC;

class Enemy : public PlaneBase
{
private:
	EnemyType m_enemyType;
	int m_hp;
	int m_ATK;
	int m_moveTime;
	bool m_isDeath;
	int m_scoreValue;
	int m_collideAKT;
	Point m_enemyPos;
	Point m_heroPos;
public:

	Enemy(EnemyType enemy,Point heroPos);
	~Enemy();
	static Enemy* create(EnemyType enemy,Point heroPos);
	virtual bool init();
	void UpdateMove(float dt);

	//判断当前对象
	virtual int isObject();
	//攻击
	virtual void attack();
	//受伤
	virtual void hurt(int value);
	//生命
	virtual int hp();
	//死亡
	virtual void death();
	//碰撞体积
	virtual Rect collideRect();
	//获取攻击力
	virtual int getAKT();
	//分数
	virtual int getScoreValue();
	//碰撞伤害
	virtual int getCollideValue();
};

#endif