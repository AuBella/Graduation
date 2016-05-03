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
	CCDirector* pDirector = CCDirector::sharedDirector();
	
    CCEGLView* pEGLView = CCEGLView::sharedOpenGLView();
	CCSize frameSize = pEGLView->getFrameSize();
	CCSize winSize=CCSize(480,320);

	//将宽和高做一个比，通过这个比，来具体的调整逻辑分辨率的大小
	float widthRate = frameSize.width/winSize.width;
	float heightRate = frameSize.height/winSize.height;
    pDirector->setOpenGLView(pEGLView);
	
    // turn on display FPS
    pDirector->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    pDirector->setAnimationInterval(1.0 / 60);
	CCLOG("------------->>>>>>>>>>>>> %f %f",winSize.width*widthRate/heightRate, winSize.height);
	pEGLView -> setDesignResolutionSize(winSize.width*widthRate/heightRate, winSize.height,  kResolutionShowAll);
	_gameLayer = GameLayer::create();
	this->addChild(_gameLayer, 0);
	operatorLayer = OperatorLayer::create();
		addChild( operatorLayer, 2 );
		
	GlobalCtrl::getInstance()->operatorLayer = operatorLayer;
	return true;
};