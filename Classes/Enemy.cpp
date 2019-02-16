#include "Enemy.h"
#include "Bullet.h"
#include "EnemyAI.h"
#include "Effect.h"

Enemy::Enemy(EnemyType enemy,Point heroPos):m_enemyType(enemy),m_isDeath(false),m_heroPos(heroPos)
{

}

Enemy::~Enemy()
{

}

Enemy * Enemy::create(EnemyType enemy, Point heroPos)
{
	Enemy *p = new Enemy(enemy,heroPos);
	if(p && p->init())
	{
		p->autorelease();
		return p;
	}
	else 
	{
		delete p;
		p = NULL;
		return NULL;
	}
}

bool Enemy::init()
{
	m_hp = m_enemyType.hp;
	m_ATK = m_enemyType.ATK;
	m_scoreValue = m_enemyType.scoreValue;
	m_moveTime = m_enemyType.moveTime;
	m_enemyPos = this->getPosition();
	m_collideAKT = m_enemyType.moveType;
	if (!Sprite::init()) {
		return false;
	}
	Size winSize = Director::getInstance()->getWinSize();
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Enemy.plist");
	this->initWithSpriteFrameName(m_enemyType.textureName);
	this->setPosition(Point(CCRANDOM_0_1() * winSize.width, winSize.height + 150));
	enemyCount.pushBack(this);
	this->schedule(schedule_selector(Enemy::UpdateMove), m_moveTime);
	return true;
}

void Enemy::UpdateMove(float dt)
{
	if (!m_isDeath) {
		EnemyAI AI(m_enemyType, m_heroPos);
		MoveTo *moveTo = MoveTo::create(dt, AI.moveTo());
		this->runAction(moveTo);
		attack();
	}
}

int Enemy::isObject()
{
	return 1;
}

void Enemy::attack()
{
	Point enemyPos = this->getPosition();
	Bullet *bullet = Bullet::create(this,"W2.png",Point(enemyPos.x,enemyPos.y - 10));
	this->getParent()->addChild(bullet);
}

void Enemy::hurt(int value)
{
	Effect *effect = Effect::create();
	auto obj = effect->hpEffect(this->getPosition(), value);
	this->getParent()->addChild(obj);
	if (m_hp > 0)
	{
		m_hp -= value;
	}
}

int Enemy::hp()
{
	return m_hp;
}

void Enemy::death()
{
	Effect *effect = Effect::create();
	effect->explode(this->getParent(),this->getPosition());
	m_isDeath = true;
	this->removeFromParent();
	enemyCount.eraseObject(this);
}

Rect Enemy::collideRect()
{
	return this->getBoundingBox();
}

int Enemy::getAKT()
{
	return m_ATK;
}

int Enemy::getScoreValue()
{
	return m_scoreValue;
}

int Enemy::getCollideValue()
{
	return m_collideAKT;
}

