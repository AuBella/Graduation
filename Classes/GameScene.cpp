#include"GameScene.h"
#include "OperatorLayer.h"

//USING_NS_CC;

GameScene::GameScene(void){
	_gameLayer = NULL;
};

GameScene::~GameScene(void){};

bool GameScene::init(){
	if(!CCScene::init())
		return false;
	_gameLayer = GameLayer::create();
	this->addChild(_gameLayer, 0);

	auto operatorLayer = OperatorLayer::create();
		addChild( operatorLayer, 2 );
	return true;
};
