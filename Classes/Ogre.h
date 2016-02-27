#include"cocos2d.h"
#include"Role.h"
#include"AnimationUtil.h"
#include"GlobalCtrl.h"
#include"Shana.h"
#include <stdio.h>  
#include <stdlib.h>  
#include <time.h>  
#include<math.h>
#include<iostream>

USING_NS_CC;

class Ogre: public Role{
public:
	Ogre(void);
	~Ogre(void);
	virtual bool init();

	void updateMonster(float delta);
	void update(float delta);
	bool faceDirecton;
	bool leftInTheMonster;
	void enterSafeArea();
	void enterAttackArea(float x, float y);
	CCSprite* GetSprite();
	void StartListen();
	void HurtAnimation();
	bool isHurt;
	bool isDead;
	bool isAttack;
	CREATE_FUNC(Ogre);
	int flag;	
private:
	float  dis;
	Shana* shana;
	void DeadEnd(CCNode* pSender);
	CCSprite* m_MonsterSprite;
	CCTMXTiledMap* tileMap;
	int effectId;
	void attackCallbackFunc( CCNode* pSender );
	void HurtEnd( CCNode* pSender);
	void initstatus();
};