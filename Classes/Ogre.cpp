#include"Ogre.h"

Ogre::Ogre(){};

Ogre::~Ogre(){};

bool Ogre::init(){
	
		if( !Role::init())
			return false;

		//设置精灵
		this->setSprite( CCSprite::create( "$maouox_1.png", CCRect( 0, 0, 55, 62 ) ) );
		this->addChild( getSprite() );
		this->setPosition(240, 200);
		//初始化各种动画
		/*CCAnimation* standAnimn = AnimationUtil::getAnimation( "$maouox_1.png", 2, 2 );
		setStandAnimation( CCRepeatForever::create( CCAnimate::create( standAnimn ) ) );

		CCAnimation* runAnimn = AnimationUtil::getAnimation( "$maouox_forward.png", 6, 6 );
		setRunAnimation( CCRepeatForever::create( CCAnimate::create( runAnimn ) ) );

		CCAnimation* deadAnimn = AnimationUtil::getAnimation( "$maouox_dead.png", 3, 3 );
		setDeadAnimation( CCRepeatForever::create( CCAnimate::create( deadAnimn ) ) );

		CCAnimation* hurtAnimn = AnimationUtil::getAnimation( "$maouox_4.png", 2, 2 );
		setHurtAnimation( CCRepeatForever::create( CCAnimate::create( hurtAnimn ) ) );
		runStandAnimation();*/

		CCAnimation* standAnimn = AnimationUtil::getAnimation( "$shana_1.png", 4, 4 );
		setStandAnimation( CCRepeatForever::create( CCAnimate::create( standAnimn ) ) );

		CCAnimation* runAnimn = AnimationUtil::getAnimation( "$shana_forward.png", 8, 8 );
		setRunAnimation( CCRepeatForever::create( CCAnimate::create( runAnimn ) ) );

		CCAnimation* deadAnimn = AnimationUtil::getAnimation( "$shana_dead.png", 3, 3 );
		setDeadAnimation( CCRepeatForever::create( CCAnimate::create( deadAnimn ) ) );

		CCAnimation* hurtAnimn = AnimationUtil::getAnimation( "$shana_4.png", 2, 2 );
		setHurtAnimation( CCRepeatForever::create( CCAnimate::create( hurtAnimn ) ) );
		runStandAnimation();

		this->schedule(schedule_selector(Ogre::updateMonster),1.0f);//每隔3秒计算距离
		this->scheduleUpdate();//英雄一旦进入可视范围，怪物追着英雄打
	return true;
};

void Ogre::CanSeeArea(){
	CCLOG("enter Monster can see area");
	//this->runRunAnimation();
	//GlobalCtrl::getInstance()->shana->onMove( direction, distance );
};

void Ogre::onMove( CCPoint direction, float distance ) {
	
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

void Ogre::updateMonster(float delta){
	shana = GlobalCtrl::getInstance()->shana;
	tileMap = GlobalCtrl::getInstance()->tilemap;
	float x = shana->getPositionX()-(this->getPositionX()+tileMap->getPositionX());
	//得到两点y的距离，记得怪物的坐标要加上地图的
	float y = shana->getPositionY()-(this->getPositionY()+tileMap->getPositionY());
	//先计算怪物和英雄的距离
	dis = sqrt(pow(x,2) + pow(y,2));
	CCLOG("ENTER updateMonster dis ================>>>>>>>>>>>>>>>>> %f\n", dis);
	//if(dis>=300){
		CanSeeArea();
	//}
};

void Ogre::update(float dt){
};