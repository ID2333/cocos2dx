
#ifndef _Effect_H_
#define _Effect_H_

#include "cocos2d.h"
USING_NS_CC;

class Effect : public Node
{
private:
	Sprite * sprite;
public:
	Effect();
	~Effect();
	static Effect* create();
	static void loadExplosion();

	//爆炸效果
	void explode(Node *pSender,Point pos);
	//子弹爆炸效果
	void bulletExplode(Node *pSender,Point pos);
	//扣血飘字效果
	Label* hpEffect(Point pos,int hpValue);
};

#endif
