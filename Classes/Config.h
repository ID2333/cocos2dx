
#ifndef _Config_H_
#define _Config_H_

#include "cocos2d.h"
#include "Bullet.h"
#include "tinyxml2\tinyxml2.h"
USING_NS_CC;

#define LOAD Config::getInstance()->loadFileData
#define SAVE Config::getInstance()->fileSave

class Enemy;
extern Vector<Bullet*> heroBullet;
extern Vector<Bullet*> enemyBullet;
extern Vector<PlaneBase*> enemyCount;

struct EnemyType
{
	int type;
	std::string textureName;
	std::string bulletType;
	int moveType;
	int hp;
	int scoreValue;
	int ATK;
	float moveTime;
};

class Config : public Node
{
private:
	std::vector<EnemyType> m_enemyTypes;
	Config();
public:
	//生命增加
	bool isHpAdd;
	//Boss生命减少
	bool isBossHp;
	//攻击力增加
	bool isATK;
	//吸血
	bool isBlood;

	//距离
	int km;
	//分数
	int scoreValue;
	//敌人刷新时间
	float enemyUpdateTime;
	//关卡
	int level;
	//defense技能
	bool defenseSkill;
	//是否通关
	bool isWin;
	//音乐开关
	bool isAudio;
	//背景音乐开关
	bool isBgAudio;
public:

	~Config();
	static Config* getInstance();
	std::vector<EnemyType> getEnemyType();

	//初始化用户数据
	void initUserDefault();
	//加载文件数据
	std::string loadFileData(const std::string & key, const std::string &file = "");
	//保存文件数据
	void fileSave(const std::string &key, const int value);
};
#endif // !_Config_H_

