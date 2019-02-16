#include "HeroSkill.h"
#include "Config.h"

#define LOAD Config::getInstance()->loadFileData

HeroSkill::HeroSkill(std::string str,Hero *hero):m_heroType(str),m_hero(hero)
{
}

HeroSkill::~HeroSkill()
{
}

HeroSkill * HeroSkill::create(std::string str, Hero *hero)
{
	auto p = new HeroSkill(str, hero);
	if (p && p->init())
	{
		p->autorelease();
		return p;
	}
	else {
		delete p;
		p = NULL;
		return NULL;
	}
}

bool HeroSkill::init()
{
	if (!Sprite::init()) {
		return false;
	}
	Skill_1_Time = Value(LOAD("Skill_1_Time")).asInt();
	Skill_1_CD = Value(LOAD("Skill_1_CD")).asInt();
	Skill_2_Time = Value(LOAD("Skill_2_Time")).asInt();
	Skill_2_CD = Value(LOAD("Skill_2_CD")).asInt();
	return true;
}

void HeroSkill::loadSkill()
{
	//¼¼ÄÜ
	Button *skill_1 = Button::create("tenfold.png");
	skill_1->setPosition(Point(40, 40));
	skill_1->setScale(0.35);
	skill_1->setTag(10);
	this->getParent()->addChild(skill_1);
	skill_1->addClickEventListener(CC_CALLBACK_1(HeroSkill::skillCallBack, this));

	int level = Value(LOAD("Skill_2_Level")).asInt();
	if (level > 0) {
		Button *skill_2 = Button::create("defense.png");
		skill_2->setPosition(Point(40, 100));
		skill_2->setScale(0.35);
		skill_2->setTag(20);
		this->getParent()->addChild(skill_2);
		skill_2->addClickEventListener(CC_CALLBACK_1(HeroSkill::skillCallBack, this));
	}
}

void HeroSkill::skillCallBack(Object *pSender)
{
	std::string skillName;
	int tag = static_cast<Node*>(pSender)->getTag();
	ProgressTo *progressto = NULL;
	if (!m_hero->m_isDeath) {
		if (tag == 10)
		{
			skillName = "tenfold.png";
			m_hero->unschedule(schedule_selector(Hero::shootUpdate));
			m_hero->schedule(schedule_selector(Hero::shootUpdate), 0.015f);
			m_hero->runAction(Sequence::create(DelayTime::create(Skill_1_Time), CallFunc::create([&]() {
				m_hero->unschedule(schedule_selector(Hero::shootUpdate));
				m_hero->schedule(schedule_selector(Hero::shootUpdate), 0.15f);
			}), NULL));
			progressto = ProgressTo::create(Skill_1_CD, 0);
		}
		if (tag == 20)
		{
			skillName = "defense.png";
			m_hero->setColor(Color3B(0,0,0));
			Config::getInstance()->defenseSkill = true;
			m_hero->runAction(Sequence::create(DelayTime::create(Skill_2_Time), CallFunc::create([&]() {
				m_hero->setColor(Color3B(255, 255, 255));
				Config::getInstance()->defenseSkill = false;
			}), NULL));
			progressto = ProgressTo::create(Skill_2_CD, 0);
		}
		Button * btn = static_cast<Button*>(pSender);
		btn->setEnabled(false);
		//ÀäÈ´¶¯»­
		Sprite *sprite = Sprite::create(skillName);
		sprite->setOpacity(90);
		sprite->setColor(Color3B(0, 0, 0));
		auto cd = ProgressTimer::create(sprite);
		cd->setType(ProgressTimer::Type::RADIAL);
		cd->setPosition(btn->getPosition());
		cd->setPercentage(100.0f);
		cd->setScale(0.35);
		cd->setReverseProgress(true);
		this->getParent()->addChild(cd);
		auto callfunc = CallFuncN::create([=](Node *node) {
			sprite->removeFromParentAndCleanup(true);
			cd->removeFromParentAndCleanup(true);
			btn->setEnabled(true);
		});
		cd->runAction(Sequence::create(progressto, callfunc, NULL));
	}
}
