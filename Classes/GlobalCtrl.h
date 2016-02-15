#pragma once

#include "cocos2d.h"
USING_NS_CC;

class Shana;
class GlobalCtrl {
public:
	GlobalCtrl();
	~GlobalCtrl();
	static GlobalCtrl* getInstance();
	static void destroyInstance();

	Shana* shana;
	CCMenu* menu;
	//Shana* shana1;
	CCTMXTiledMap* tilemap;

private:
	static GlobalCtrl* _instance;
};

