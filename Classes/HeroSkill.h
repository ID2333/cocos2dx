
#ifndef _HeroSkill_H_
#define _HeroSkill_H_

#include "cocos2d.h"
#include "Hero.h"
#include "ui\UIButton.h"
using namespace ui;
USING_NS_CC;

class HeroSkill : public Sprite
{
private:
	std::string m_heroType;
	Hero *m_hero;
	int Skill_1_Time;
	int Skill_1_CD;
	int Skill_2_Time;
	int Skill_2_CD;
public:
	HeroSkill(std::string str, Hero *hero);
	~HeroSkill();

	static HeroSkill *create(std::string str, Hero *hero);
	virtual bool init();

	void loadSkill();
	void skillCallBack(Object *pSender);
};

#endif
