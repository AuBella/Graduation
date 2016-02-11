#include "Role.h"


Role::Role():
	_sprite(nullptr),
	_runAnimn(nullptr),
	_standAnimn(nullptr),
	_hurtAnimn(nullptr),
	_velocity(ccp(0,0)),
	_deadAnimn(nullptr),
	_allowMove(true),
	_skillA(nullptr),
	_skillB(nullptr),
	_skillC(nullptr),
	_skillD(nullptr),
	_skillE(nullptr)
{}


Role::~Role() {
	CC_SAFE_RELEASE_NULL( _sprite );
	CC_SAFE_RELEASE_NULL( _runAnimn );
	CC_SAFE_RELEASE_NULL( _standAnimn );
	CC_SAFE_RELEASE_NULL( _deadAnimn );
	CC_SAFE_RELEASE_NULL( _hurtAnimn );
	CC_SAFE_RELEASE_NULL( _skillA );
	CC_SAFE_RELEASE_NULL( _skillB );
	CC_SAFE_RELEASE_NULL( _skillC );
	CC_SAFE_RELEASE_NULL( _skillD );
	CC_SAFE_RELEASE_NULL( _skillE );
}


bool Role::init() {
	bool bRet = false;
	do 
	{
		CC_BREAK_IF( !CCNode::init() );
		bRet = true;
	} while ( false );
	return bRet;
}


bool Role::changeState( RoleActionState state ) {
	bool bRet = false;
	do 
	{
		CC_BREAK_IF( getCurState() == state );
		setCurState( state );
		bRet = true;
	} while ( false );

	return bRet;
}


void Role::runStandAnimation() {
	if ( changeState( AC_STAND ) ) {
		getSprite()->stopAllActions();
		getSprite()->runAction( getStandAnimation() );
		//getSprite()->setOpacity(80);
		setAllowMove( true );
	}
}


void Role::runDeadAnimation() {
	if ( changeState( AC_DEAD ) ) {
		getSprite()->stopAllActions();
		getSprite()->runAction( getDeadAnimation() );
		setAllowMove( false );
	}
}


void Role::runRunAnimation() {
	if ( changeState( AC_RUN ) ) {
		getSprite()->stopAllActions();
		getSprite()->runAction( getRunAnimation() );
		setAllowMove( true );
	}
}

void Role::runHurtAnimation() {
	if ( changeState( AC_HURT ) ) {
		getSprite()->stopAllActions();
		getSprite()->runAction( getHurtAnimation() );
		setAllowMove( true );
	}
}


void Role::runSkillAAnimation() {
	if ( changeState( AC_SKILL_A ) ) {
		setAllowMove( false );
		getSprite()->stopAllActions();
		getSprite()->runAction( getSkillA() );
	}
}


void Role::runSkillBAnimation() {
	if ( changeState( AC_SKILL_B ) ) {
		setAllowMove( false );
		getSprite()->stopAllActions();
		getSprite()->runAction( getSkillB() );
	}
}


void Role::runSkillCAnimation() {
	if ( changeState( AC_SKILL_C ) ) {
		setAllowMove( false );
		getSprite()->stopAllActions();
		getSprite()->runAction( getSkillC() );
	}
}

void Role::runSkillDAnimation() {
	if ( changeState( AC_SKILL_D ) ) {
		setAllowMove( false );
		getSprite()->stopAllActions();
		getSprite()->runAction( getSkillD() );
	}
}

void Role::runSkillEAnimation() {
	if ( changeState( AC_SKILL_E ) ) {
		setAllowMove( false );
		getSprite()->stopAllActions();
		getSprite()->runAction( getSkillE() );
	}
}


void Role::onMove( CCPoint direction, float distance ) {
	
	CCLOG("Position %f %f\n",distance,getPositionX());
	if ( getAllowMove() ) {
		bool isFlippedX = (direction.x < 0? true : false);
		//CCLOG("isFlippedX %f\n",isFlippedX);
		getSprite()->setFlipX( isFlippedX );
		distance = (distance>15.0 ? 3.0f : 1.0f);
		setVelocity( direction*distance );
		runRunAnimation();
	}
}

void Role::createStandAnimCallback( CCNode* pSender ) {
	runStandAnimation();
}