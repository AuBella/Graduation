#include "Shana.h"
#include "AnimationUtil.h"
#include "GlobalCtrl.h"


Shana::Shana() {
	isHurt = false;
	isRunning = false;
	shanaisAttack = false;
	redBlood = 100;
	isDead = false;
}


Shana::~Shana() {}


bool Shana::init() {
	if( !Role::init() )
		return false;
	m_MonsterSprite =CCSprite::create( "$legendaryswordsman_1.png", CCRect( 0, 0, 69, 62 ));
	this->setSprite(m_MonsterSprite );
	this->addChild( getSprite() );
	
	CCAnimation* standAnimn = AnimationUtil::getAnimation( "$legendaryswordsman_1.png", 3, 6 );
	setStandAnimation( CCRepeatForever::create( CCAnimate::create( standAnimn ) ) );

	CCAnimation* runAnimn = AnimationUtil::getAnimation( "$legendaryswordsman_forward.png", 8, 8 );
	setRunAnimation( CCRepeatForever::create( CCAnimate::create( runAnimn ) ) );

	CCAnimation* deadAnimn = AnimationUtil::getAnimation( "$legendaryswordsman_dead.png", 3, 3 );
	setDeadAnimation( ( CCSequence::create(CCAnimate::create( deadAnimn ),CCCallFuncN::create(this, callfuncN_selector(Shana::DeadEnd) ), NULL) ) );


	CCAnimation* hurtAnimn = AnimationUtil::getAnimation( "$legendaryswordsman_4.png", 1, 4 );
	setHurtAnimation( CCSequence::create(CCAnimate::create( hurtAnimn ),
		CCCallFuncN::create(this, callfuncN_selector(Shana::HurtEnd)), NULL ));

	CCAnimation* skillA = AnimationUtil::getAnimation( "$legendaryswordsman_2.png", 8, 16 );
	setSkillA( CCSequence::create( CCAnimate::create( skillA ),
		CCCallFuncN::create(this, callfuncN_selector(Shana::attackCallbackFunc1) ),
		CCCallFuncN::create(this, callfuncN_selector(Shana::createStandAnimCallback)), NULL ));

	CCAnimation* skillB = AnimationUtil::getAnimation( "$legendaryswordsman_2extra1.png", 7, 18 );
	setSkillB( CCSequence::create( CCAnimate::create( skillB ),
		CCCallFuncN::create(this,callfuncN_selector( Shana::attackCallbackFunc1 ) ),
		CCCallFuncN::create(this,callfuncN_selector( Shana::createStandAnimCallback ) ), NULL ) );

	CCAnimation* skillC = AnimationUtil::getAnimation( "$legendaryswordsman_2extra2.png", 8, 16 );
	setSkillC( CCSequence::create( CCAnimate::create( skillC ),
		CCCallFuncN::create(this, callfuncN_selector( Shana::attackCallbackFunc1 ) ),
		CCCallFuncN::create(this,callfuncN_selector( Shana::createStandAnimCallback ) ), NULL ) );

	CCAnimation* skillD = AnimationUtil::getAnimation( "$legendaryswordsman_2extra3.png", 9, 16 );
	setSkillD( CCSequence::create( CCAnimate::create( skillD ),
		CCCallFuncN::create(this,callfuncN_selector( Shana::attackCallbackFunc1 ) ),
		CCCallFuncN::create( this,callfuncN_selector( Shana::createStandAnimCallback ) ), NULL ) );

	CCAnimation* skillE = AnimationUtil::getAnimation( "$legendaryswordsman_2extra4.png", 9, 9 );
	setSkillE( CCSequence::create( CCAnimate::create( skillE ),
		CCCallFuncN::create(this, callfuncN_selector( Shana::attackCallbackFunc1 ) ),
		CCCallFuncN::create( this,callfuncN_selector( Shana::createStandAnimCallback ) ), NULL ) );
	return true;
}

void Shana::StartListen(){
	runStandAnimation();
	this->scheduleUpdate();
	this->updateBox();
	this->setVelocity( CCPoint(0,0) );
	this->setCurSkillState( SKILL_NULL );
	this->setCanMutilAttack( false );
}

void Shana::attackCallbackFunc1( CCNode* pSender ) {
	shanaisAttack = false;
}

void Shana::HurtAnimation(){
	redBlood -= 10;
	redBlood < 0?0:redBlood;
	int blood = 1000+redBlood;
	CCNotificationCenter::sharedNotificationCenter()->postNotification("Hurt",(CCObject *)( blood));
	if(redBlood <= 0){
		isDead = true;
		int effectId = CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sound/0052_0000.wav");
		runDeadAnimation();
	}else{
		CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sound/0051_0000.mp3");
		this->runHurtAnimation();
	}
}

void Shana::HurtEnd( CCNode* pSender){
	isHurt = false;
	shanaisAttack = false;
	isRunning = false;
	runStandAnimation();	
	setCurSkillState( SKILL_NULL );
	setCanMutilAttack( false );
	shanaisAttack = false;
}


void Shana::DeadEnd(CCNode* pSender){
	if(isDead){
		this->unschedule(schedule_selector(Shana::update));
	}
 }

void Shana::createStandAnimCallback(CCNode* pSender){
	runStandAnimation();
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
	CCTMXTiledMap* map = GlobalCtrl::getInstance()->tilemap;

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

void Shana::onStop() {
	runStandAnimation();
}


void Shana::runSkillAAnimation() {
	 CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sound/0046_0000.mp3");
	Role::runSkillAAnimation();
	setCurSkillState( SKILL_A );
	setCanMutilAttack( true );
}


void Shana::runSkillBAnimation() {
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sound/0047_0000.mp3");
	Role::runSkillBAnimation();
	setCurSkillState( SKILL_B );
}


void Shana::runSkillCAnimation() {
	 CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sound/0041_0000.mp3");
	Role::runSkillCAnimation();
	setCurSkillState( SKILL_C );
}


void Shana::runSkillDAnimation() {
	 CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sound/004D_0000.mp3");
	Role::runSkillDAnimation();
	setCurSkillState( SKILL_D );
}

void Shana::runSkillEAnimation() {
	 CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sound/0045_0000.mp3");
	Role::runSkillEAnimation();
	float width = getSprite()->getContentSize().width;
	float mapWidth = GlobalCtrl::getInstance()->tilemap->getContentSize().width;
	CCPoint curPos = getPosition();
	
	double distance =mapWidth - width - curPos.x< 200?mapWidth - width - curPos.x:200;
	if(getSprite()->isFlipX())
		distance = -(curPos.x - width< 200?curPos.x - width:200);
	CCMoveBy* move = CCMoveBy::create( 0.5f, CCPoint( distance, 0 ) );
	this->runAction( move );
	setCurSkillState( SKILL_NULL );
	setCanMutilAttack( false );
	shanaisAttack = false;
}