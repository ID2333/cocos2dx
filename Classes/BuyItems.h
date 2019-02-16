
#ifndef _BuyItems_H_
#define _BuyItems_H_

#include "cocos2d.h"
USING_NS_CC;

class BuyItems : public Layer
{
public:
	static Scene *createScene();
	virtual bool init();
	CREATE_FUNC(BuyItems);

	void callBack(Object *pSender);
	void MsgMenu(const std::string &text);
};

#endif
