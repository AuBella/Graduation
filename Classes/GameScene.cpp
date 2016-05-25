#include"GameScene.h"

#include"RewardLayer.h"
GameScene::GameScene(void){
	CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic("sound");
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("sound/fighting.mp3", -1);  
	gameLayer = NULL;
	TimeNum = 120;
	operatorLayer= NULL;
	heroIcon = NULL;
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
	//主角游戏层
	gameLayer = GameLayer::create();
	this->addChild(gameLayer, 0);
	//玩家操作层
	operatorLayer = OperatorLayer::create();
		addChild( operatorLayer, 2 );
	GlobalCtrl::getInstance()->operatorLayer = operatorLayer;
	//倒计时
	setupInitTime(TimeNum);
	setupHeroIcon("aa");
	return true;
};
void GameScene::setupInitTime(int num){/*
	CCSize winSize = CCDirector::sharedDirector() -> getWinSize();
	CCLOG("....................%f %f", winSize.width, winSize.height);*/
	pLabel = CCLabelTTF::create("Time", "fonts/Helvetica", 15);//要显示的内容，字体，字号 
	pLabel->setColor(ccc3(255,255,0));
	//pLabel ->setPosition(ccp(winSize.width / 2, winSize.height - 10));
	
	pLabel ->setPosition(ccp(512/ 2,320 - 10));
	operatorLayer->addChild(pLabel,1);
	pLabel = CCLabelTTF::create("99:99", "fonts/Helvetica", 20);//要显示的内容，字体，字号 
	pLabel->setColor(ccc3(255,255,0)); 
	operatorLayer->addChild(pLabel,1);
	//pLabel ->setPosition(ccp(winSize.width / 2, winSize.height - 25));
	pLabel ->setPosition(ccp(512 / 2, 320 - 25));
	schedule(schedule_selector(GameScene::update),1);
}

void GameScene::update(float delta){
	
	CCArray* ogreArray = GlobalCtrl::getInstance() ->pArray;
	CCLOG("------------------------------%d", ogreArray->count());
	bool flag = true;
	for (unsigned int i = 0; i <ogreArray->count(); ++i) {
		Ogre* pObj=(Ogre*)ogreArray->objectAtIndex(i);
		if(pObj -> redBlood > 0){
			flag = false;
		}
	}
	if(flag){
		showRewardResult();
		this->unschedule(schedule_selector(GameScene::update)); 
		//unscheduleUpdate();
	}
	TimeNum -= delta;  
	char* mtime = new char[10];  
	//此处只是显示分钟数和秒数  自己可以定义输出时间格式  
	sprintf(mtime,"%d : %d",(int)TimeNum/60,(int)TimeNum%60);  
	pLabel->setString(mtime);  
}
void GameScene::showRewardResult(){
	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	CCRenderTexture *renderTexture = CCRenderTexture::create(visibleSize.width,visibleSize.height);
	renderTexture->begin(); 
	renderTexture->end();
	CCDirector::sharedDirector()->replaceScene(RewardLayer::scene(renderTexture, TimeNum, 89));	
}
void GameScene::setupHeroIcon(char* name){
	heroIcon = CCSprite::create("Common/310_hoodle.png");
}