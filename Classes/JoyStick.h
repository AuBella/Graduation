#pragma once

#include "cocos2d.h"
USING_NS_CC;

class JoyStick : public CCNode,public CCTouchDelegate{
public:
	JoyStick();
	~JoyStick();
	static JoyStick* create( const char* background, const char* mask );
	 //����ҡ��  
    void startJoyStick(bool _isStopOther);  
  
    //ֹͣҡ��  
    void stopJoyStick();  
private:
	bool init( const char* background, const char* mask );

	CCSprite* back;
	CCSprite* mask;
	CCPoint centerPoint;
    float radius;//ҡ�˰뾶  
    CCPoint currentPoint;//ҡ�˵�ǰλ��  
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

