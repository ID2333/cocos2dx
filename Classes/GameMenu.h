
#ifndef _GameMenu_H_
#define _GameMenu_H_

#include "cocos2d.h"
#include "ui\UIButton.h"
USING_NS_CC;
using namespace ui;
using namespace std;


class GameMenu : public Layer{
public:
	static Scene* createScene();
	virtual bool init();
	CREATE_FUNC(GameMenu);

	void Callback(Object *pSender);
	void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);

	Button* createButton(const string &image, Point pos, int tag = 0, const std::string &titleText = " ", int titleSize = 20,
		Color3B titleColor = Color3B(135, 206, 250));
	Sprite* createSprite(const string &image, Point pos, float scaleValue = 1.0);
	Label* createLabel(std::string text, Point pos, Color3B color, Point AnchorPoint = Point(0.5, 0.5), const std::string &font = "Arial", int fontSize = 20,
		TextHAlignment hAlignment = TextHAlignment::LEFT, int tag = 0);
};
#endif

