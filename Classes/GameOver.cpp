#include "GameOver.h"
#include "Config.h"
#include "ui\UIButton.h"
#include "GameMenu.h"

#define LOAD Config::getInstance()->loadFileData
#define SAVE Config::getInstance()->fileSave

GameOver::GameOver()
{
}

GameOver::~GameOver()
{
	
}

Scene * GameOver::createScene()
{
	auto scene = Scene::create();
	auto layer = GameOver::create();
	scene->addChild(layer);
	return scene;
}

bool GameOver::init()
{
	if (!Layer::init()) {
		return false;
	}

	Sprite *sprite = Sprite::create("loading.png");
	sprite->setAnchorPoint(Point(0,0));
	this->addChild(sprite);

	Sprite *moneySprite = Sprite::create("money.png");
	moneySprite->setPosition(Point(130, 192));
	moneySprite->setScale(0.5);
	this->addChild(moneySprite);

	int scoreValue = Config::getInstance()->scoreValue;
	LabelTTF *label = LabelTTF::create("Score:" + Value(scoreValue).asString(), "Arial Bold", 16);
	label->setPosition(Point(160,280));
	label->setColor(Color3B(255,179,0));
	this->addChild(label);

	std::string score = LOAD("WinScore","UI.xml");
	std::string winScore = Config::getInstance()->isWin ? Value(Config::getInstance()->level * 20000).asString() : "0";

	LabelTTF *winlabel = LabelTTF::create(score + winScore, "Arial Bold", 16);
	winlabel->setPosition(Point(160, 250));
	winlabel->setColor(Color3B(255, 179, 0));
	this->addChild(winlabel);

	score = LOAD("AllScore", "UI.xml");
	int allScore = Value(winScore).asInt() + scoreValue;
	LabelTTF *allScroe = LabelTTF::create(score + Value(allScore).asString(), "Arial Bold", 16);
	allScroe->setPosition(Point(160, 220));
	allScroe->setColor(Color3B(255, 179, 0));
	this->addChild(allScroe);

	LabelTTF *money = LabelTTF::create("+" + Value(allScore / 40).asString(), "Arial Bold", 16,Size::ZERO,TextHAlignment::RIGHT);
	money->setAnchorPoint(Point(0, 0.5));
	money->setPosition(Point(150, 190));
	money->setColor(Color3B(255, 179, 0));
	this->addChild(money);
	
	score = LOAD("Money");
	SAVE("Money", Value(score).asInt() + allScore / 40);

	Sprite *logo = Sprite::create("gameOver.png");
	logo->setPosition(Point(160,350));
	this->addChild(logo);

	ui::Button *btn = ui::Button::create("bgk.png");
	btn->setTitleText("Menu");
	btn->setTitleFontSize(21);
	btn->setTitleColor(Color3B(135, 206, 250));
	btn->addClickEventListener(CC_CALLBACK_0(GameOver::CallBackMenu,this));
	btn->setPosition(Point(160,150));
	this->addChild(btn);

	return true;
}

void GameOver::CallBackMenu()
{
	Config::getInstance()->scoreValue = 0;
	Config::getInstance()->km = 0;
	Config::getInstance()->isWin = false;
	Config::getInstance()->defenseSkill = false;
	Director::getInstance()->runWithScene(TransitionFade::create(1.0f, GameMenu::createScene()));
}
