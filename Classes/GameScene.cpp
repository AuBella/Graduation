#include"GameScene.h"

GameScene::GameScene(void){
	CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic("sound");
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("sound/fighting.mp3", -1);  
	_gameLayer = NULL;
	operatorLayer= NULL;
};

GameScene::~GameScene(void){
	CocosDenshion::SimpleAudioEngine::sharedEngine()->stopBackgroundMusic("sound/fighting.mp3");  
};

bool GameScene::init(){
	if(!CCScene::init())
		return false;
	_gameLayer = GameLayer::create();
	this->addChild(_gameLayer, 0);
	operatorLayer = OperatorLayer::create();
		addChild( operatorLayer, 2 );
		
	GlobalCtrl::getInstance()->operatorLayer = operatorLayer;
	return true;
};