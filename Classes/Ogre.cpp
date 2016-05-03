#include"Ogre.h"

Ogre::Ogre(){
	faceDirecton = true;
	leftInTheMonster = true;
	isHurt = false;
	isDead = false;
	isAttack = false;
	redBlood = 100;
	ogreAttacknum = rand() % 5;
	flag = 0;
};

void Ogre::initstatus(){
	isHurt = false;
	isAttack = false;
	flag = -100;
}

Ogre::~Ogre(){};
CCSprite* Ogre::GetSprite()
{
	return m_MonsterSprite;
}
bool Ogre::init(){
	
		if( !Role::init())
			return false;
		//设置精灵
		m_MonsterSprite = CCSprite::create( "monster_2_stand.png", CCRect( 0, 0, 86, 97 ) );
		m_MonsterSprite->setScale(0.6);
		this->setSprite( m_MonsterSprite );
		this->addChild( getSprite() );
		this->setPosition(240, 200);
		//初始化各种动画
		CCAnimation* standAnimn = AnimationUtil::getAnimation( "monster_2_stand.png", 3, 3 );
		setStandAnimation( CCRepeatForever::create( CCAnimate::create( standAnimn ) ) );

		CCAnimation* runAnimn = AnimationUtil::getAnimation( "monster_2_run.png", 4, 4 );
		setRunAnimation( CCRepeatForever::create( CCAnimate::create( runAnimn ) ) );

		CCAnimation* deadAnimn = AnimationUtil::getAnimation( "monster_2_attack_1.png", 1, 1 );
		setDeadAnimation( CCRepeatForever::create( CCSequence::create(CCAnimate::create( deadAnimn ),CCCallFuncN::create(this, callfuncN_selector(Ogre::DeadEnd) ), NULL) ) );

		CCAnimation* hurtAnimn = AnimationUtil::getAnimation( "monster_2_hurt.png", 1, 4 );
		setHurtAnimation(CCRepeatForever::create( CCSequence::create(CCAnimate::create( hurtAnimn ),/*CCAnimate::create( standAnimn ),*/
			CCCallFuncN::create(this, callfuncN_selector(Ogre::HurtEnd)), NULL )));

		CCAnimation* skillA = AnimationUtil::getAnimation( "monster_2_attack.png", 3, 6 );
		setSkillA( CCSequence::create( CCAnimate::create( skillA ),
			CCCallFuncN::create(this, callfuncN_selector(Ogre::attackCallbackFunc) ),
			CCCallFuncN::create(this, callfuncN_selector(Ogre::createStandAnimCallback)), NULL ));
		runStandAnimation();
	return true;
};

 void Ogre::HurtAnimation(int num){
	if(isDead)
		return;
	isHurt = true;
	redBlood-=10;
	effectId = CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sound/0312_00EB.wav");
	this->runHurtAnimation(); 
 }

 void Ogre::HurtEnd( CCNode* pSender){ 
	CCLOG("ogre hurtend ");
	redBlood <= 0?0:redBlood;
	CCNotificationCenter::sharedNotificationCenter()->postNotification("Hurt",(CCObject *)( 100+ redBlood));
	if(redBlood > 0){
		CocosDenshion::SimpleAudioEngine::sharedEngine()->stopEffect(effectId);
		runStandAnimation();
		isHurt = false;
		isAttack = false;
	}
	else{
		isDead = true;
		effectId = CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sound/0312_03AF.wav");
		runDeadAnimation();
	}
 }

 void Ogre::DeadEnd(CCNode* pSender){
	if(isDead){
		this->removeChild(m_MonsterSprite,true);
		
		this->unschedule(schedule_selector(Ogre::update));
		this->unschedule(schedule_selector(Ogre::updateMonster));
	}
 }
void Ogre::attackCallbackFunc( CCNode* pSender ) {
	isAttack = false;
}
void Ogre::StartListen(){
	shana = GlobalCtrl::getInstance()->shana;
	tileMap = GlobalCtrl::getInstance()->tilemap;
	this->schedule(schedule_selector(Ogre::updateMonster),2.0f);
	this->scheduleUpdate();
}

void Ogre::enterSafeArea(){
	if(dis <= 200 || isDead || isHurt || isAttack)
		return;
	float width = getSprite()->getContentSize().width;
	float mapWidth = GlobalCtrl::getInstance()->tilemap->getContentSize().width;
	CCPoint curPos = this->getPosition();
	if(getSprite()->isFlipX());
	double distance = -(curPos.x - width < 100?curPos.x-width: 100);
	int flag = rand() % 2;
	//if(shana -> getSprite()->isFlipX()){
	if(flag == 1){
		distance =(mapWidth - width - curPos.x < 100?mapWidth - width - curPos.x: 100);
		faceDirecton = false;
	}
	else{
		faceDirecton = true;
	}
	CCCallFunc* callFuncRunAction = CCCallFunc::create(this, callfunc_selector(Role::runRunAnimation));
	//float moveTime = rand() % 1000 / 1000;
	//CCMoveBy* move = CCMoveBy::create( moveTime, CCPoint( distance, 0 ) );
	CCMoveBy* move = CCMoveBy::create( 2.0f, CCPoint( distance, 0 ) );

	CCSpawn* moveAndRunAction = CCSpawn::create(callFuncRunAction, move, NULL);
	CCCallFunc* callFuncStanAction = CCCallFunc::create(this, callfunc_selector(Role::runStandAnimation));
	CCActionInterval* xunluo=CCSequence::create(moveAndRunAction,callFuncStanAction,NULL);
	this->runAction(xunluo);
};

void Ogre::updateMonster(float delta){
	if(dis>=200){
		enterSafeArea();
	}
};

void Ogre::update(float dt){
	float x = shana->getPositionX()-(this->getPositionX()+tileMap->getPositionX());
	float y = shana->getPositionY()-(this->getPositionY()+tileMap->getPositionY());
	dis = sqrt(pow(x,2) + pow(y,2));
	if(faceDirecton != this->getSprite()->isFlipX() && abs(x) > 80)
		this->getSprite()->setFlipX( faceDirecton );
	if(dis > 200 &&dis <201){
		runStandAnimation();
	}
	if(dis > 200){
		initstatus();
	}
	if(isDead || isHurt || isAttack)
		return;
	if(dis <= 200){
		faceDirecton = shana->getPositionX()>this->getPositionX()? false:true;
		
		if(abs(x) <= 80){
			if(abs(y) <= 20){
				if(flag > 1000){
					initstatus();
				}
				flag++;	
				
				if((flag == 1 || rand() %200 == 1) && !isHurt && !isDead && !shana->isDead && !shana->isHurt){
					effectId = CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sound/0312_01B4.wav");
					isAttack = true;
					shana -> HurtAnimation(ogreAttacknum);
					runSkillAAnimation();
				}
				if(!isAttack&& !isHurt)
					runStandAnimation();
			}
		}
		if(!(abs(x)<=80 && abs(y) <= 20)){
			if(!isHurt && !isAttack){
				runRunAnimation();
			}
			//if(rand() % 2 !=0)
				enterAttackArea(x, y);
		}
	}
	
};

void Ogre::enterAttackArea(float x, float y){
	float directionx = abs(x) <= 80? directionx = 0:(x > 0? 1: -1);
	float directiony = abs(y) <= 20? directiony = 0:y > 0? 1: -1;
	this->setPosition(this->getPositionX()+directionx*2,this->getPositionY()+directiony);
};