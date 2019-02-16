
#ifndef _Hero_H_
#define _Hero_H_

#include "cocos2d.h"
#include "PlaneBase.h"
USING_NS_CC;

class Hero : public PlaneBase
{
private:
	Sprite *m_hero;
	std::string m_heroType;
	Point bulletPos;
	int m_hp;
	int m_ATK;
	int m_hpMax;
public:
	bool m_isDeath;

	Hero(const std::string &heroType);
	~Hero();
	virtual bool init();
	static Hero* create(const std::string &heroType);
	void hpShow();
	void setHp(int hpValue);
	int getHpMax();

	virtual void attack();
	virtual void hurt(int value);
	virtual int hp();
	virtual Rect collideRect();
	virtual void death();
	virtual int isObject();
	virtual int getAKT();
	virtual int getScoreValue();
	virtual int getCollideValue();
	void shootUpdate(float dt);
};
#endif // !_Hero_H_

