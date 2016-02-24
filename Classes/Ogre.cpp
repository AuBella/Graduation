#include"Ogre.h"

Ogre::Ogre(){
	faceDirecton = true;
	leftInTheMonster = true;
	isHurt = false;
	isDead = false;
	isAttack = false;
	redBlood = 100;
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

 void Ogre::HurtAnimation(){
	if(isDead)
		return;
	isHurt = true;
	//effectId = CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sound/hurt.wav");
	effectId = CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sound/0312_00EB.wav");
	//int effectId1 = CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sound/hurt1.wav");   
	//CCLOG("enter HURTAnimation   %d ", effectId); 
	this->runHurtAnimation(); 
 }

 void Ogre::HurtEnd( CCNode* pSender){ 
	CCLOG("ogre hurtend ");
	redBlood-=10;
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
	//GlobalCtrl::getInstance()->shana ->isAttack = false;
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
	/*Shana* shana = GlobalCtrl::getInstance()->shana;
	shana->runHurtAnimation();*/
}
void Ogre::StartListen(){
	shana = GlobalCtrl::getInstance()->shana;
	tileMap = GlobalCtrl::getInstance()->tilemap;
	this->schedule(schedule_selector(Ogre::updateMonster),2.0f);//每隔3秒计算距离
	this->scheduleUpdate();//英雄一旦进入可视范围，怪物追着英雄打
}

void Ogre::enterSafeArea(){
	//CCLOG("enter Monster can see area");
	if(dis <= 200 || isDead || isHurt || isAttack)
		return;
	float width = getSprite()->getContentSize().width;
	float mapWidth = GlobalCtrl::getInstance()->tilemap->getContentSize().width;
	CCPoint curPos = this->getPosition();
	if(getSprite()->isFlipX());
	////faceDirecton = true;
	//double distance = -min(curPos.x - width, 100);
	double distance = -(curPos.x - width < 100?curPos.x-width: 100);
	if(shana -> getSprite()->isFlipX()){
		//CCLOG("shana is face left");
		//distance =min(mapWidth - width - curPos.x, 100);
		
		distance =(mapWidth - width - curPos.x < 100?mapWidth - width - curPos.x: 100);
		faceDirecton = false;
		//this->getSprite()->setFlipX( false );
	}
	else{
		//CCLOG("shana is face right");
		faceDirecton = true;
		//this->getSprite()->setFlipX( true );
	}
	CCCallFunc* callFuncRunAction = CCCallFunc::create(this, callfunc_selector(Role::runRunAnimation));
	CCMoveBy* move = CCMoveBy::create( 1.0f, CCPoint( distance, 0 ) );

	CCSpawn* moveAndRunAction = CCSpawn::create(callFuncRunAction, move, NULL);
	//创建连续动作
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
	//if(shana->isDead)
	//	this->unschedule(schedule_selector(Ogre::update));
	
	//CCLOG("ENTER update attack area ================>>>>>>>>>>>>>>>>> %f\n", dis);
	float x = shana->getPositionX()-(this->getPositionX()+tileMap->getPositionX());
	//得到两点y的距离，记得怪物的坐标要加上地图的
	float y = shana->getPositionY()-(this->getPositionY()+tileMap->getPositionY());
	//先计算怪物和英雄的距离
	dis = sqrt(pow(x,2) + pow(y,2));
	if(faceDirecton != this->getSprite()->isFlipX() && abs(x) > 80)
		this->getSprite()->setFlipX( faceDirecton );
	//进入追踪区域
	if(dis > 200 &&dis <201){
		runStandAnimation();
	}
	if(dis > 200){
		initstatus();/*
		if(!isHurt && !isAttack)
			runStandAnimation();*/
	}
	if(isDead || isHurt || isAttack)
		return;
	if(dis <= 200){
		//进入攻击区域
		//runStandAnimation();
		faceDirecton = shana->getPositionX()>this->getPositionX()? false:true;
		
		if(abs(x) <= 80){
			/*if(abs(x) > 79 &&abs(x) <80){
				runStandAnimation();
			}*/
			if(abs(y) <= 20){
				//runStandAnimation();
				if(flag > 1000){
					initstatus();
				}
				flag++;	
				
				if((flag == 1 || rand() %200 == 1) && !isHurt && !isDead && !shana->isDead){
					effectId = CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sound/0312_01B4.wav");
					isAttack = true;
					shana -> HurtAnimation();
					runSkillAAnimation();
				}
				if(!isAttack&& !isHurt)
					runStandAnimation();
			}
		}
		if(!(abs(x)<=80 && abs(y) <= 20)){
			if(!isHurt && !isAttack){
				CCLOG("enter ????????????11111111111");
				runRunAnimation();
			}
			
			enterAttackArea(x, y);
		}
		/*if(isHurt && !(GlobalCtrl::getInstance()->shana ->shanaisAttack)){
			runStandAnimation();
			isHurt = false;
		}*/
	}
	
};

void Ogre::enterAttackArea(float x, float y){
	float directionx = abs(x) <= 80? directionx = 0:(x > 0? 1: -1);
	float directiony = abs(y) <= 20? directiony = 0:y > 0? 1: -1;
	this->setPosition(this->getPositionX()+directionx*2,this->getPositionY()+directiony);
};