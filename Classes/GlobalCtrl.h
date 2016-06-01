#pragma once

#include "cocos2d.h"
USING_NS_CC;
#include"CHero.h"
class Shana;
class OperatorLayer;
class JoyStick;
class SkillButton;
//class CHero;
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
	CHero* hero;
	bool canEnter;
	bool canSetting;

	//guanka
	bool isSuccess;
private:
	static GlobalCtrl* _instance;
};

