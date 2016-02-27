#pragma once

#include "cocos2d.h"
#include "GlobalCtrl.h"
#include "Shana.h"

USING_NS_CC;

class JoyStick : public CCNode,public CCTouchDelegate{
public:
	JoyStick();
	~JoyStick();
	static JoyStick* create( const char* background, const char* mask );
    void startJoyStick(bool _isStopOther);  
    void stopJoyStick();  
    virtual void setTouchEnabled(bool value);
private:
	bool init( const char* background, const char* mask );

	CCSprite* back;
	CCSprite* mask;
	CCPoint centerPoint;
    float radius;
    CCPoint currentPoint;
	virtual void onEnter();
    virtual void onExit();
	bool isCanMove;
	void showJoyStick();
	void hideJoyStick();
	Shana* shana;
	CCRect getJoyStickBox();
	
	bool ccTouchBegan( CCTouch* touch, CCEvent* event );
	void ccTouchMoved( CCTouch* touch, CCEvent* event );
	void ccTouchEnded( CCTouch* touch, CCEvent* event );
	void ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent);
};

