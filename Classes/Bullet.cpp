#include "Bullet.h"
#include "Config.h"
#include "Effect.h"

Bullet::Bullet(PlaneBase *plane, const std::string & bulletType,Point pos):m_plane(plane), m_bulletName(bulletType),m_pos(pos),m_isDeath(false)
{
	
}

Bullet::~Bullet()
{
	
}

bool Bullet::init()
{
	if (!Sprite::init()) {
		return false;
	}
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("bullet.plist");
	this->initWithSpriteFrameName(m_bulletName);
	Point heroPos = m_plane->getPosition();
	m_object = m_plane->isObject();
	m_AKT = m_plane->getAKT();
	switch (m_plane->isObject())
	{
	case 0:
		//玩家子弹
		this->setPosition(Point(heroPos.x + m_pos.x, heroPos.y + m_pos.y));
		this->setBlendFunc({ GL_SRC_ALPHA,GL_ONE });
		heroBullet.pushBack(this);
		this->schedule(schedule_selector(Bullet::updatePos), 0.001);
		break;
	case 1:
		//敌人子弹
		this->setPosition(m_pos);
		this->setBlendFunc({ GL_SRC_ALPHA,GL_ONE });
		enemyBullet.pushBack(this);
		this->schedule(schedule_selector(Bullet::updatePos), 0.005);
		break;
	case 3:
		//Boss子弹
		this->setPosition(m_pos);
		this->setBlendFunc({ GL_SRC_ALPHA,GL_ONE });
		enemyBullet.pushBack(this);
		this->schedule(schedule_selector(Bullet::updatePos), 0.006);
		break;
	}
	return true;
}

Bullet * Bullet::create(PlaneBase *plane, const std::string & bulletType,Point pos)
{
	Bullet *p = new Bullet(plane,bulletType,pos);
	if (p && p->init()) {
		p->autorelease();
		return p;
	}
	else {
		delete p;
		p = NULL;
		return NULL;
	}
}

void Bullet::death()
{
	if (!m_isDeath) {
		m_isDeath = true;
		Effect *effect = Effect::create();
		effect->bulletExplode(this->getParent(), this->getPosition());
		
		switch (m_object)
		{
		case 0:
			heroBullet.eraseObject(this);
			break;
		case 1:
			enemyBullet.eraseObject(this);
			break;
		case 3:
			enemyBullet.eraseObject(this);
			break;
		}
		
		this->removeFromParent();
	}
}

int Bullet::getAKT()
{
	return m_AKT;
}

bool Bullet::isdead()
{
	return m_isDeath;
}

void Bullet::updatePos(float dt)
{
	if (!m_isDeath) {
		float y = this->getPositionY();
		float x = this->getPositionX();
		switch (m_object)
		{
		case 0:
			y += 1;
			break;
		case 1:
			y -= 1;
			break;
		case 3:
			y -= 1;
			break;
		}
		this->setPositionY(y);
		if (y > 500 || y < -20)
			death();
	}
}



