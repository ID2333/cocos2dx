
#ifndef _GameOver_H_
#define _GameOver_H_

#include "cocos2d.h"
USING_NS_CC;

class GameOver : public Layer
{
public:
	GameOver();
	~GameOver();

	static Scene* createScene();
	virtual bool init();
	CREATE_FUNC(GameOver);

	void CallBackMenu();
};

#endif
