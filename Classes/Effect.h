
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

	//��ըЧ��
	void explode(Node *pSender,Point pos);
	//�ӵ���ըЧ��
	void bulletExplode(Node *pSender,Point pos);
	//��ѪƮ��Ч��
	Label* hpEffect(Point pos,int hpValue);
};

#endif
