
#ifndef _BuyPlane_H_
#define _BuyPlane_H_

#include "cocos2d.h"
USING_NS_CC;

class BuyPlane : public Layer
{
public:
	static Scene *createScene();
	virtual bool init();
	CREATE_FUNC(BuyPlane);

	void callBack(Object *pSender);
	void MsgMenu(const std::string &text);
};
#endif // !_BuyPlane_H_

