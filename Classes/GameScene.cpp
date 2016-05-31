#include"GameScene.h"
#include"baseRes.h"
#include"RewardLayer.h"
GameScene::GameScene(void){
	CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic("sound");
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("sound/fighting.mp3", -1);  
	gameLayer = NULL;
	TimeNum = 0;
	currentLevel = 0;
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

	//����͸���һ���ȣ�ͨ������ȣ�������ĵ����߼��ֱ��ʵĴ�С
	float widthRate = frameSize.width/winSize.width;
	float heightRate = frameSize.height/winSize.height;
    pDirector->setOpenGLView(pEGLView);
	
    // turn on display FPS
    pDirector->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    pDirector->setAnimationInterval(1.0 / 60);
	CCLOG("------------->>>>>>>>>>>>> %f %f",winSize.width*widthRate/heightRate, winSize.height);
	pEGLView -> setDesignResolutionSize(winSize.width*widthRate/heightRate, winSize.height,  kResolutionShowAll);
	return true;
};
void GameScene::setupInitTime(int num){
	pLabel = CCLabelTTF::create("Time", "fonts/Helvetica", 15);//Ҫ��ʾ�����ݣ����壬�ֺ� 
	pLabel->setColor(ccc3(255,255,0));
	
	pLabel ->setPosition(ccp(512/ 2,320 - 10));
	operatorLayer->addChild(pLabel,1);
	pLabel = CCLabelTTF::create("99:99", "fonts/Helvetica", 20);//Ҫ��ʾ�����ݣ����壬�ֺ� 
	pLabel->setColor(ccc3(255,255,0)); 
	operatorLayer->addChild(pLabel,1);
	pLabel ->setPosition(ccp(512 / 2, 320 - 25));
	schedule(schedule_selector(GameScene::update),1);
}

void GameScene::update(float delta){
	CCArray* ogreArray = GlobalCtrl::getInstance() ->pArray;
	bool flag = true;
	for (unsigned int i = 0; i <ogreArray->count(); ++i) {
		Ogre* pObj=(Ogre*)ogreArray->objectAtIndex(i);
		if(pObj -> redBlood > 0){
			flag = false;
		}
	}
	TimeNum += delta;  
	char* mtime = new char[10];  
	//�˴�ֻ����ʾ������������  �Լ����Զ������ʱ���ʽ  
	sprintf(mtime,"%d : %d",(int)TimeNum/60,(int)TimeNum%60);  
	pLabel->setString(mtime);  
}
void GameScene::showRewardResult(){
	/*CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	CCRenderTexture *renderTexture = CCRenderTexture::create(visibleSize.width,visibleSize.height);
	renderTexture->begin(); 
	renderTexture->end();
	CCDirector::sharedDirector()->replaceScene(RewardLayer::scene(renderTexture, TimeNum, 89));	*/
}
void GameScene::setupHeroIcon(char* name){
	heroIcon = CCSprite::create("Common/310_hoodle.png");
}

void GameScene::StartGame(int _level, int _difficult){
	currentLevel = _level;
	//������Ϸ��
	gameLayer = GameLayer::create();
	gameLayer->StartGameLevel(55+_level,_difficult);
	this->addChild(gameLayer, 0);
	schedule(schedule_selector(GameScene::rewardresult),1);
	//���Ʋ�
	operatorLayer = OperatorLayer::create();
		addChild( operatorLayer, 2 );
	GlobalCtrl::getInstance()->operatorLayer = operatorLayer;
	setupInitTime(TimeNum);
	setupHeroIcon("aa");
}

void GameScene::rewardresult(float delta){
	if(GlobalCtrl::getInstance()->shana->isDead || (currentLevel == 0 &&(gameLayer->getkillnum() >= 10 || TimeNum > 60))){
		unschedule(schedule_selector(GameScene::rewardresult));
		CCUserDefault::sharedUserDefault()->setBoolForKey("level_style", !GlobalCtrl::getInstance()->shana->isDead);
		CCUserDefault::sharedUserDefault()->setIntegerForKey("level_killnum", gameLayer->getkillnum());
		CCUserDefault::sharedUserDefault()->setIntegerForKey("level_medal", TimeNum);
		CCUserDefault::sharedUserDefault()->setIntegerForKey("level_rewardmedal", rand()%100);
		CCUserDefault::sharedUserDefault()->setBoolForKey("overachieve1", !GlobalCtrl::getInstance()->shana->isDead);
		CCUserDefault::sharedUserDefault()->setBoolForKey("overachieve2", gameLayer->getkillnum() >= 10?true:false);
		CCUserDefault::sharedUserDefault()->setBoolForKey("overachieve3", TimeNum < 60?true:false);
		CCUserDefault::sharedUserDefault()->setIntegerForKey("currentlevelNum", currentLevel);

		CCUserDefault::sharedUserDefault()->flush();
		CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
		CCRenderTexture *renderTexture = CCRenderTexture::create(visibleSize.width,visibleSize.height);
		renderTexture->begin(); 
		this->visit();
		//this->getParent()->visit();
		renderTexture->end();
		CCScene* pScene = RewardLayer::scene(renderTexture, TimeNum, 89);
		CCDirector::sharedDirector()->replaceScene(pScene);	
	}
}