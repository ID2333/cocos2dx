
#ifndef _Bullet_H_
#define _Bullet_H_

#include "cocos2d.h"
#include "Hero.h"
USING_NS_CC;

class Bullet : public Sprite
{
private:
	PlaneBase * m_plane;
	std::string m_bulletName;
	Point m_pos;
	int m_object;
	int m_AKT;
	bool m_isDeath;
public:
	Bullet(PlaneBase *plane, const std::string &bulletType,Point pos);
	~Bullet();
	static Bullet* create(PlaneBase *plane,const std::string &bulletType,Point pos);
	virtual bool init();

	void death();
	int getAKT();
	bool isdead();
	void updatePos(float dt);
};

#endif
