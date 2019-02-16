
#ifndef _Boss_H_
#define _Boss_H_

#include "cocos2d.h"
#include "PlaneBase.h"
USING_NS_CC;

class Boss : public PlaneBase
{
private:
	int m_level;
	int m_hp;
	int m_AKT;
	int m_hpMax;
	std::string m_bossName;
public:
	Boss(int m_level);
	~Boss();

	static Boss *create(int level);
	virtual bool init();
	void update(float dt);
	void hpShow();
	void bossAction(std::string &boosName);

	virtual void attack();
	virtual void hurt(int value);
	virtual int hp();
	virtual void death();
	virtual Rect collideRect();
	virtual int isObject();
	virtual int getAKT();
	virtual int getScoreValue();
	virtual int getCollideValue();
};

#endif
