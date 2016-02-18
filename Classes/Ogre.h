#include"cocos2d.h"
#include"Role.h"
#include"AnimationUtil.h"
#include"GlobalCtrl.h"
#include"Shana.h"
#include <stdio.h>  
#include <stdlib.h>  
#include <time.h>  
#include<math.h>
#include "ProgressView.h"
#include<iostream>

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
	//�����˶��ķ���
	bool faceDirecton;
	bool leftInTheMonster;
	//�ڿ��ӷ�Χ�ڣ��������Ӣ���˶�
	void enterSafeArea();
	void enterAttackArea(float x, float y);
	//����Ӣ��
	CCSprite* GetSprite();
	void StartListen();
	void HurtAnimation();
	bool isHurt;
	bool isDead;
	bool isAttack;
	CREATE_FUNC(Ogre);
	int flag;	
private:
	float  dis;//��ǰ�����Ӣ�۵ľ���
	Shana* shana;
	void DeadEnd(CCNode* pSender);
	CCSprite* m_MonsterSprite;//���ﾫ��
	ProgressView*  Monster_xue;//����Ѫ��
	CCTMXTiledMap* tileMap;
	int effectId;
	void attackCallbackFunc( CCNode* pSender );
	void HurtEnd( CCNode* pSender);
	void initstatus();
};