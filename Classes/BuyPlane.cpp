#include "BuyPlane.h"
#include "ui\UIButton.h"
#include "GameMenu.h"
#include "Config.h"
using namespace ui;

#define GOBACK_TAG 1
#define LOAD Config::getInstance()->loadFileData
#define SAVE Config::getInstance()->fileSave
Scene * BuyPlane::createScene()
{
	auto scene = Scene::create();
	auto layer = BuyPlane::create();
	scene->addChild(layer);
	return scene;
}

bool BuyPlane::init()
{
	if (!Layer::init()) {
		return false;
	}
	auto winSize = Director::getInstance()->getWinSize();

	Sprite *bg = Sprite::create("map.jpg");
	bg->setAnchorPoint(Point(0, 0));
	this->addChild(bg);

	Button *goBack = Button::create("back.png");
	goBack->setPosition(Point(270, 40));
	goBack->setTag(GOBACK_TAG);
	goBack->addClickEventListener(CC_CALLBACK_1(BuyPlane::callBack, this));
	this->addChild(goBack);

	Sprite *planeBg = Sprite::create("buyBg.jpg");
	planeBg->setPosition(Point(winSize.width / 2,winSize.height / 2));
	this->addChild(planeBg,1,233);

	auto planeBgos = planeBg->getContentSize();
	Sprite *planeSpr = Sprite::create("ship.png");
	planeSpr->setPosition(Point(planeBgos.width / 2,planeBgos.height - 25));
	planeBg->addChild(planeSpr);

	//攻击力
	int value = Value(LOAD("ATK")).asInt();
	std::string labelStr = LOAD("ATK", "UI.xml") + Value(value).asString() + "-->" + Value(value + 1).asString();
	Label *ATKLabel = Label::create(labelStr, "宋体", 20);
	ATKLabel->setPosition(Point(planeBgos.width / 2,planeBgos.height - 70));
	planeBg->addChild(ATKLabel,11,2);
	ATKLabel->setColor(Color3B(255, 215, 0));

	Button *ATKBtn = Button::create("bgk.png");
	ATKBtn->setPosition(Point(planeBgos.width / 2, planeBgos.height - 110));
	ATKBtn->setTitleText(LOAD("ATK_Money"));
	ATKBtn->setTitleColor(Color3B(135, 206, 250));
	ATKBtn->setScale(0.8);
	ATKBtn->setTitleFontSize(20);
	ATKBtn->addClickEventListener(CC_CALLBACK_1(BuyPlane::callBack, this));
	planeBg->addChild(ATKBtn,11,20);

	//生命值
	value = Value(LOAD("HP")).asInt();
	labelStr = LOAD("HP","UI.xml") + Value(value).asString() + "-->" + Value(value + 100).asString();
	Label *Hplabel = Label::create(labelStr, "宋体", 20);
	Hplabel->setPosition(Point(planeBgos.width / 2, planeBgos.height - 150));
	planeBg->addChild(Hplabel,11,3);
	Hplabel->setColor(Color3B(255, 215, 0));

	Button *HpBtn = Button::create("bgk.png");
	HpBtn->setPosition(Point(planeBgos.width / 2, planeBgos.height - 190));
	HpBtn->setTitleText(LOAD("HP_Money"));
	HpBtn->setTitleColor(Color3B(135, 206, 250));
	HpBtn->setScale(0.8);
	HpBtn->setTitleFontSize(20);
	HpBtn->addClickEventListener(CC_CALLBACK_1(BuyPlane::callBack, this));
	planeBg->addChild(HpBtn, 11, 30);

	//子弹数量
	value = Value(LOAD("BulletCount")).asInt();
	labelStr = LOAD("BulletCount","UI.xml") + Value(value).asString() + "-->" + Value(value + 2).asString();
	Label *BulletLabel = Label::create(labelStr, "宋体", 20);
	BulletLabel->setPosition(Point(planeBgos.width / 2, planeBgos.height - 230));
	planeBg->addChild(BulletLabel,11,4);
	BulletLabel->setColor(Color3B(255, 215, 0));

	Button *BulletBtn = Button::create("bgk.png");
	BulletBtn->setPosition(Point(planeBgos.width / 2, planeBgos.height - 270));
	BulletBtn->setTitleText(LOAD("BulletCount_Money"));
	BulletBtn->setTitleColor(Color3B(135, 206, 250));
	BulletBtn->setScale(0.8);
	BulletBtn->setTitleFontSize(20);
	BulletBtn->addClickEventListener(CC_CALLBACK_1(BuyPlane::callBack, this));
	planeBg->addChild(BulletBtn, 11, 40);
	if (LOAD("BulletCount") == "4") {
		BulletLabel->setString(LOAD("BulletCount","UI.xml") + "4");
		BulletBtn->setEnabled(false);
		BulletBtn->setTitleText("MAX");
	}
	return true;
}

void BuyPlane::callBack(Object * pSender)
{
	auto tag = static_cast<Node*>(pSender)->getTag();
	auto btn = static_cast<Button*>(pSender);
	if (tag == GOBACK_TAG) Director::getInstance()->runWithScene(TransitionFade::create(1.0f, GameMenu::createScene()));

	int money = Value(LOAD("Money")).asInt();

	//攻击力升级
	if (tag == 20)
	{
		Label *label = static_cast<Label*>(this->getChildByTag(233)->getChildByTag(2));
		int BuyMoney = Value(LOAD("ATK_Money")).asInt();
		int value = Value(LOAD("ATK")).asInt();
		if (money >= BuyMoney)
		{
			money -= BuyMoney;
			value++;
			BuyMoney += 10000;
			SAVE("Money", money);
			SAVE("ATK", value);
			SAVE("ATK_Money", BuyMoney);
			label->setString(LOAD("ATK","UI.xml") + Value(value).asString() + "-->" + Value(value + 1).asString());
			btn->setTitleText(Value(BuyMoney).asString());
			MsgMenu(LOAD("UpTrue","UI.xml"));
		}
		else
		{
			MsgMenu(LOAD("Error1", "UI.xml"));
		}
	}

	//生命值升级
	if (tag == 30)
	{
		Label *label = static_cast<Label*>(this->getChildByTag(233)->getChildByTag(3));
		int BuyMoney = Value(LOAD("HP_Money")).asInt();
		int value = Value(LOAD("HP")).asInt();
		if (money >= BuyMoney)
		{
			money -= BuyMoney;
			value += 100;
			BuyMoney += 10000;
			SAVE("Money", money);
			SAVE("HP", value);
			SAVE("HP_Money", BuyMoney);
			label->setString(LOAD("HP","UI.xml") + Value(value).asString() + "-->" + Value(value + 100).asString());
			btn->setTitleText(Value(BuyMoney).asString());
			MsgMenu(LOAD("UpTrue", "UI.xml"));
		}
		else
		{
			MsgMenu(LOAD("Error1", "UI.xml"));
		}
	}

	//子弹数量升级
	if (tag == 40)
	{
		Label *label = static_cast<Label*>(this->getChildByTag(233)->getChildByTag(4));
		int BuyMoney = Value(LOAD("BulletCount_Money")).asInt();
		int value = Value(LOAD("BulletCount")).asInt();
		if (money >= BuyMoney)
		{
			money -= BuyMoney;
			value += 2; 
			BuyMoney += 20000;
			SAVE("Money", money);
			SAVE("BulletCount", value);
			SAVE("BulletCount_Money", BuyMoney);
			label->setString(LOAD("BulletCount","UI.xml") + "4");
			btn->setTitleText("MAX");
			btn->setEnabled(false);
			MsgMenu(LOAD("UpTrue", "UI.xml"));
		}
		else
		{
			MsgMenu(LOAD("Error1", "UI.xml"));
		}
	}
}

void BuyPlane::MsgMenu(const std::string & text)
{
	auto winSize = Director::getInstance()->getWinSize();
	//背景
	Sprite *bg = Sprite::create("buyBg.jpg");
	bg->setPosition(Point(winSize.width / 2, winSize.height / 2));
	bg->setScaleX(0.6);
	bg->setScaleY(0.2);
	this->addChild(bg,22);

	//信息
	Label *label = Label::create(text, "Arial", 20);
	label->setColor(Color3B(255, 255, 0));
	label->setPosition(Point(winSize.width / 2, winSize.height / 2 + 15));
	this->addChild(label,22);

	//金币
	Sprite *moneySpr = Sprite::create("money.png");
	moneySpr->setPosition(Point(winSize.width / 2 - 30, winSize.height / 2 - 15));
	moneySpr->setScale(0.5);
	this->addChild(moneySpr,22);

	Label *money = Label::create(LOAD("Money"), "Arial", 20);
	money->setPosition(Point(winSize.width / 2 - 10, winSize.height / 2 - 15));
	money->setAnchorPoint(Point(0, 0.5));
	money->setColor(Color3B(255, 215, 0));
	money->setAlignment(TextHAlignment::LEFT);
	this->addChild(money,22);

	//2秒后消失
	bg->runAction(Sequence::create(DelayTime::create(2.0f), CallFunc::create([=]() {
		bg->removeFromParentAndCleanup(true);
		label->removeFromParentAndCleanup(true);
		moneySpr->removeFromParentAndCleanup(true);
		money->removeFromParentAndCleanup(true);
	}), NULL));
}
