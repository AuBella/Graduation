#pragma once

#include "cocos2d.h"
USING_NS_CC;

class JoyStick : public CCNode,public CCTouchDelegate{
public:
	JoyStick();
	~JoyStick();
	static JoyStick* create( const char* background, const char* mask );
	 //Æô¶¯Ò¡¸Ë  
    void startJoyStick(bool _isStopOther);  
  
    //Í£Ö¹Ò¡¸Ë  
    void stopJoyStick();  
private:
	bool init( const char* background, const char* mask );

	CCSprite* back;
	CCSprite* mask;
	CCPoint centerPoint;
    float radius;//Ò¡¸Ë°ë¾¶  
    CCPoint currentPoint;//Ò¡¸Ëµ±Ç°Î»ÖÃ  
	virtual void onEnter();
    virtual void onExit();
	bool isCanMove;
	void showJoyStick();
	void hideJoyStick();

	CCRect getJoyStickBox();
	
	bool ccTouchBegan( CCTouch* touch, CCEvent* event );
	void ccTouchMoved( CCTouch* touch, CCEvent* event );
	void ccTouchEnded( CCTouch* touch, CCEvent* event );
};

