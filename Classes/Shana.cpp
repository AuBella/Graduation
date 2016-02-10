#include "Shana.h"
#include "AnimationUtil.h"
#include "GlobalCtrl.h"


Shana::Shana() {}


Shana::~Shana() {}


bool Shana::init() {
	bool bRet = false;
	do 
	{
		CC_BREAK_IF( !Role::init() );

		//设置精灵
		this->setSprite( CCSprite::create( "$shana_1.png", CCRect( 0, 0, 55, 62 ) ) );
		this->addChild( getSprite() );
		//初始化各种动画
		CCAnimation* standAnimn = AnimationUtil::getAnimation( "$shana_1.png", 4, 4 );
		setStandAnimation( CCRepeatForever::create( CCAnimate::create( standAnimn ) ) );

		CCAnimation* runAnimn = AnimationUtil::getAnimation( "$shana_forward.png", 8, 8 );
		setRunAnimation( CCRepeatForever::create( CCAnimate::create( runAnimn ) ) );

		CCAnimation* deadAnimn = AnimationUtil::getAnimation( "$shana_dead.png", 3, 3 );
		setDeadAnimation( CCRepeatForever::create( CCAnimate::create( deadAnimn ) ) );

		CCAnimation* hurtAnimn = AnimationUtil::getAnimation( "$shana_4.png", 2, 2 );
		setHurtAnimation( CCRepeatForever::create( CCAnimate::create( hurtAnimn ) ) );

		CCAnimation* skillA = AnimationUtil::getAnimation( "$shana_2.png", 7, 20 );
		setSkillA( CCSequence::create( CCAnimate::create( skillA ),
			CCCallFuncN::create(this, callfuncN_selector(Shana::attackCallbackFunc) ),
			CCCallFuncN::create(this, callfuncN_selector(Shana::createStandAnimCallback)), nullptr ));

		CCAnimation* skillB = AnimationUtil::getAnimation( "$shana_2extra1.png", 9, 24 );
		setSkillB( CCSequence::create( CCAnimate::create( skillB ),
			CCCallFuncN::create(this,callfuncN_selector( Shana::attackCallbackFunc ) ),
			CCCallFuncN::create(this,callfuncN_selector( Shana::createStandAnimCallback ) ), nullptr ) );

		CCAnimation* skillC = AnimationUtil::getAnimation( "$shana_2extra2.png", 8, 22 );
		setSkillC( CCSequence::create( CCAnimate::create( skillC ),
			CCCallFuncN::create(this, callfuncN_selector( Shana::attackCallbackFunc ) ),
			CCCallFuncN::create(this,callfuncN_selector( Shana::createStandAnimCallback ) ), nullptr ) );

		CCAnimation* skillD = AnimationUtil::getAnimation( "$shana_2extra3.png", 13, 15 );
		setSkillD( CCSequence::create( CCAnimate::create( skillD ),
			CCCallFuncN::create(this,callfuncN_selector( Shana::attackCallbackFunc ) ),
			CCCallFuncN::create( this,callfuncN_selector( Shana::createStandAnimCallback ) ), nullptr ) );

		CCAnimation* skillE = AnimationUtil::getAnimation( "$shana_2extra4.png", 8, 8 );
		setSkillE( CCSequence::create( CCAnimate::create( skillE ),
			CCCallFuncN::create(this, callfuncN_selector( Shana::attackCallbackFunc ) ),
			CCCallFuncN::create( this,callfuncN_selector( Shana::createStandAnimCallback ) ), nullptr ) );

		runStandAnimation();
		//runHurtAnimation();
		this->updateBox();
		this->setVelocity( CCPoint(0,0) );
		this->setCurSkillState( SKILL_NULL );
		this->setCanMutilAttack( false );

		this->scheduleUpdate();

		bRet = true;
	} while ( false );
	return bRet;
}


void Shana::attackCallbackFunc( CCNode* pSender ) {

}


void Shana::updateBox() {
	bool isFlipX = getSprite()->isFlipX();
	float x = getPositionX();
	float y = getPositionY();
	float width = 55.0f;
	float actualWidth = getSprite()->getContentSize().width;
	float height = getSprite()->getContentSize().height;

	if ( isFlipX ) {
		setHitBox( CCRect( (x - width / 2) - (actualWidth - width), y - height / 2, (actualWidth - width), height ) );
		setBodyBox( CCRect( x - width / 2, y - height / 2, width, height ) );
	} else {
		setHitBox( CCRect( x + width / 2, y - height / 2, actualWidth - width, height ) );
		setBodyBox( CCRect( x - width / 2, y - height / 2, width, height ) );
	}
}


void Shana::update( float delta ) {
	updateSelf();
	updateBox();
	centerViewOfPoint( getPosition() );
}


void Shana::updateSelf() { 
	if ( getCurState() == AC_RUN ) {
		CCSize visibleSize = CCEGLView::sharedOpenGLView()->getVisibleSize();
		CCPoint curPos = getPosition();
		CCPoint expectPos = curPos + getVelocity();
		CCPoint actualPos = expectPos;
		CCLOG("updateSelf %f %f\n ", expectPos.x, actualPos.x);
		float width = getSprite()->getContentSize().width;
		float height = getSprite()->getContentSize().height;

		float mapHeight = GlobalCtrl::getInstance()->tilemap->getTileSize().height * 4;
		float mapWidth = GlobalCtrl::getInstance()->tilemap->getContentSize().width;

		if ( expectPos.x - width / 2 < 0 || expectPos.x + width/2 > mapWidth ) {
			actualPos.x = curPos.x;
		}
		if ( expectPos.y - height / 2 < 0 || expectPos.y - height/2 > mapHeight) {
			actualPos.y = curPos.y;
		}
		this->setPosition( actualPos );
		this->setZOrder( visibleSize.height - getPositionY() );
	}
}


void Shana::centerViewOfPoint( CCPoint pos ) {
	CCSize visibleSize = CCEGLView::sharedOpenGLView()->getVisibleSize();
	auto map = GlobalCtrl::getInstance()->tilemap;

	float mapWidth = map->getMapSize().width*map->getTileSize().width;
	float mapHeight = map->getMapSize().height*map->getTileSize().height;

	float x = MAX( getPositionX(), visibleSize.width / 2 );
	float y = MAX( getPositionY(), visibleSize.height / 2 );

	x = MIN( x, mapWidth - visibleSize.width / 2 );
	y = MIN( y, mapHeight - visibleSize.height / 2 );

	CCPoint actualPos = CCPoint( x, y );
	CCPoint centerPos = CCPoint( visibleSize / 2 );
	CCPoint disPos = centerPos - actualPos;

	getParent()->setPosition( disPos );
}

//void Shana::onMove( CCPoint direction, float distance ) {
//	
//	CCLOG("Position %f %f\n",distance,getPositionX());
//	if ( getAllowMove() ) {
//		bool isFlippedX = (direction.x < 0? true : false);
//		//CCLOG("isFlippedX %f\n",isFlippedX);
//		getSprite()->setFlipX( isFlippedX );
//		distance = (distance>15.0 ? 3.0f : 1.0f);
//		setVelocity( direction*distance );
//		runRunAnimation();
//	}
//}

void Shana::onStop() {
	runStandAnimation();
}


void Shana::runSkillAAnimation() {
	Role::runSkillAAnimation();
	setCurSkillState( SKILL_A );
	setCanMutilAttack( true );
}


void Shana::runSkillBAnimation() {
	Role::runSkillBAnimation();
	setCurSkillState( SKILL_B );
}


void Shana::runSkillCAnimation() {
	Role::runSkillCAnimation();
	setCurSkillState( SKILL_C );
}


void Shana::runSkillDAnimation() {
	Role::runSkillDAnimation();
	setCurSkillState( SKILL_D );
}

void Shana::runSkillEAnimation() {
	Role::runSkillEAnimation();
	float width = getSprite()->getContentSize().width;
	float mapWidth = GlobalCtrl::getInstance()->tilemap->getContentSize().width;
	CCPoint curPos = getPosition();
	CCLOG("updateSelf %f\n ", curPos.x);
	double distance =min(mapWidth - width - curPos.x, 200);
	if(getSprite()->isFlipX())
		distance = -min(curPos.x - width, 200);
	CCLOG("%f %f %f\n",distance,width);
	CCMoveBy* move = CCMoveBy::create( 0.5f, CCPoint( distance, 0 ) );
	this->runAction( move );
	setCurSkillState( SKILL_NULL );
	setCanMutilAttack( false );
}