#include "EnemyAI.h"

EnemyAI::EnemyAI(EnemyType enemyType, Point heroPos):m_enemyType(enemyType),m_heroPos(heroPos)
{
}

EnemyAI::~EnemyAI()
{
}

Point EnemyAI::moveTo()
{
	Size winSize = Director::getInstance()->getWinSize();
	Point pos = m_heroPos;
	switch (m_enemyType.type)
	{
		case 0:
			pos.x = pos.x + CCRANDOM_0_1() * 10;
			pos.y = pos.y + 50;
			break;
		case 1:
			pos.x = pos.x + CCRANDOM_0_1() * 10;
			pos.y = pos.y + 50;
			break;
		case 2:
			pos.x = pos.x + CCRANDOM_0_1() * 10;
			pos.y = pos.y + 50;
			break;
		case 3:
			if (CCRANDOM_0_1() * 10 >= 5) {
				pos.x = m_heroPos.x + CCRANDOM_0_1() * 50;
				pos.y = winSize.height - 200 - CCRANDOM_0_1() * 100;
			}
			pos.x = 10 + CCRANDOM_0_1() * winSize.width - 10;
			pos.y = winSize.height - 200;
			break;
		case 4:
			if (CCRANDOM_0_1() * 10 >= 4) {
				pos.x = m_heroPos.x + CCRANDOM_0_1() * 30;
				pos.y = winSize.height - 150 - CCRANDOM_0_1() * 100;
			}
			pos.x = 10 + CCRANDOM_0_1() * winSize.width - 10;
			pos.y = winSize.height - 150 + CCRANDOM_0_1() * 50;
			break;
		case 5:
			if (CCRANDOM_0_1() * 10 >= 3) {
				pos.x = m_heroPos.x + CCRANDOM_0_1() * 10;
				pos.y = winSize.height - 100 + CCRANDOM_0_1() * 100;
			}
			pos.x = 10 + CCRANDOM_0_1() * winSize.width - 10;
			pos.y = winSize.height - 100 + +CCRANDOM_0_1() * 100;
			break;
	default:
		break;
	}
	return pos;
}


