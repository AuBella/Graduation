#pragma once
#include"cocos2d.h"
#include"GameLayer.h"

USING_NS_CC;

class GameScene: public CCScene{
public:
	GameScene(void);
	~GameScene(void);
	virtual bool init();
	CC_SYNTHESIZE(GameLayer*, _gameLayer, GameLayer);
	CREATE_FUNC(GameScene);
};