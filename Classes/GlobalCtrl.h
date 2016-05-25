#pragma once

#include "cocos2d.h"
USING_NS_CC;

class Shana;
class OperatorLayer;
class JoyStick;
class SkillButton;
class GlobalCtrl {
public:
	GlobalCtrl();
	~GlobalCtrl();
	static GlobalCtrl* getInstance();
	static void destroyInstance();
	//static GlobalCtrl* 
	Shana* shana;
	JoyStick* joyStick;
	SkillButton* skillButton;
	OperatorLayer* operatorLayer;
	CCMenu* menu;
	CCTMXTiledMap* tilemap;
	CCArray* pArray;
	bool canEnter;
	bool canSetting;
private:
	static GlobalCtrl* _instance;
};

