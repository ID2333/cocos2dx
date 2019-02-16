
#ifndef _PlaneBase_H_
#define _PlaneBase_H_

#include "cocos2d.h"
using namespace cocos2d;

class PlaneBase : public Sprite
{
public:
	//����
	virtual void attack() = 0;
	//����
	virtual void hurt(int value) = 0;
	//����
	virtual int hp() = 0;
	//����
	virtual void death() = 0;
	//��ײ��Χ
	virtual Rect collideRect() = 0;
	//��ȡ���� 0:Ӣ�� 1:�л� 3:boss
	virtual int isObject() = 0;
	//��ȡ������
	virtual int getAKT() = 0;
	//����
	virtual int getScoreValue() = 0;
	//��ײ�˺�
	virtual int getCollideValue() = 0;
};
#endif // !_PlaneBase_H_
