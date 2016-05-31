#pragma once

#include "Role.h"

enum SkillState {
	SKILL_NULL = 0,
	SKILL_A,
	SKILL_B,
	SKILL_C,
	SKILL_D
};

class Shana : public Role{
public:
	Shana();
	~Shana();
	virtual bool init();
	CREATE_FUNC( Shana );
	void onStop();

	CC_SYNTHESIZE( SkillState, _curSkillState, CurSkillState );
	CC_SYNTHESIZE( bool, _canMutilAtk, CanMutilAttack );

	virtual void runSkillAAnimation();
	virtual void runSkillBAnimation();
	virtual void runSkillCAnimation();
	virtual void runSkillDAnimation();
	/*virtual*/ void runSkillEAnimation();
	
	bool isHurt;
	bool isRunning;
	bool shanaisAttack;
	void HurtAnimation(int num);
	void HurtEnd();
	void StartListen();
	int userbloodnum;
private:
	void updateBox();
	virtual void update( float delta );
	void updateSelf();
	void HurtEnd( CCNode* pSender);
	void centerViewOfPoint( CCPoint pos );
	void attackCallbackFunc1( CCNode* pSender );
	void createStandAnimCallback(CCNode* pSender);
	void DeadEnd(CCNode* pSender);
	CCSprite* m_MonsterSprite;
};

