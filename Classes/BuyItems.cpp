#include "BuyItems.h"
#include "ui\UIButton.h"
#include "GameMenu.h"
#include "Config.h"
using namespace ui;

#define GOBACK_TAG 1
#define HPADD_TAG 2
#define ATK_TAG 3
#define BOSSHP_TAG 4
#define BLOOD_TAG 5
#define HPADD_LABEL_TAG 6
#define ATK_LABEL_TAG 7
#define BOSSHP_LABEL_TAG 8
#define BLOOD_LABEL_TAG 9
#define LOAD Config::getInstance()->loadFileData
#define SAVE Config::getInstance()->fileSave
Scene * BuyItems::createScene()
{
	auto scene = Scene::create();
	auto layer = BuyItems::create();
	scene->addChild(layer);
	return scene;
}

bool BuyItems::init()
{
	if (!Layer::init()) {
		return false;
	}

	Sprite *bg = Sprite::create("map.jpg");
	bg->setAnchorPoint(Point(0, 0));
	this->addChild(bg);

	Button *goBack = Button::create("back.png");
	goBack->setPosition(Point(270, 40));
	goBack->setTag(GOBACK_TAG);
	goBack->addClickEventListener(CC_CALLBACK_1(BuyItems::callBack, this));
	this->addChild(goBack);

	Label *buyItemsText = Label::create(LOAD("Item_label","UI.xml"), "Arial", 20);
	buyItemsText->setColor(Color3B(255, 0, 0));
	buyItemsText->setPosition(Point(160, 450));
	this->addChild(buyItemsText);

	//生命值增加
	Button *hpAdd100Btn = Button::create("blood.png");
	hpAdd100Btn->setPosition(Point(40, 400));
	hpAdd100Btn->setScale(0.25);
	hpAdd100Btn->setTag(HPADD_TAG);
	hpAdd100Btn->addClickEventListener(CC_CALLBACK_1(BuyItems::callBack, this));
	this->addChild(hpAdd100Btn);

	std::string label = LOAD("HP_Item", "UI.xml") + '\n' + LOAD("Money", "UI.xml")+ "1000; " + LOAD("Have", "UI.xml") + LOAD("HP_ItemCount");
	Label *hpAdd100 = Label::create(label, "Arial", 20);
	hpAdd100->setAnchorPoint(Point(0, 0.5));
	hpAdd100->setColor(Color3B(255, 0, 0));
	hpAdd100->setTag(HPADD_LABEL_TAG);
	hpAdd100->setPosition(Point(80, 400));
	this->addChild(hpAdd100);

	//攻击力增加
	Button *ATKBtn = Button::create("ATK.png");
	ATKBtn->setPosition(Point(40, 320));
	ATKBtn->setScale(0.5);
	ATKBtn->setTag(ATK_TAG);
	ATKBtn->addClickEventListener(CC_CALLBACK_1(BuyItems::callBack, this));
	this->addChild(ATKBtn);

	label = LOAD("ATK_Item", "UI.xml") + '\n' + LOAD("Money", "UI.xml") + "2000; " + LOAD("Have", "UI.xml") + LOAD("ATK_ItemCount");
	Label *ATK = Label::create(label, "Arial", 20);
	ATK->setAnchorPoint(Point(0, 0.5));
	ATK->setColor(Color3B(255, 0, 0));
	ATK->setTag(ATK_LABEL_TAG);
	ATK->setPosition(Point(80, 320));
	this->addChild(ATK);

	//BOSS生命减少
	Button *BossHpBtn = Button::create("BossHp.png");
	BossHpBtn->setPosition(Point(40, 240));
	BossHpBtn->setScale(0.5);
	BossHpBtn->setTag(BOSSHP_TAG);
	BossHpBtn->addClickEventListener(CC_CALLBACK_1(BuyItems::callBack, this));
	this->addChild(BossHpBtn);

	label = LOAD("BossHP_Item", "UI.xml") + '\n' + LOAD("Money", "UI.xml") + "2000; " + LOAD("Have", "UI.xml") + LOAD("BossHP_ItemCount");
	Label *BossHp = Label::create(label, "Arial", 20);
	BossHp->setAnchorPoint(Point(0, 0.5));
	BossHp->setColor(Color3B(255, 0, 0));
	BossHp->setTag(BOSSHP_LABEL_TAG);
	BossHp->setPosition(Point(80, 240));
	this->addChild(BossHp);

	//杀死敌人生命值+1
	Button *bloodBtn = Button::create("BloodHp.png");
	bloodBtn->setPosition(Point(40, 160));
	bloodBtn->setScale(0.5);
	bloodBtn->setTag(BLOOD_TAG);
	bloodBtn->addClickEventListener(CC_CALLBACK_1(BuyItems::callBack, this));
	this->addChild(bloodBtn);

	label = LOAD("Blood_Item", "UI.xml") + '\n' + LOAD("Money", "UI.xml") + "2000; " + LOAD("Have", "UI.xml") + LOAD("Blood_ItemCount");
	Label *blood = Label::create(label, "Arial", 20);
	blood->setAnchorPoint(Point(0, 0.5));
	blood->setColor(Color3B(255, 0, 0));
	blood->setTag(BLOOD_LABEL_TAG);
	blood->setPosition(Point(80, 160));
	this->addChild(blood);
	return true;
}

void BuyItems::callBack(Object * pSender)
{
	auto tag = static_cast<Node*>(pSender)->getTag();
	auto btn = static_cast<Button*>(pSender);
	if (tag == GOBACK_TAG) { Director::getInstance()->runWithScene(TransitionFade::create(1.0f, GameMenu::createScene())); return; }

	int money = Value(LOAD("Money")).asInt();
	std::string str, itemLabel;
	int itemMoney, itemCount,labelTag;

	if (tag == HPADD_TAG) { str = "HP_"; itemMoney = 1000; labelTag = HPADD_LABEL_TAG; }
	if (tag == ATK_TAG) { str = "ATK_"; itemMoney = 2000; labelTag = ATK_LABEL_TAG; }
	if (tag == BOSSHP_TAG) { str = "BossHP_"; itemMoney = 2000; labelTag = BOSSHP_LABEL_TAG; }
	if (tag == BLOOD_TAG) { str = "Blood_"; itemMoney = 2000; labelTag = BLOOD_LABEL_TAG;}

	itemCount = Value(LOAD(str + "ItemCount")).asInt();
	itemLabel = LOAD(str + "Item","UI.xml") + '\n';

	if (money >= itemMoney)
	{
		SAVE("Money",money - itemMoney);
		SAVE(str + "ItemCount", ++itemCount);
		Label *label = static_cast<Label*>(this->getChildByTag(labelTag));
		label->setString(itemLabel + LOAD("Money","UI.xml") + Value(itemMoney).asString() + "; " + LOAD("Have", "UI.xml") + Value(itemCount).asString());
		MsgMenu(LOAD("BuyTrue","UI.xml"));
		return;
	}
	MsgMenu(LOAD("Error1","UI.xml"));
}

void BuyItems::MsgMenu(const std::string & text)
{
	auto winSize = Director::getInstance()->getWinSize();
	//背景
	Sprite *bg = Sprite::create("buyBg.jpg");
	bg->setPosition(Point(winSize.width / 2, winSize.height / 2));
	bg->setScaleX(0.6);
	bg->setScaleY(0.2);
	this->addChild(bg);

	//信息
	Label *label = Label::create(text, "Arial", 20);
	label->setColor(Color3B(255, 255, 0));
	label->setPosition(Point(winSize.width / 2, winSize.height / 2 + 15));
	this->addChild(label);

	//金币
	Sprite *moneySpr = Sprite::create("money.png");
	moneySpr->setPosition(Point(winSize.width / 2 - 30, winSize.height / 2 - 15));
	moneySpr->setScale(0.5);
	this->addChild(moneySpr);

	Label *money = Label::create(LOAD("Money"), "Arial", 20);
	money->setPosition(Point(winSize.width / 2 - 10, winSize.height / 2 - 15));
	money->setAnchorPoint(Point(0, 0.5));
	money->setColor(Color3B(255, 215, 0));
	money->setAlignment(TextHAlignment::LEFT);
	this->addChild(money);

	//2秒后消失
	bg->runAction(Sequence::create(DelayTime::create(2.0f), CallFunc::create([=]() {
		bg->removeFromParentAndCleanup(true);
		label->removeFromParentAndCleanup(true);
		moneySpr->removeFromParentAndCleanup(true);
		money->removeFromParentAndCleanup(true);
	}), NULL));
}
