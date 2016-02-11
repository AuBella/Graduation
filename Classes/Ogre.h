#include"cocos2d.h"
#include"Role.h"
#include"AnimationUtil.h"
#include"GlobalCtrl.h"
#include"Shana.h"
#include <stdio.h>  
#include <stdlib.h>  
#include <time.h>  
#include "ProgressView.h"

USING_NS_CC;
//enum SkillState1 {
//	SKILL_NULL1 = 0,
//	SKILL_A1,
//	SKILL_B1,
//};

class Ogre: public Role{
public:
	Ogre(void);
	~Ogre(void);
	virtual bool init();

	void updateMonster(float delta);
	void update(float delta);
	//怪物运动的方向
	bool faceDirecton;
	bool leftInTheMonster;
	//在可视范围内，怪物跟随英雄运动
	void enterSafeArea();
	void enterAttackArea(float x, float y);
	//返回英雄
	CCSprite* GetSprite();
	void StartListen();
	CREATE_FUNC(Ogre);
private:
	float  dis;//当前怪物和英雄的距离
	Shana* shana;
	CCSprite* m_MonsterSprite;//怪物精灵
	ProgressView*  Monster_xue;//怪物血条
	CCTMXTiledMap* tileMap;
};