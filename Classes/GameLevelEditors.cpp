#include "GameLevelEditors.h"


GameLevelEditors::GameLevelEditors(int value):m_level(value)
{
	float time = ((float)m_level - 1.0f) / 10.0f;
	if (m_level <= 10) m_enemyCountUpdate = 1.0f - time;
}

GameLevelEditors::~GameLevelEditors()
{
	 
}


Enemy * GameLevelEditors::createEnemy(std::vector<EnemyType> enemyType, Point heroPos)
{
	Enemy *enemy = NULL;
	if (m_level <= 5) {
		if (CCRANDOM_0_1() * 10 > 5) {
			enemy = Enemy::create(enemyType[3], heroPos);
		}
		else {
			enemy = Enemy::create(enemyType[4], heroPos);
		}
	}
	if (m_level > 5) {
		int num = CCRANDOM_0_1() * 10;
		if (num >= 9) {
			enemy = Enemy::create(enemyType[5], heroPos);
		}
		else if(num >= 7){
			enemy = Enemy::create(enemyType[4], heroPos);
		}
		else if (num >= 3) {
			enemy = Enemy::create(enemyType[3], heroPos);
		}
		else {
			enemy = Enemy::create(enemyType[num], heroPos);
		}
	}
	return enemy;
}



