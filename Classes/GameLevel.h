
#ifndef _GameLevel_H_
#define _GameLevel_H_
#include "cocos2d.h"
USING_NS_CC;

class GameLevel : public Layer
{
private:
	LabelBMFont * m_gameLevel_1;
	int m_index;
public:
	GameLevel();
	~GameLevel();
	static Scene *createScene();
	virtual bool init();
	CREATE_FUNC(GameLevel);

	void start(Object *pSender);
	void itemCallBack(Object *pSender);
	void nextCallBack();
	void lastCallBack();
	void backCallBack();

	void MsgMenu(const std::string &text);
};
#endif
