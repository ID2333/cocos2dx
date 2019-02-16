#include "GameScene.h"
#include "ui\UILoadingBar.h"
#include "Enemy.h"
#include "Config.h"
#include "Effect.h"
#include "Boss.h"
#include "GameOver.h"
#include "ui\UIButton.h"
#include "HeroSkill.h"
#include "GameMenu.h"
#include "SimpleAudioEngine.h"
using namespace ui;

#define LOAD Config::getInstance()->loadFileData
#define SAVE Config::getInstance()->fileSave

GameScene::GameScene():gameLevel(Config::getInstance()->level),m_Boss(NULL)
{
	
}

GameScene::~GameScene()
{

}

void GameScene::onExit()
{
	Layer::onExit();
	heroBullet.clear();
	enemyBullet.clear();
	enemyCount.clear();
}

Scene * GameScene::createScene()
{
	auto scene = Scene::create();
	auto layer = GameScene::create();
	scene->addChild(layer);
	return scene;
}

bool GameScene::init()
{
	if (!Layer::init()) {
		return false;
	}
	//加载效果
	Effect::loadExplosion();
	
	//触摸事件
	m_isOver = false;
	auto touch = EventListenerTouchOneByOne::create();
	touch->onTouchBegan = [&](Touch *touch, Event *event) {return true; };
	touch->onTouchMoved = [&](Touch *touch, Event *event)
	{
		if (!m_isOver) {
			Point pos = touch->getDelta();
			Point currentPos = m_hero->getPosition();
			currentPos.add(pos);
			currentPos = currentPos.getClampPoint(Point(0, 0), Point(winSize.width, winSize.height));
			m_hero->setPosition(currentPos);
		}
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touch, this);

	winSize = Director::getInstance()->getWinSize();

	//背景
	std::string bgStr;
	if (Config::getInstance()->level > 5) { 
		bgStr = "backgroud.png"; 
	}
	else {
		bgStr = "bg01.jpg";
	}
    m_bg1 = Sprite::create(bgStr);
	m_bg1->setPosition(Point(winSize.width / 2, m_bg1->getContentSize().height / 2));
	this->addChild(m_bg1);
	m_bg2 = Sprite::create(bgStr);
	m_bg2->setPosition(Point(winSize.width / 2, m_bg1->getContentSize().height + m_bg1->getContentSize().height / 2));
	this->addChild(m_bg2);

	m_TiledMap1 = TMXTiledMap::create("level01.tmx");
	m_TiledMap2 = TMXTiledMap::create("level01.tmx");
	m_TiledMap2->setPosition(0, m_TiledMap2->getContentSize().height);
	this->addChild(m_TiledMap1);
	this->addChild(m_TiledMap2);

	//分数
	m_scroe = LabelBMFont::create("Score: 0","arial-14.fnt");
	m_scroe->setAnchorPoint(Point(1,0));
	m_scroe->setPosition(Point(winSize.width - 5,winSize.height - 30));
	m_scroe->setAlignment(TextHAlignment::RIGHT);
	this->addChild(m_scroe,99999);

	//距离
	m_distance = LabelBMFont::create("0 km", "arial-14.fnt");
	m_distance->setAnchorPoint(Point(1, 0));
	m_distance->setPosition(Point(winSize.width - 5, winSize.height - 50));
	m_distance->setAlignment(TextHAlignment::RIGHT);
	this->addChild(m_distance, 88888);

	//当前关卡
	int num = Config::getInstance()->level;
	LabelBMFont *level = LabelBMFont::create("Level_" + Value(num).asString(),"arial-14.fnt");
	level->setPosition(Point(winSize.width / 2 + 20,winSize.height - 23));
	level->setScale(1.2);
	level->setColor(Color3B(0, 255, 0));
	this->addChild(level, 999);
	
	//飞机
	m_hero = Hero::create("ship01.png");
	m_hero->setPosition(Point(winSize.width / 2, 50));
	m_hero->setTag(1);
	this->addChild(m_hero);
	m_hero->attack();
	m_hero->hpShow();

	//加载技能
	HeroSkill *heroSkill = HeroSkill::create("ship01.png", m_hero);
	this->addChild(heroSkill);
	heroSkill->loadSkill();

	this->schedule(schedule_selector(GameScene::mapUpdate));
	this->schedule(schedule_selector(GameScene::enemyCountUpdate), gameLevel.m_enemyCountUpdate);
	this->scheduleUpdate();
	
	//返回按钮
	Button *menuBtn = Button::create("bgk.png");
	menuBtn->addClickEventListener(CC_CALLBACK_1(GameScene::pauseCallBack, this));
	menuBtn->setPosition(Point(winSize.width / 2,winSize.height / 2));
	menuBtn->setTitleText("Menu");
	menuBtn->setTitleFontSize(21);
	menuBtn->setColor(Color3B(135, 206, 250));
	menuBtn->setVisible(false);
	menuBtn->setEnabled(false);
	this->addChild(menuBtn,11,2333);

	//暂停按钮
	Button *pauseBtn = Button::create("pause.png");
	pauseBtn->addClickEventListener(CC_CALLBACK_1(GameScene::pauseCallBack,this));
	pauseBtn->setAnchorPoint(Point(1, 0));
	pauseBtn->setPosition(Point(winSize.width,0));
	this->addChild(pauseBtn, 10, 233);

	//继续按钮
	Button *continueBtn = Button::create("play.png");
	continueBtn->addClickEventListener(CC_CALLBACK_1(GameScene::pauseCallBack, this));
	continueBtn->setAnchorPoint(Point(1, 0));
	continueBtn->setPosition(Point(winSize.width, 0));
	continueBtn->setVisible(false);
	continueBtn->setEnabled(false);
	this->addChild(continueBtn, 10, 234);

	//播放音乐
	if (Config::getInstance()->isAudio) {
		CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("Music/bgMusic.mp3", true);
		Config::getInstance()->isBgAudio = true;
	}
	return true;
}

void GameScene::update(float dt)
{
	if (!m_isOver)
	{
		//英雄子弹与敌机碰撞检测
		for (auto heroBullets : heroBullet)
		{
			if (heroBullets->isdead()) continue;
			Rect heroCollide = heroBullets->getBoundingBox();
			for (auto enemy : enemyCount)
			{
				Rect enemyCollide = enemy->collideRect();
				if (heroCollide.intersectsRect(enemyCollide))
				{
					enemy->hurt(heroBullets->getAKT());
					log("AKT: %d", heroBullets->getAKT());
					log("hp: %d", enemy->hp());
					heroBullets->death();
					if (enemy->hp() <= 0)
					{
						//吸血道具
						if (Config::getInstance()->isBlood)
						{
							if(m_hero->getHpMax() != m_hero->hp()) m_hero->setHp(m_hero->hp() + 1);
						}
						int score = Config::getInstance()->scoreValue += enemy->getScoreValue();
						char str[20];
						sprintf(str, "%d", score);
						m_scroe->setString("Score:" + (std::string)str);
						if (enemy->isObject() == 3) {
							m_isOver = true;
						}
						enemy->death();
						return;
					}
					break;
				}
			}
		}
		//敌机子弹与英雄碰撞检测
		for (auto enemyBullets : enemyBullet)
		{
			Rect enemyCollide = enemyBullets->getBoundingBox();
			Rect heroCollide = m_hero->collideRect();
			if (enemyCollide.intersectsRect(heroCollide))
			{
				enemyBullets->death();
				//防御技能是否开启
				if (Config::getInstance()->defenseSkill == false) {
					m_hero->hurt(enemyBullets->getAKT());
				}
				if (m_hero->hp() <= 0) {
					m_hero->death();
					m_hero = NULL;
					m_isOver = true;
					return;
				}
			}
		}
		//敌机与英雄碰撞检测
		for (auto enemy : enemyCount)
		{
			Rect enemyCollide = enemy->getBoundingBox();
			Rect heroCollide = m_hero->collideRect();
			if (heroCollide.intersectsRect(enemyCollide))
			{
				enemy->hurt(m_hero->getCollideValue());
				m_hero->hurt(enemy->getCollideValue());
				if (enemy->hp() <= 0) enemy->death();
				int hp = m_hero->hp();
				if (hp < 0) {
					m_hero->death();
					m_hero = NULL;
					m_isOver = true;
					return;
				}
			}
		}
	}
}

void GameScene::enemyCountUpdate(float dt)
{
	if (!m_isOver) {
		if (!m_Boss) {
			if (Config::getInstance()->km > 100) {
				if (enemyCount.size() <= 30) {
					auto enemyType = Config::getInstance()->getEnemyType();
					auto heroPos = m_hero->getPosition();
					Enemy *enemy = gameLevel.createEnemy(enemyType, heroPos);
					this->addChild(enemy);
				}
			}
		}
		if (Config::getInstance()->km > 1000) {
			if (!m_Boss) {
				m_Boss = Boss::create(Config::getInstance()->level);
				this->addChild(m_Boss);
				m_Boss->hpShow();
			}
		}
	}
}

void GameScene::pauseCallBack(Object * pSender)
{
	auto Btn = static_cast<Button*>(pSender);
	//暂停
	if (Btn->getTag() == 233)
	{
		CocosDenshion::SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
		CocosDenshion::SimpleAudioEngine::getInstance()->pauseAllEffects();
		Director::getInstance()->pause();
		Btn->setEnabled(false);
		Btn->setVisible(false);
		auto continueBtn = static_cast<Button*>(this->getChildByTag(234));
		continueBtn->setEnabled(true);
		continueBtn->setVisible(true);
		auto goBackBtn = static_cast<Button*>(this->getChildByTag(2333));
		goBackBtn->setEnabled(true);
		goBackBtn->setVisible(true);
	}
	//继续
	if (Btn->getTag() == 234)
	{
		Director::getInstance()->resume();
		if (Config::getInstance()->isAudio) {
			CocosDenshion::SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
			CocosDenshion::SimpleAudioEngine::getInstance()->resumeAllEffects();
		}
		Btn->setEnabled(false);
		Btn->setVisible(false);
		auto pauseBtn = static_cast<Button*>(this->getChildByTag(233));
		pauseBtn->setEnabled(true);
		pauseBtn->setVisible(true);
		auto goBackBtn = static_cast<Button*>(this->getChildByTag(2333));
		goBackBtn->setEnabled(false);
		goBackBtn->setVisible(false);
	}
	//返回
	if (Btn->getTag() == 2333)
	{
		//游戏结束切换场景
		Config::getInstance()->scoreValue = 0;
		Config::getInstance()->km = 0;
		Config::getInstance()->isWin = false;
		Director::getInstance()->resume();
		Director::getInstance()->runWithScene(TransitionFade::create(1.0f, GameMenu::createScene()));
	}
}

void GameScene::mapUpdate(float dt)
{
	auto m_bg1Y = m_bg1->getPositionY();
	auto m_bg2Y = m_bg2->getPositionY();
	auto TiledMapY1 = m_TiledMap1->getPositionY();
	auto TiledMapY2 = m_TiledMap2->getPositionY();
	m_bg1Y = m_bg1Y - 1;
	m_bg2Y = m_bg2Y - 1;
	TiledMapY1 = TiledMapY1 - 1;
	TiledMapY2 = TiledMapY2 - 1;

	m_bg1->setPositionY(m_bg1Y);
	m_bg2->setPositionY(m_bg2Y);
	m_TiledMap1->setPositionY(TiledMapY1);
	m_TiledMap2->setPositionY(TiledMapY2);

	if (m_bg1->getPositionY() < -(m_bg1->getContentSize().height / 2) || m_bg2->getPositionY() < -(m_bg2->getContentSize().height / 2))
	{
		m_bg2->setPosition(Point(winSize.width / 2, m_bg1->getContentSize().height / 2));
		m_bg1->setPosition(Point(winSize.width / 2, m_bg1->getContentSize().height + m_bg1->getContentSize().height / 2));
	}
	if (m_TiledMap1->getPositionY() < -(m_TiledMap1->getContentSize().height) || m_TiledMap2->getPositionY() < -(m_TiledMap2->getContentSize().height))
	{
		m_TiledMap2->setPosition(Point(0, 0));
		m_TiledMap1->setPosition(Point(0, m_TiledMap1->getContentSize().height));
	}

	int value = Config::getInstance()->km += 1;
	char str[20];
	sprintf(str, "%d", value);
	m_distance->setString((std::string)str + " km");
	if (m_isOver) {

		if (m_hero) {
			this->unscheduleAllSelectors();
			auto label = LabelBMFont::create("You Win !!!", "Font/bitmapFontTest.fnt");
			label->setPosition(Point(winSize.width / 2, winSize.height / 2));
			this->addChild(label);
			label->setScale(0);
			label->runAction(ScaleTo::create(0.8, 0.6));
			Config::getInstance()->isWin = true;

			auto levelStr = LOAD("Level");
			int level = Value(levelStr).asInt();
			if (level < 10) {
				if (level == Config::getInstance()->level)
				{
					++level;
					SAVE("Level", level);
				}
			}
		}

		this->scheduleOnce(schedule_selector(GameScene::updateOne),3.0f);
	}
}

void GameScene::updateOne(float dt)
{
	Director::getInstance()->runWithScene(TransitionFade::create(1.0f, GameOver::createScene()));
}