
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
	//��������
	bool isHpAdd;
	//Boss��������
	bool isBossHp;
	//����������
	bool isATK;
	//��Ѫ
	bool isBlood;

	//����
	int km;
	//����
	int scoreValue;
	//����ˢ��ʱ��
	float enemyUpdateTime;
	//�ؿ�
	int level;
	//defense����
	bool defenseSkill;
	//�Ƿ�ͨ��
	bool isWin;
	//���ֿ���
	bool isAudio;
	//�������ֿ���
	bool isBgAudio;
public:

	~Config();
	static Config* getInstance();
	std::vector<EnemyType> getEnemyType();

	//��ʼ���û�����
	void initUserDefault();
	//�����ļ�����
	std::string loadFileData(const std::string & key, const std::string &file = "");
	//�����ļ�����
	void fileSave(const std::string &key, const int value);
};
#endif // !_Config_H_

