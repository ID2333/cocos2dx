#include "GameLevel.h"
#include "GameScene.h"
#include "ui\UIButton.h"
#include "GameMenu.h"
using namespace ui;

#define HPADD_TAG 1
#define ATK_TAG 2
#define BOSSHP_TAG 3
#define BLOOD_TAG 4

GameLevel::GameLevel():m_index(Value(LOAD("Level")).asInt())
{
}

GameLevel::~GameLevel()
{
}

Scene * GameLevel::createScene()
{
	auto scene = Scene::create();
	auto layer = GameLevel::create();
	scene->addChild(layer);
	return scene;
}

bool GameLevel::init()
{
	if (!Layer::init()) {
		return false;
	}

	//初始化道具
	Config::getInstance()->isHpAdd = false;
	Config::getInstance()->isATK = false;
	Config::getInstance()->isBossHp = false;
	Config::getInstance()->isBlood = false;

	Size winSize = Director::getInstance()->getWinSize();
	Sprite *bg = Sprite::create("bg.png");
	bg->setAnchorPoint(Point(0, 0));
	this->addChild(bg);

	m_gameLevel_1 = LabelBMFont::create("level "+ Value(m_index).asString(), "Font/bitmapFontTest.fnt");
	MenuItemLabel* gameStart = MenuItemLabel::create(m_gameLevel_1, CC_CALLBACK_1(GameLevel::start, this));

	Sprite *sprite = Sprite::create("bgk.png");
	sprite->setPosition(Point(winSize.width / 2,winSize.height / 2));
	this->addChild(sprite);
	gameStart->setScale(0.5);
	
	ui::Button *nextBtn = ui::Button::create("next.png");
	nextBtn->setPosition(Point(winSize.width / 2 + 50, winSize.height / 2 - 60));
	nextBtn->addClickEventListener(CC_CALLBACK_0(GameLevel::nextCallBack,this));
	this->addChild(nextBtn);
	ui::Button *lastBtn = ui::Button::create("last.png");
	lastBtn->setPosition(Point(winSize.width / 2 - 50, winSize.height / 2 - 60));
	lastBtn->addClickEventListener(CC_CALLBACK_0(GameLevel::lastCallBack, this));
	this->addChild(lastBtn);
	ui::Button *backBtn = ui::Button::create("back.png");
	backBtn->setPosition(Point(winSize.width - 50, 40));
	backBtn->addClickEventListener(CC_CALLBACK_0(GameLevel::backCallBack, this));
	this->addChild(backBtn);
	
	gameStart->setPosition(Point(winSize.width / 2, winSize.height / 2));
	
	Menu* menu = Menu::create(gameStart, NULL);
	menu->setPosition(Point::ZERO);
	addChild(menu);

	Label *itemLabel = Label::create(LOAD("ItemLabel", "UI.xml"), "Arial", 20);
	itemLabel->setPosition(Point(winSize.width / 2, winSize.height - 40));
	this->addChild(itemLabel);

	//生命值增加道具
	Button *hpAdd = Button::create("blood.png");
	hpAdd->setPosition(Point(winSize.width / 2 - 100,winSize.height - 100));
	hpAdd->setScale(0.2);
	hpAdd->setColor(Color3B(105, 105, 105));
	hpAdd->addClickEventListener(CC_CALLBACK_1(GameLevel::itemCallBack, this));
	this->addChild(hpAdd,10,HPADD_TAG);
	Label *hpAddlabel = Label::create("X " + LOAD("HP_ItemCount"),"Arial",18);
	hpAddlabel->setPosition(Point(winSize.width / 2 - 100, winSize.height - 150));
	this->addChild(hpAddlabel);

	//攻击力道具
	Button *ATK = Button::create("ATK.png");
	ATK->setPosition(Point(winSize.width / 2 - 30, winSize.height - 100));
	ATK->setScale(0.4);
	ATK->setColor(Color3B(105, 105, 105));
	ATK->addClickEventListener(CC_CALLBACK_1(GameLevel::itemCallBack, this));
	this->addChild(ATK,10,ATK_TAG);
	Label *ATKlabel = Label::create("X " + LOAD("ATK_ItemCount"), "Arial", 18);
	ATKlabel->setPosition(Point(winSize.width / 2 - 30, winSize.height - 150));
	this->addChild(ATKlabel);

	//Boss生命减少道具
	Button *BossHp = Button::create("BossHp.png");
	BossHp->setPosition(Point(winSize.width / 2 + 40, winSize.height - 100));
	BossHp->setScale(0.4);
	BossHp->setColor(Color3B(105,105,105));
	BossHp->addClickEventListener(CC_CALLBACK_1(GameLevel::itemCallBack, this));
	this->addChild(BossHp,10,BOSSHP_TAG);
	Label *BossHplabel = Label::create("X " + LOAD("BossHP_ItemCount"), "Arial", 18);
	BossHplabel->setPosition(Point(winSize.width / 2 + 40, winSize.height - 150));
	this->addChild(BossHplabel);

	//吸血道具
	Button *blood = Button::create("BloodHp.png");
	blood->setPosition(Point(winSize.width / 2 + 110, winSize.height - 100));
	blood->setScale(0.4);
	blood->setColor(Color3B(105, 105, 105));
	blood->addClickEventListener(CC_CALLBACK_1(GameLevel::itemCallBack, this));
	this->addChild(blood,10,BLOOD_TAG);
	Label *bloodlabel = Label::create("X " + LOAD("Blood_ItemCount"), "Arial", 18);
	bloodlabel->setPosition(Point(winSize.width / 2 + 110, winSize.height - 150));
	this->addChild(bloodlabel);
	return true;
}


void GameLevel::start(Object * pSender)
{
	if (Config::getInstance()->isHpAdd) {
		int itemCount = Value(LOAD("HP_ItemCount")).asInt();
		SAVE("HP_ItemCount", --itemCount);
	}
	if (Config::getInstance()->isATK) {
		int itemCount = Value(LOAD("ATK_ItemCount")).asInt();
		SAVE("ATK_ItemCount", --itemCount);
	}
	if (Config::getInstance()->isBossHp) {
		int itemCount = Value(LOAD("BossHP_ItemCount")).asInt();
		SAVE("BossHP_ItemCount", --itemCount);
	}
	if (Config::getInstance()->isBlood) {
		int itemCount = Value(LOAD("Blood_ItemCount")).asInt();
		SAVE("Blood_ItemCount", --itemCount);
	}
	Config::getInstance()->level = m_index;
	Director::getInstance()->runWithScene(TransitionFade::create(1.0f, GameScene::createScene()));
}

void GameLevel::itemCallBack(Object * pSender)
{
	auto btn = static_cast<Button*>(pSender);
	std::string str;
	if (btn->getColor() == Color3B(105, 105, 105))
	{
		if (btn->getTag() == HPADD_TAG) str = "HP_ItemCount";
		if (btn->getTag() == ATK_TAG) str = "ATK_ItemCount";
		if (btn->getTag() == BOSSHP_TAG) str = "BossHP_ItemCount";
		if (btn->getTag() == BLOOD_TAG) str = "Blood_ItemCount";

		int itemCount = Value(LOAD(str)).asInt();
		if (itemCount > 0)
		{
			if (btn->getTag() == HPADD_TAG) Config::getInstance()->isHpAdd = true;
			if (btn->getTag() == ATK_TAG) Config::getInstance()->isATK = true;
			if (btn->getTag() == BOSSHP_TAG) Config::getInstance()->isBossHp = true;
			if (btn->getTag() == BLOOD_TAG) Config::getInstance()->isBlood = true;
			btn->setColor(Color3B(255, 255, 255));
		}
		else {
			MsgMenu(LOAD("Error2","UI.xml"));
		}
	}
	else {
		if (btn->getTag() == HPADD_TAG) Config::getInstance()->isHpAdd = false;
		if (btn->getTag() == ATK_TAG) Config::getInstance()->isATK = false;
		if (btn->getTag() == BOSSHP_TAG) Config::getInstance()->isBossHp = false;
		if (btn->getTag() == BLOOD_TAG) Config::getInstance()->isBlood = false;
		btn->setColor(Color3B(105, 105, 105));
	}
}

void GameLevel::nextCallBack()
{
	auto level = LOAD("Level");
	if (Value(level).asInt() > m_index) {
		m_index++;
		m_gameLevel_1->setString(StringUtils::format("level %d", m_index));
	}
	else if(m_index == 10){
		MsgMenu(Config::getInstance()->loadFileData("Error5", "UI.xml"));
	}
	else {
		MsgMenu(Config::getInstance()->loadFileData("Error4", "UI.xml"));
	}
}

void GameLevel::lastCallBack()
{
	if (m_index > 1) {
		m_index--;
		m_gameLevel_1->setString(StringUtils::format("level %d", m_index));
	}
}

void GameLevel::backCallBack()
{
	Director::getInstance()->runWithScene(TransitionFade::create(1.0f, GameMenu::createScene()));
}

void GameLevel::MsgMenu(const std::string & text)
{
	auto winSize = Director::getInstance()->getWinSize();
	//背景
	Sprite *bg = Sprite::create("buyBg.jpg");
	bg->setPosition(Point(winSize.width / 2, winSize.height / 2));
	bg->setScaleX(0.7);
	bg->setScaleY(0.1);
	this->addChild(bg);

	//信息
	Label *label = Label::create(text, "Arial", 20);
	label->setColor(Color3B(255, 255, 0));
	label->setPosition(Point(winSize.width / 2, winSize.height / 2 ));
	this->addChild(label);

	//2秒后消失
	bg->runAction(Sequence::create(DelayTime::create(2.0f), CallFunc::create([=]() {
		bg->removeFromParentAndCleanup(true);
		label->removeFromParentAndCleanup(true);
	}), NULL));
}
