
#ifndef _GameScene_H_
#define _GameScene_H_

#include "cocos2d.h"
#include "Hero.h"
#include "Enemy.h"
#include "GameLevelEditors.h"
#include "Boss.h"
using namespace cocos2d;

class GameScene : public Layer
{
private:
	Sprite *m_bg1;
	Sprite *m_bg2;
	TMXTiledMap *m_TiledMap1;
	TMXTiledMap *m_TiledMap2;
	Size winSize;
	LabelBMFont *m_scroe;
	LabelBMFont *m_distance;
	Hero *m_hero;
	Enemy *m_enemy;
	bool m_isOver;
	GameLevelEditors gameLevel;
	Boss *m_Boss;
public:
	GameScene();
	~GameScene();
	
	void onExit();
	static Scene* createScene();
	virtual bool init();
	CREATE_FUNC(GameScene);

	//�л�GameOver����
	void updateOne(float dt);
	//�ӵ��͵л���ײ���
	void update(float dt);
	//��ͼ����
	void mapUpdate(float dt);
	//�л�ˢ��
	void enemyCountUpdate(float dt);
	
	//��ͣ�ͼ����ص�
	void pauseCallBack(Object *pSender);
};
#endif