
#ifndef _EnemyAI_H_
#define _EnemyAI_H_

#include "cocos2d.h"
#include "Config.h"
USING_NS_CC;

class EnemyAI : public Sprite
{
private:
	EnemyType m_enemyType;
	Point m_heroPos;
public:
	EnemyAI(EnemyType enemyType, Point heroPos);
	~EnemyAI();

	Point moveTo();
};

#endif
