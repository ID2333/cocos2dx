#include "Hero.h"
#include "Bullet.h"
#include "ui\UILoadingBar.h"
#include "Effect.h"
#include "Config.h"
using namespace ui;

#define LOAD Config::getInstance()->loadFileData

Hero::Hero(const std::string & heroType) :bulletPos(0, 0), m_heroType(heroType), m_isDeath(false),m_ATK(1)
{

}

Hero::~Hero()
{
	
}

Hero * Hero::create(const std::string & heroType)
{
	Hero *p = new Hero(heroType);
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

void Hero::hpShow()
{
	auto winSize = Director::getInstance()->getWinSize();
	Texture2D *texture = TextureCache::getInstance()->addImage("ship01.png");
	Sprite *life = Sprite::createWithTexture(texture, Rect(0, 0, 60, 38));
	life->setScale(0.6);
	life->setPosition(Point(30, winSize.height - 23));
	this->getParent()->addChild(life, 7777);
	Sprite *hp = Sprite::create("background.png");
	hp->setPosition(Point(90, winSize.height - 23));
	hp->setScaleX(0.8);
	hp->setScaleY(1.2);
	this->getParent()->addChild(hp, 1111);
	LoadingBar *hpBar = LoadingBar::create("progress.png");
	hpBar->setPosition(Point(90, winSize.height - 23));
	hpBar->setScaleX(0.8);
	hpBar->setScaleY(1.2);
	hpBar->setPercent(100);
	hpBar->setTag(30);
	this->getParent()->addChild(hpBar, 111111);

	Label *label = Label::create(Value(m_hp).asString(), "Arial", 16);
	label->setBlendFunc({ GL_SRC_ALPHA,GL_ONE });
	label->setPosition(Point(90, winSize.height - 23));
	this->getParent()->addChild(label, 111112,40);
}

void Hero::setHp(int hpValue)
{
	m_hp = hpValue;
	auto hpBar = static_cast<LoadingBar*>(this->getParent()->getChildByTag(30));
	auto label = static_cast<Label*>(this->getParent()->getChildByTag(40));
	hpBar->setPercent(m_hp / (m_hpMax / 100));
	label->setString(Value(m_hp).asString());
}

int Hero::getHpMax()
{
	return m_hpMax;
}

bool Hero::init()
{
	if (!Sprite::init()) {
		return false;
	}

	Texture2D *texture = TextureCache::getInstance()->addImage(m_heroType);
	this->initWithTexture(texture);

	//¾«ÁéÖ¡
	SpriteFrame *heroFrame1 = SpriteFrame::createWithTexture(texture, Rect(0, 0, 60, 38));
	SpriteFrame *heroFrame2 = SpriteFrame::createWithTexture(texture, Rect(60, 0, 60, 38));
	Vector<SpriteFrame*> animations;
	animations.pushBack(heroFrame1);
	animations.pushBack(heroFrame2);
	//¾«Áé¶¯»­
	Animation *animation = Animation::createWithSpriteFrames(animations, 0.1);
	Animate* animate = Animate::create(animation);
	this->runAction(RepeatForever::create(animate));

	m_hp = Value(Config::getInstance()->loadFileData("HP")).asInt();
	m_ATK = Value(Config::getInstance()->loadFileData("ATK")).asInt();

	if (Config::getInstance()->isHpAdd) m_hp += 100;
	if (Config::getInstance()->isATK) m_ATK += 1;
	m_hpMax = m_hp;

	return true;
}


void Hero::attack()
{
	this->schedule(schedule_selector(Hero::shootUpdate), 0.15);
}

void Hero::hurt(int value)
{
	auto hpBar = static_cast<LoadingBar*>(this->getParent()->getChildByTag(30));
	auto label = static_cast<Label*>(this->getParent()->getChildByTag(40));
	Effect *effect = Effect::create();
	auto obj = effect->hpEffect(this->getPosition(), value);
	this->getParent()->addChild(obj);
	m_hp -= value;
	if (m_hp > 0) {
		hpBar->setPercent(m_hp / (m_hpMax / 100));
		label->setString(Value(m_hp).asString());
	}
	else {
		hpBar->setPercent(0);
		label->setString("0");
	}
}

int Hero::hp()
{
	return m_hp;
}

Rect Hero::collideRect()
{
	Point pos = getPosition();
	Size cs = getContentSize();
	return Rect(pos.x - cs.width / 2, pos.y - cs.height / 2, cs.width, cs.height / 2);
}

void Hero::death()
{
	Effect *effect = Effect::create();
	effect->explode(this->getParent(), this->getPosition());
	m_isDeath = true;
	this->removeFromParentAndCleanup(true);
}

int Hero::isObject()
{
	return 0;
}

int Hero::getAKT()
{
	return m_ATK;
}

int Hero::getScoreValue()
{
	return 0;
}

int Hero::getCollideValue()
{
	return 15;
}

void Hero::shootUpdate(float dt)
{
	Bullet *bullet1 = Bullet::create(this, "W1.png", Point(13, 40));
	this->getParent()->addChild(bullet1);
	Bullet *bullet2 = Bullet::create(this, "W1.png", Point(-13, 40));
	this->getParent()->addChild(bullet2);

	if (Value(LOAD("BulletCount")).asInt() >= 4) {
		Bullet *bullet3 = Bullet::create(this, "W1.png", Point(25, 30));
		this->getParent()->addChild(bullet3);
		Bullet *bullet4 = Bullet::create(this, "W1.png", Point(-25, 30));
		this->getParent()->addChild(bullet4);
	}

}
