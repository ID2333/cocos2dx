#include "Boss.h"
#include "Config.h"
#include "Effect.h"
#include "GameOver.h"
#include "ui\UILoadingBar.h"
using namespace ui;

Boss::Boss(int level):m_level(level)
{
	if (!Config::getInstance()->isBossHp) {
		m_hp = 500 + (m_level - 1) * 250;
	}
	else{
		m_hp = (500 + (m_level - 1) * 250) * 0.8;
	}
	m_hpMax = 500 + (m_level - 1) * 250;
	m_AKT = 10;
}

Boss::~Boss()
{
}

Boss * Boss::create(int level)
{
	Boss *p = new Boss(level);
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

bool Boss::init()
{
	if (!Sprite::init()) {
		return false;
	}
	Size winSize = Director::getInstance()->getWinSize();

	m_bossName = "bossfirst.png";
	if (m_level > 5) m_bossName = "boss_1.png";

	Texture2D *BossSprite = TextureCache::getInstance()->addImage(m_bossName);
	this->initWithTexture(BossSprite);
	enemyCount.pushBack(this);
	this->setPosition(winSize.width / 2, winSize.height + 300);
	bossAction(m_bossName);
	return true;
}

void Boss::hpShow()
{
	auto winSize = Director::getInstance()->getWinSize();
	LabelBMFont *bossLabel = LabelBMFont::create("Boss", "Font/bitmapFontTest.fnt");
	bossLabel->setScale(0.5);
	bossLabel->setPosition(Point(50, winSize.height - 50));
	this->getParent()->addChild(bossLabel, 5555);

	Sprite *hp = Sprite::create("background.png");
	hp->setPosition(Point(winSize.width / 2, winSize.height - 50));
	hp->setScale(1.5);
	this->getParent()->addChild(hp, 1111);

	LoadingBar *hpBar = LoadingBar::create("progress.png");
	hpBar->setPosition(Point(winSize.width / 2, winSize.height - 50));
	hpBar->setScale(1.5);
	hpBar->setPercent(100);
	this->getParent()->addChild(hpBar, 111111, 50);

	std::string str = Value(m_hp).asString();
	int hpMaxToi = m_hpMax * 0.2;
	std::string hpStr = Value(hpMaxToi).asString();
	if (Config::getInstance()->isBossHp) str += "(-" + hpStr + ")";
	Label *label = Label::create(str, "Arial", 19);
	label->setBlendFunc({ GL_SRC_ALPHA,GL_ONE });
	label->setPosition(Point(winSize.width / 2, winSize.height - 50));
	this->getParent()->addChild(label, 111112, 60);
}

void Boss::bossAction(std::string & boosName)
{
	Size winSize = Director::getInstance()->getWinSize();
	if (boosName == "bossfirst.png")
	{
		MoveTo *moveTo1 = MoveTo::create(2 - m_level * 0.2, Point(50, winSize.height - 100));
		MoveTo *moveTo2 = MoveTo::create(2 - m_level * 0.2, Point(winSize.width - 50, winSize.height - 100));
		auto action = Sequence::create(moveTo1, moveTo2, NULL);
		this->runAction(RepeatForever::create(action));
		this->schedule(schedule_selector(Boss::update), 1 - m_level * 0.1);

		if (m_level == 1) this->setColor(Color3B(255, 215, 0));
		if (m_level == 2) this->setColor(Color3B(0, 0, 255));
		if (m_level == 3) this->setColor(Color3B(54, 54, 54));
		if (m_level == 4) this->setColor(Color3B(255, 0, 0));
	}
	if (boosName == "boss_1.png")
	{
		MoveTo *moveTo = MoveTo::create(1, Point(winSize.width / 2, winSize.height - 100));
		this->runAction(moveTo);
		auto rotate1 = RotateBy::create(2 - m_level * 0.15, 360);
		this->runAction(RepeatForever::create(rotate1));
		this->schedule(schedule_selector(Boss::update), 2 - m_level * 0.15);

		if (m_level == 6) this->setColor(Color3B(255, 215, 0));
		if (m_level == 7) this->setColor(Color3B(0, 0, 255));
		if (m_level == 8) this->setColor(Color3B(54, 54, 54));
		if (m_level == 9) this->setColor(Color3B(255, 0, 0));
	}
}

void Boss::update(float dt)
{
	if (m_bossName == "boss_1.png") {
		auto MoveTo = MoveTo::create(2 - m_level * 0.15,Point(CCRANDOM_0_1() * 320,CCRANDOM_0_1() * 480));
		this->runAction(MoveTo);
	}
	if (m_bossName == "bossfirst.png") {
		attack();
	}
}

void Boss::attack()
{
	Point pos = this->getPosition();
	Bullet *bullet1 = Bullet::create(this, "W2.png", Point(pos.x,pos.y - 20));
	this->getParent()->addChild(bullet1);
	Bullet *bullet2 = Bullet::create(this, "W2.png", Point(pos.x - 20, pos.y - 20));
	this->getParent()->addChild(bullet2);
	Bullet *bullet3 = Bullet::create(this, "W2.png", Point(pos.x + 20, pos.y - 20));
	this->getParent()->addChild(bullet3);
	Bullet *bullet4 = Bullet::create(this, "W2.png", Point(pos.x + 40, pos.y - 20));
	this->getParent()->addChild(bullet4);
	Bullet *bullet5 = Bullet::create(this, "W2.png", Point(pos.x - 40, pos.y - 20));
	this->getParent()->addChild(bullet5);

}

void Boss::hurt(int value)
{
	
	auto hpBar = static_cast<LoadingBar*>(this->getParent()->getChildByTag(50));
	auto label = static_cast<Label*>(this->getParent()->getChildByTag(60));
	std::string str;
	int hpMaxToi = m_hpMax * 0.2;
	std::string hpStr = Value(hpMaxToi).asString();
	if (Config::getInstance()->isBossHp) str = "(-" + hpStr + ")";
	m_hp -= value;
	Effect *effect = Effect::create();
	auto obj = effect->hpEffect(this->getPosition(), value);
	this->getParent()->addChild(obj);
	if (m_hp > 0) {
		hpBar->setPercent(m_hp / (m_hpMax / 100));
		label->setString(Value(m_hp).asString() + str);
	}
	else {
		hpBar->setPercent(0);
		label->setString("0" + str);
	}
	
}

int Boss::hp()
{
	return m_hp;
}

void Boss::death()
{
	Effect *effect = Effect::create();
	effect->explode(this->getParent(), this->getPosition());
	enemyCount.eraseObject(this);
	this->removeFromParent(); 
}



Rect Boss::collideRect()
{
	return this->getBoundingBox();
}

int Boss::isObject()
{
	return 3;
}

int Boss::getAKT()
{
	return m_AKT;
}

int Boss::getScoreValue()
{
	return 5000 + (m_level - 1) * 5000;
}

int Boss::getCollideValue()
{
	return 1000;
}
