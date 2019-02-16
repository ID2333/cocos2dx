
#ifndef _GameLevelEditors_H_
#define _GameLevelEditors_H_

#include "cocos2d.h"
#include "Enemy.h"
USING_NS_CC;

class GameLevelEditors : public Node
{
private:
	int m_level;
public:
	float m_enemyCountUpdate;

	GameLevelEditors(int value);
	~GameLevelEditors();

	Enemy* createEnemy(std::vector<EnemyType> enemyType,Point heroPos);

};
#endif // !_GameLevelEditors_H_

