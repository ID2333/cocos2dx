
#ifndef _BuySkill_H_
#define _BuySkill_H_

#include "cocos2d.h"
#include "GameMenu.h"
USING_NS_CC;

class BuySkill : public Layer
{
private:
	Sprite * buySprite;
public:
	static Scene* createScene();
	virtual bool init();
	CREATE_FUNC(BuySkill);

	void callBack(Object *pSender);
	void btnCallBack(Object * pSender,int tag);

	void chageFileItems(std::string keyName);
	void MsgMenu(const std::string &text);
};

#endif
