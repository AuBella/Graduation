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
	//�����˶��ķ���
	bool faceDirecton;
	bool leftInTheMonster;
	//�ڿ��ӷ�Χ�ڣ��������Ӣ���˶�
	void enterSafeArea();
	void enterAttackArea(float x, float y);
	//����Ӣ��
	CCSprite* GetSprite();
	void StartListen();
	CREATE_FUNC(Ogre);
private:
	float  dis;//��ǰ�����Ӣ�۵ľ���
	Shana* shana;
	CCSprite* m_MonsterSprite;//���ﾫ��
	ProgressView*  Monster_xue;//����Ѫ��
	CCTMXTiledMap* tileMap;
};