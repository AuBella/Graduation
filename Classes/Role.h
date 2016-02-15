#pragma once

#include "cocos2d.h"
#include"GlobalCtrl.h"
USING_NS_CC;

enum RoleActionState {
	AC_STAND = 0,
	AC_DEAD,
	AC_RUN,
	AC_HURT,
	AC_SKILL_A,
	AC_SKILL_B,
	AC_SKILL_C,
	AC_SKILL_D,
	AC_SKILL_E
};


class Role : public CCNode{
public:
	Role();
	~Role();
	virtual bool init();


	//角色精灵
	CC_SYNTHESIZE_RETAIN( CCSprite*, _sprite, Sprite );
	CC_SYNTHESIZE( bool, _allowMove, AllowMove );

	//角色拥有的动画
	CC_SYNTHESIZE_RETAIN( CCAction*, _runAnimn, RunAnimation );
	CC_SYNTHESIZE_RETAIN( CCAction*, _standAnimn, StandAnimation );
	CC_SYNTHESIZE_RETAIN( CCAction*, _deadAnimn, DeadAnimation );
	CC_SYNTHESIZE_RETAIN( CCAction*, _hurtAnimn, HurtAnimation );
	CC_SYNTHESIZE_RETAIN( CCAction*, _skillA, SkillA );
	CC_SYNTHESIZE_RETAIN( CCAction*, _skillB, SkillB );
	CC_SYNTHESIZE_RETAIN( CCAction*, _skillC, SkillC );
	CC_SYNTHESIZE_RETAIN( CCAction*, _skillD, SkillD );
	CC_SYNTHESIZE_RETAIN( CCAction*, _skillE, SkillE );

	//角色状态
	CC_SYNTHESIZE( RoleActionState, _curState, CurState );

	//碰撞矩形
	CC_SYNTHESIZE( CCRect, _hitBox, HitBox );
	CC_SYNTHESIZE( CCRect, _bodyBox, BodyBox );
	CC_SYNTHESIZE( CCPoint, _velocity, Velocity );

public:
	void runStandAnimation();
	void runDeadAnimation();
	void runRunAnimation();
	void runHurtAnimation();

	virtual void runSkillAAnimation();
	virtual void runSkillBAnimation();
	virtual void runSkillCAnimation();
	virtual void runSkillDAnimation();
	virtual void runSkillEAnimation();

	
	virtual void onMove( CCPoint direction, float distance );
protected:
	bool changeState( RoleActionState state );
	void createStandAnimCallback(CCNode* pSender);

};

