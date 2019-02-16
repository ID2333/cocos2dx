#include "BuySkill.h"
#include "ui\UIButton.h"
#include "Config.h"
using namespace std;
using namespace ui;

#define LOAD Config::getInstance()->loadFileData
#define SAVE Config::getInstance()->fileSave
#define GOBACK_TAG 1
#define DEFENSE_SKILL_TAG 2
#define INITIAL_SKILL_TAG 3
#define CLOSE_TAG 4
#define BUY_BTN_TAG 5
#define UPGRADE_BTN_TAG 6
#define SKILL_LABEL_TAG 7

Scene * BuySkill::createScene()
{
	auto scene = Scene::create();
	auto layer = BuySkill::create();
	scene->addChild(layer);
	return scene;
}

bool BuySkill::init()
{
	if (!Layer::init()) {
		return false;
	}
	
	Sprite *bg = Sprite::create("map.jpg");
	bg->setAnchorPoint(Point(0, 0));
	this->addChild(bg);

	Label *buySkillText = Label::create(LOAD("Skill_label", "UI.xml"), "Arial", 20);
	buySkillText->setAnchorPoint(Point(0, 0.5));
	buySkillText->setColor(Color3B(0, 255, 0));
	buySkillText->setPosition(Point(80, 450));
	this->addChild(buySkillText);

	Button *goBack = Button::create("back.png");
	goBack->setPosition(Point(270, 40));
	goBack->setTag(GOBACK_TAG);
	goBack->addClickEventListener(CC_CALLBACK_1(BuySkill::callBack, this));
	this->addChild(goBack);
	
	//初始技能
	Button *Skill_1 = Button::create("tenfold.png");
	Skill_1->setPosition(Point(40, 400));
	Skill_1->setScale(0.5);
	Skill_1->setTag(INITIAL_SKILL_TAG);
	Skill_1->addClickEventListener(CC_CALLBACK_1(BuySkill::callBack, this));
	this->addChild(Skill_1);

	std::string label = LOAD("Skill_1", "UI.xml") + '\n';
	label += LOAD("Skill_Time", "UI.xml") + LOAD("Skill_1_Time") + "s; ";
	label += LOAD("Skill_CD", "UI.xml") + LOAD("Skill_1_CD") + "s";
	Label *Skill_1_Label = Label::create(label, "Arial", 20);
	Skill_1_Label->setAnchorPoint(Point(0, 0.5));
	Skill_1_Label->setColor(Color3B(0, 255, 0));
	Skill_1_Label->setPosition(Point(80, 400));
	this->addChild(Skill_1_Label);

	//防御技能
	Button *Skill_2 = Button::create("defense.png");
	Skill_2->setPosition(Point(40,320));
	Skill_2->setScale(0.5);
	Skill_2->setTag(DEFENSE_SKILL_TAG);
	Skill_2->addClickEventListener(CC_CALLBACK_1(BuySkill::callBack, this));
	this->addChild(Skill_2);

	label = LOAD("Skill_2", "UI.xml") + '\n';
	label += LOAD("Skill_Time", "UI.xml") + LOAD("Skill_2_Time") + "s; ";
	label += LOAD("Skill_CD", "UI.xml") + LOAD("Skill_2_CD") + "s";
	Label *Skill_2_Label = Label::create(label,"Arial",20);
	Skill_2_Label->setAnchorPoint(Point(0, 0.5));
	Skill_2_Label->setColor(Color3B(0,255,0));
	Skill_2_Label->setPosition(Point(80, 320));
	this->addChild(Skill_2_Label);

	return true;
}

void BuySkill::callBack(Object * pSender)
{
	auto tag = static_cast<Node*>(pSender)->getTag();
	if (tag == GOBACK_TAG) Director::getInstance()->runWithScene(TransitionFade::create(1.0f, GameMenu::createScene()));

	if (tag > 1) {
		Button *upgradeBtn = NULL;
		Button *buyBtn = NULL;
		std::string str, skillName;

		//创建或销毁购买和升级界面
		if (buySprite)
		{
			buySprite->removeFromParentAndCleanup(true);
			buySprite = NULL;
			return;
		}
		else {
			//背景
			buySprite = Sprite::create("buyBg.jpg");
			buySprite->setPosition(Point(160, 240));
			this->addChild(buySprite);

			//购买按钮
			buyBtn = Button::create("bgk.png");
			buyBtn->setTitleText(LOAD("Buy","UI.xml"));
			buyBtn->setTitleColor(Color3B(135, 206, 250));
			buyBtn->setTitleFontSize(20);
			buyBtn->setPosition(Point(70, 40));
			buyBtn->setScaleX(0.8);
			buyBtn->addClickEventListener(CC_CALLBACK_1(BuySkill::btnCallBack, this, tag));
			buyBtn->setTag(BUY_BTN_TAG);
			buySprite->addChild(buyBtn);

			//升级按钮
			upgradeBtn = Button::create("bgk.png");
			upgradeBtn->setTitleText(LOAD("Upgrade", "UI.xml"));
			upgradeBtn->setTitleColor(Color3B(135, 206, 250));
			upgradeBtn->setTitleFontSize(20);
			upgradeBtn->setPosition(Point(180, 40));
			upgradeBtn->setScaleX(0.8);
			upgradeBtn->setTag(UPGRADE_BTN_TAG);
			upgradeBtn->addClickEventListener(CC_CALLBACK_1(BuySkill::btnCallBack, this, tag));
			buySprite->addChild(upgradeBtn);

			//关闭按钮
			Button *closeBtn = Button::create("CloseSelected.png");
			closeBtn->setPosition(Point(225, 270));
			closeBtn->setTag(CLOSE_TAG);
			closeBtn->addClickEventListener(CC_CALLBACK_1(BuySkill::btnCallBack, this, -1));
			buySprite->addChild(closeBtn);
		}

		//技能信息
		if (tag == DEFENSE_SKILL_TAG) { str = "Skill_2_"; skillName = "defense.png"; }
		if (tag == INITIAL_SKILL_TAG) { str = "Skill_1_"; skillName = "tenfold.png"; }
		if (Value(LOAD(str + "Level")).asInt() > 0) { buyBtn->setEnabled(false); buyBtn->setTitleText(LOAD("BuyT","UI.xml")); }
		if (Value(LOAD(str + "Level")).asInt() == 6) { upgradeBtn->setEnabled(false); upgradeBtn->setTitleText("MAX"); }

		Sprite *skill = Sprite::create(skillName);
		skill->setAnchorPoint(Point(0.5, 0.5));
		skill->setPosition(Point(125,265));
		skill->setScale(0.5);
		buySprite->addChild(skill);

		std::string text = LOAD("Skill_Text", "UI.xml") + '\n';
		text += LOAD("Skill_Level", "UI.xml") + LOAD(str + "Level") + '\n';
		text += LOAD("Skill_Time", "UI.xml") + LOAD(str + "Time") + "s\n";
		text += LOAD("Skill_CD", "UI.xml") + LOAD(str + "CD") + "s\n";
		text += LOAD("Skill_BuyMoney", "UI.xml") + LOAD(str + "BuyMoney") + '\n';
		text += LOAD("Skill_UpMoney", "UI.xml") + LOAD(str + "UpMoney");
		Label *SkillLabel = Label::create(text, "Arial", 20);
		SkillLabel->setColor(Color3B(0, 255, 0));
		SkillLabel->setPosition(Point(125, 150));
		SkillLabel->setTag(SKILL_LABEL_TAG);
		buySprite->addChild(SkillLabel);
	}
}

void BuySkill::btnCallBack(Object * pSender,int tag)
{
	//点击关闭时
	auto temp = static_cast<Node*>(pSender)->getTag();
	if (temp == CLOSE_TAG) {
		buySprite->removeFromParentAndCleanup(true);
		buySprite = NULL;
		return;
	}

	std::string skill;
	if (tag == INITIAL_SKILL_TAG) skill = "Skill_1_";
	if (tag == DEFENSE_SKILL_TAG) skill = "Skill_2_";

	//点击购买时
	if (temp == BUY_BTN_TAG)
	{
		int buyMoney = Value(LOAD(skill + "BuyMoney")).asInt();
		int money = Value(LOAD("Money")).asInt();
		if (money >= buyMoney)
		{
			SAVE("Money",money - buyMoney);
			int skillLevel = Value(LOAD(skill + "Level")).asInt() + 1;
			SAVE(skill + "Level",skillLevel);

			auto label = static_cast<Label*>(buySprite->getChildByTag(SKILL_LABEL_TAG));
			auto buyBtn = static_cast<Button*>(buySprite->getChildByTag(BUY_BTN_TAG));

			std::string text = LOAD("Skill_Text", "UI.xml") + '\n';
			text += LOAD("Skill_Level", "UI.xml") + LOAD(skill + "Level") + '\n';
			text += LOAD("Skill_Time", "UI.xml") + LOAD(skill + "Time") + "s\n";
			text += LOAD("Skill_CD", "UI.xml") + LOAD(skill + "CD") + "s\n";
			text += LOAD("Skill_BuyMoney", "UI.xml") + LOAD(skill + "BuyMoney") + '\n';
			text += LOAD("Skill_UpMoney", "UI.xml") + LOAD(skill + "UpMoney");
			label->setString(text);
			buyBtn->setTitleText(LOAD("BuyT","UI.xml"));
			buyBtn->setEnabled(false);
			MsgMenu(LOAD("BuyTrue","UI.xml"));
		}
		else {
			MsgMenu(LOAD("Error1","UI.xml"));
		}
	}

	//点击升级时
	if (temp == UPGRADE_BTN_TAG)
	{
		//判断是否已经购买
		if (!static_cast<Button*>(buySprite->getChildByTag(BUY_BTN_TAG))->isEnabled()) 
		{
			chageFileItems(skill);
		}
		else {
			MsgMenu(LOAD("Error2","UI.xml"));
		}
	}
}


void BuySkill::chageFileItems(std::string keyName)
{
	auto label = static_cast<Label*>(buySprite->getChildByTag(SKILL_LABEL_TAG));
	auto btn = static_cast<Button*>(buySprite->getChildByTag(UPGRADE_BTN_TAG));
	int SkillUpMoney = Value(LOAD(keyName + "UpMoney")).asInt();
	int money = Value(LOAD("Money")).asInt();
	if (money >= SkillUpMoney)
	{
		int level = Value(LOAD(keyName + "Level")).asInt();
		if (level < 6)
		{
			//减少金币
			SAVE("Money",money - SkillUpMoney);

			//数据提升
			int time = Value(LOAD(keyName + "Time")).asInt() + 1;
			int cd = Value(LOAD(keyName + "CD")).asInt() - 1;
			SkillUpMoney += SkillUpMoney * 0.5;
			level++;

			//满级
			if (level == 6) { btn->setTitleText("MAX"); btn->setEnabled(false); }

			//保存
			SAVE(keyName + "Level", level);
			SAVE(keyName + "Time", time);
			SAVE(keyName + "CD", cd);
			SAVE(keyName + "UpMoney", SkillUpMoney);
			MsgMenu(LOAD("UpTrue","UI.xml"));
		}
		else {
			MsgMenu(LOAD("Error3", "UI.xml"));
		}
	}
	else {
		MsgMenu(LOAD("Error1", "UI.xml"));
	}
	std::string text = LOAD("Skill_Text", "UI.xml") + '\n';
	text += LOAD("Skill_Level", "UI.xml") + LOAD(keyName + "Level") + '\n';
	text += LOAD("Skill_Time", "UI.xml") + LOAD(keyName + "Time") + "s\n";
	text += LOAD("Skill_CD", "UI.xml") + LOAD(keyName + "CD") + "s\n";
	text += LOAD("Skill_BuyMoney", "UI.xml") + LOAD(keyName + "BuyMoney") + '\n';
	text += LOAD("Skill_UpMoney", "UI.xml") + LOAD(keyName + "UpMoney");
	label->setString(text);
}

void BuySkill::MsgMenu(const std::string & text)
{
	//背景
	Sprite *bg = Sprite::create("buyBg.jpg");
	bg->setPosition(Point(buySprite->getContentSize().width / 2, buySprite->getContentSize().height / 2));
	bg->setScaleX(0.6);
	bg->setScaleY(0.2);
	buySprite->addChild(bg);
	
	//信息
	Label *label = Label::create(text, "Arial", 20);
	label->setColor(Color3B(255, 255, 0));
	label->setPosition(Point(bg->getContentSize().width / 2, bg->getContentSize().height / 2 + 15));
	buySprite->addChild(label);

	//金币
	Sprite *moneySpr = Sprite::create("money.png");
	moneySpr->setPosition(Point(bg->getContentSize().width / 2 - 30, bg->getContentSize().height / 2 - 15));
	moneySpr->setScale(0.5);
	buySprite->addChild(moneySpr);

	Label *money = Label::create(LOAD("Money"), "Arial", 20);
	money->setPosition(Point(bg->getContentSize().width / 2 - 10, bg->getContentSize().height / 2 - 15));
	money->setAnchorPoint(Point(0, 0.5));
	money->setColor(Color3B(255, 215, 0));
	money->setAlignment(TextHAlignment::LEFT);
	buySprite->addChild(money);

	//2秒后消失
	buySprite->runAction(Sequence::create(DelayTime::create(2.0f), CallFunc::create([=]() {
		bg->removeFromParentAndCleanup(true);
		label->removeFromParentAndCleanup(true);
		moneySpr->removeFromParentAndCleanup(true);
		money->removeFromParentAndCleanup(true);
	}),NULL));
}
