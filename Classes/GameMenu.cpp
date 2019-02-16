#include "GameMenu.h"
#include "SimpleAudioEngine.h"
#include "GameScene.h"
#include "GameLevel.h"
#include "BuyItems.h"
#include "BuyPlane.h"
#include "BuySkill.h"
#include "tinyxml2\tinyxml2.h"

#define START_TAG 1
#define BUY_SKILL_TAG 2
#define BUY_PLANE_TAG 3
#define BUY_ITEMS_TAG 4
#define LAST_TAG 5
#define NEXT_TAG 6
#define MUSICBTN_TAG 7

Scene * GameMenu::createScene()
{
	auto scene = Scene::create();
	auto layer = GameMenu::create();
	scene->addChild(layer);
	return scene;
}

bool GameMenu::init()
{
	if (!Layer::init()) {
		return false;
	}

	Size winSize = Director::getInstance()->getWinSize();
	
	auto androidListener = EventListenerKeyboard::create();
	androidListener->onKeyPressed = CC_CALLBACK_2(GameMenu::onKeyPressed, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(androidListener, this);

	//初始化数据
	Config::getInstance()->initUserDefault();

	//UI
	createSprite("menubg.png",Point(winSize.width / 2,winSize.height / 2));
	createSprite("money.png", Point(20, 460),0.5);
	createSprite("buyBg.jpg", Point(winSize.width / 2 + 60, winSize.height / 2), 0.5);
	createSprite("ship.png", Point(winSize.width / 2 + 60, winSize.height / 2 + 50));

	//文字
	createLabel(LOAD("Money"), Point(40, 460), Color3B(255, 215, 0),Point(0,0.5));
	createLabel("level_" + LOAD("Level"), Point(winSize.width - 20, 460), Color3B(255, 0, 0), Point(1, 0.5),"Arial",20, TextHAlignment::RIGHT);
	createLabel("ShowHeroData", Point(winSize.width / 2 + 60, winSize.height / 2 - 10), Color3B(0, 255, 0));
	createLabel("Music", Point(40,420), Color3B(135, 206, 250));

	//游戏按钮
	createButton("start.png", Point(winSize.width / 2, winSize.height - 400), START_TAG);
	createButton("bgk.png", Point(winSize.width / 2 - 90, winSize.height / 2), BUY_SKILL_TAG, LOAD("Skill", "UI.xml"));
	createButton("bgk.png", Point(winSize.width / 2 - 90, winSize.height / 2 - 60), BUY_PLANE_TAG, LOAD("Plane", "UI.xml"));
	createButton("bgk.png", Point(winSize.width / 2 - 90, winSize.height / 2 + 60), BUY_ITEMS_TAG, LOAD("Item", "UI.xml"));
	auto musicBtn = createButton("bgk.png", Point(115,420), MUSICBTN_TAG,"on");
	musicBtn->setScale(0.7);

	//播放音乐
	if (Config::getInstance()->isAudio) {
		if (Config::getInstance()->isBgAudio) {
			CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("Music/mainMainMusic.mp3", true);
			Config::getInstance()->isBgAudio = false;
		}
		musicBtn->setTitleText("off");
	}

	return true;
}


void GameMenu::Callback(Object *pSender)
{
	auto tag = static_cast<Node*>(pSender)->getTag();
	if (tag == START_TAG) Director::getInstance()->runWithScene(TransitionFade::create(1.2f, GameLevel::createScene()));
	if (tag == BUY_ITEMS_TAG) Director::getInstance()->runWithScene(TransitionFade::create(1.2f, BuyItems::createScene()));
	if (tag == BUY_PLANE_TAG) Director::getInstance()->runWithScene(TransitionFade::create(1.2f, BuyPlane::createScene()));
	if (tag == BUY_SKILL_TAG) Director::getInstance()->runWithScene(TransitionFade::create(1.2f, BuySkill::createScene()));

	//声音开关
	if (tag == MUSICBTN_TAG)
	{
		auto btn = static_cast<Button*>(pSender);
		if (btn->getTitleText() == "off")
		{
			Config::getInstance()->isAudio = false;
			CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
			btn->setTitleText("on");
		}else{
			Config::getInstance()->isAudio = true;
			CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("Music/mainMainMusic.mp3", true);
			btn->setTitleText("off");
		}
	}
}

void GameMenu::onKeyPressed(EventKeyboard::KeyCode keyCode, Event * event)
{
	if (keyCode == EventKeyboard::KeyCode::KEY_ESCAPE) {
		Director::getInstance()->end();
	}
}

Button * GameMenu::createButton(const std::string & image, Point pos, int tag, const std::string & titleText, int titleSize, Color3B titleColor)
{
	auto btn = Button::create(image);
	if (!btn) {
		log("Error: btn == NULL");
		return NULL;
	}
	btn->setPosition(pos);
	btn->setTitleText(titleText);
	btn->setTitleFontSize(titleSize);
	btn->setTitleColor(titleColor);
	if (tag != 0) btn->setTag(tag);
	btn->addClickEventListener(CC_CALLBACK_1(GameMenu::Callback, this));
	this->addChild(btn);
	return btn;
}

Sprite * GameMenu::createSprite(const std::string & image, Point pos, float scaleValue)
{
	auto sprite = Sprite::create(image);
	if (!sprite) {
		log("Error: sprite == NULL");
		return NULL;
	}
	sprite->setPosition(pos);
	sprite->setScale(scaleValue);
	this->addChild(sprite);
	return sprite;
}

Label * GameMenu::createLabel(std::string text, Point pos, Color3B color, Point AnchorPoint, const std::string & font, int fontSize, TextHAlignment hAlignment, int tag)
{
	if (text == "ShowHeroData")
	{
		text = LOAD("ATK", "UI.xml") + LOAD("ATK") + '\n';
		text += LOAD("HP", "UI.xml") + LOAD("HP") + '\n';
		text += LOAD("BulletCount", "UI.xml") + LOAD("BulletCount");
	}
	auto label = Label::create(text, font, fontSize, Size::ZERO, hAlignment);
	if (!label)
	{
		log("Error: label == NULL");
		return NULL;
	}
	label->setPosition(pos);
	label->setAnchorPoint(AnchorPoint);
	label->setColor(color);
	if (tag != 0) label->setTag(tag);
	this->addChild(label);
	return label;
}
