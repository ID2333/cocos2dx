
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

	//切换GameOver场景
	void updateOne(float dt);
	//子弹和敌机碰撞检测
	void update(float dt);
	//地图滚动
	void mapUpdate(float dt);
	//敌机刷新
	void enemyCountUpdate(float dt);
	
	//暂停和继续回调
	void pauseCallBack(Object *pSender);
};
#endif