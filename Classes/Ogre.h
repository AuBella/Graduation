#include"cocos2d.h"
#include"Role.h"
#include"AnimationUtil.h"
#include"GlobalCtrl.h"
#include"Shana.h"

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
	
	void CanSeeArea();
	void updateMonster(float delta);
	void update(float delta);
	void onMove( CCPoint direction, float distance );
	CREATE_FUNC(Ogre);
private:
	float  dis;//当前怪物和英雄的距离
	Shana* shana;
	CCTMXTiledMap* tileMap;
};