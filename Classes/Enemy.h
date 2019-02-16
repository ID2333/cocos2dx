
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

	//�жϵ�ǰ����
	virtual int isObject();
	//����
	virtual void attack();
	//����
	virtual void hurt(int value);
	//����
	virtual int hp();
	//����
	virtual void death();
	//��ײ���
	virtual Rect collideRect();
	//��ȡ������
	virtual int getAKT();
	//����
	virtual int getScoreValue();
	//��ײ�˺�
	virtual int getCollideValue();
};

#endif