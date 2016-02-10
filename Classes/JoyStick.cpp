#include "JoyStick.h"
#include "GlobalCtrl.h"
#include "Shana.h"


JoyStick::JoyStick():
isCanMove(false)
{}


JoyStick::~JoyStick() {}


JoyStick* JoyStick::create( const char* background, const char* mask ) {
	auto joyStick = new JoyStick();
	if ( joyStick && joyStick->init( background, mask ) ) {
		joyStick->autorelease();
		return joyStick;
	}
	CC_SAFE_DELETE( joyStick );
	return nullptr;
}/*
void JoyStick::onEnter()
{
	CCNode::onEnter();
	CCDirector::sharedDirector()->getTouchDispatcher()->addStandardDelegate(this,0);
}*/

void JoyStick::onEnter()
{
    //注册监听   1.dele类，2.优先级，3.YES为阻碍其他类的move 和 end
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
    CCNode::onEnter();
}
 
void JoyStick::onExit()
{
    //移除监听
    CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
    CCNode::onExit();
}

bool JoyStick::init( const char* background, const char* mask ) {
	if(!CCNode::init())
		return false;
	back = CCSprite::create( background );
	this->mask = CCSprite::create( mask );
	this->mask->setScale(0.75);
	this->addChild( back, -1 );
	this->addChild( this->mask, 0 );
	centerPoint = CCPoint(0,0);
	radius = back->getContentSize().width * 0.5;
	return true;
}


bool JoyStick::ccTouchBegan( CCTouch* touch, CCEvent* event ) {
	auto pos = touch->getLocation();
	CCLOG ("Containt: %f %f %f %f  %f %f\n", getJoyStickBox().getMinX(), getJoyStickBox().getMinY() , getJoyStickBox().getMaxX(), getJoyStickBox().getMaxY(), pos.x, pos.y);
		
	if ( getJoyStickBox().containsPoint( pos ) ) {
	    currentPoint = pos;  
		//CCLOG ("Containt: %f %f %f %f  %f %f\n", getJoyStickBox().getMinX(), getJoyStickBox().getMinY() , getJoyStickBox().getMaxX(), getJoyStickBox().getMaxY(), pos.x, pos.y);
		isCanMove = true;
		showJoyStick();
		GlobalCtrl::getInstance()->shana->setCanMutilAttack( false );
	}
	return true;
}


void JoyStick::ccTouchMoved( CCTouch* touch, CCEvent* event ) {
	if ( isCanMove ) {
		auto currentPoint = touch->getLocation();
		currentPoint = convertToNodeSpace(currentPoint );
		if (ccpDistance(currentPoint, centerPoint) > radius)  
			currentPoint =ccpAdd(centerPoint,ccpMult(ccpNormalize(ccpSub(currentPoint, centerPoint)), radius));  
		float distance = currentPoint.getDistance( centerPoint );
		if ( distance > 33.0f ) {
			distance = 33.0f;
		}
		//CCPoint direction = centerPoint,ccpMult(ccpNormalize(ccpSub(currentPoint, centerPoint)));
		
		CCPoint direction = ccpSub(currentPoint,centerPoint) /ccpDistance(currentPoint,centerPoint);
		this->mask->setPosition( currentPoint);

		GlobalCtrl::getInstance()->shana->onMove( direction, distance );
	}
}


void JoyStick::ccTouchEnded( CCTouch* touch, CCEvent* event ) {
		auto pos = touch->getLocation();
	CCLOG ("ended: %f %f\n", pos.x, pos.y);

	hideJoyStick();
	isCanMove = false;
	mask->setPosition( CCPoint(0,0) );
	GlobalCtrl::getInstance()->shana->onStop();
}

void JoyStick::showJoyStick() {
	back->setVisible( true );
	mask->setVisible( true );
}


void JoyStick::hideJoyStick() {
	back->setVisible( true );
	mask->setVisible( true );
}


CCRect JoyStick::getJoyStickBox() {
	float x = getPositionX();
	float y = getPositionY();
	float width = back->getContentSize().width;
	float height = back->getContentSize().height;
	return CCRect( x - width / 2, y - height / 2, width, height );
}