#include "Config.h"
#include "Enemy.h"
#include "GameLevelEditors.h"

static Config *g_config = NULL;

Vector<Bullet*> heroBullet;
Vector<Bullet*> enemyBullet;
Vector<PlaneBase*> enemyCount;

Config::Config() : scoreValue(0), km(0), defenseSkill(false), isWin(false), isAudio(true), isBgAudio(true)
{
	EnemyType temp;
	temp.type = 0;
	temp.textureName = "E0.png";
	temp.bulletType = "W2.png";
	temp.scoreValue = 15;
	temp.moveType = 5;
	temp.hp = 1;
	temp.ATK = 2;
	temp.moveTime = 1.0f;
	m_enemyTypes.push_back(temp);

	temp.type = 1;
	temp.textureName = "E1.png";
	temp.bulletType = "W2.png";
	temp.scoreValue = 30;
	temp.moveType = 8;
	temp.hp = 2;
	temp.ATK = 2;
	temp.moveTime = 1.0f;
	m_enemyTypes.push_back(temp);

	temp.type = 2;
	temp.textureName = "E2.png";
	temp.bulletType = "W2.png";
	temp.scoreValue = 60;
	temp.moveType = 10;
	temp.hp = 4;
	temp.ATK = 3;
	temp.moveTime = 1.0f;
	m_enemyTypes.push_back(temp);

	temp.type = 3;
	temp.textureName = "E3.png";
	temp.bulletType = "W2.png";
	temp.scoreValue = 90;
	temp.moveType = 15;
	temp.hp = 6;
	temp.ATK = 3;
	temp.moveTime = 2.0f;
	m_enemyTypes.push_back(temp);

	temp.type = 4;
	temp.textureName = "E4.png";
	temp.bulletType = "W2.png";
	temp.scoreValue = 120;
	temp.moveType = 20;
	temp.hp = 10;
	temp.ATK = 5;
	temp.moveTime = 1.5f;
	m_enemyTypes.push_back(temp);

	temp.type = 5;
	temp.textureName = "E5.png";
	temp.bulletType = "W2.png";
	temp.scoreValue = 150;
	temp.moveType = 30;
	temp.hp = 15;
	temp.ATK = 5;
	temp.moveTime = 1.0f;
	m_enemyTypes.push_back(temp);
}

Config::~Config()
{
}

Config * Config::getInstance()
{
	if (!g_config)
	{
		g_config = new Config;
	}
	return g_config;
}

std::vector<EnemyType> Config::getEnemyType()
{
	return m_enemyTypes;
}

void Config::initUserDefault()
{
	auto userDefault = UserDefault::getInstance();
	if (!userDefault->getBoolForKey("init"))
	{
		//初始化
		userDefault->setBoolForKey("init", true);

		//技能数据
		userDefault->setIntegerForKey("Skill_1_Level", 1);
		userDefault->setIntegerForKey("Skill_1_Time", 3);
		userDefault->setIntegerForKey("Skill_1_CD", 30);
		userDefault->setIntegerForKey("Skill_1_BuyMoney", 5000);
		userDefault->setIntegerForKey("Skill_1_UpMoney", 1000);

		userDefault->setIntegerForKey("Skill_2_Level", 0);
		userDefault->setIntegerForKey("Skill_2_Time", 3);
		userDefault->setIntegerForKey("Skill_2_CD", 25);
		userDefault->setIntegerForKey("Skill_2_BuyMoney", 5000);
		userDefault->setIntegerForKey("Skill_2_UpMoney", 1500);

		//UI
		userDefault->setIntegerForKey("Money", 0);
		userDefault->setIntegerForKey("Level", 1);

		//飞机数据
		userDefault->setIntegerForKey("ATK", 1);
		userDefault->setIntegerForKey("HP", 100);
		userDefault->setIntegerForKey("BulletCount", 2);
		userDefault->setIntegerForKey("ATK_Money", 10000);
		userDefault->setIntegerForKey("HP_Money", 10000);
		userDefault->setIntegerForKey("BulletCount_Money", 20000);

		//道具数据
		userDefault->setIntegerForKey("ATK_ItemCount", 0);
		userDefault->setIntegerForKey("HP_ItemCount", 0);
		userDefault->setIntegerForKey("BossHP_ItemCount", 0);
		userDefault->setIntegerForKey("Blood_ItemCount", 0);

		//保存
		userDefault->flush();
	}
}

std::string Config::loadFileData(const std::string & key, const std::string & file)
{
	std::string str;
	//UI文件
	if (file == "UI.xml")
	{
		tinyxml2::XMLDocument *Doc = new tinyxml2::XMLDocument();
		auto pBuffer = FileUtils::getInstance()->getStringFromFile(file);
		Doc->Parse(pBuffer.c_str());
		tinyxml2::XMLElement *root = Doc->RootElement();
		//遍历节点
		for (auto rootElenemt = root->FirstChildElement(); rootElenemt; rootElenemt = rootElenemt->NextSiblingElement())
		{
			if (rootElenemt->Attribute(key.c_str()))
			{
				str = rootElenemt->Attribute(key.c_str());
				log("%s:%s",key.c_str(), rootElenemt->Attribute(key.c_str()));
				CC_SAFE_DELETE(Doc);
				break;
			}
		}
	}
	else {
		str = UserDefault::getInstance()->getStringForKey(key.c_str());
	}
	return str;
}

void Config::fileSave(const std::string & key, const int value)
{
	UserDefault::getInstance()->setIntegerForKey(key.c_str(), value);
	UserDefault::getInstance()->flush();
}

