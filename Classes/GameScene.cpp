#include"GameScene.h"
#include"baseRes.h"
#include"RewardLayer.h"
#include"Common.h"
#include"ShadeLayer.h"

#define MAINFRAME		60
#define d_fShowLocateMinute		214, 396
#define d_fShowLocateSecond		243, 396
#define d_LocateLimit	73, 28
#define d_fCantMove		20.0f
#define MAINFRAME		60
#define PIXELPERMETER	3

GameScene::GameScene(void){
	CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic("sound");
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("sound/fighting.mp3", -1);  
	gameLayer = NULL;
	TimeNum = 0;
	currentLevel = 0;
	operatorLayer= NULL;
	m_iMapNum = 0;
	m_fHeroLocateX = 0;
	m_fHeroLocateY = 0;
	GameStart = true;
	userbloodnum = 3;
	gameTime = 0;
	m_iGameMinute = 0;
	m_iGameSecond = 0;
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
	pEGLView -> setDesignResolutionSize(winSize.width*widthRate/heightRate, winSize.height,  kResolutionShowAll);
	return true;
};

//初始化计数器
void GameScene::setupInitTime(int num){
	GameStart = LimitInit();
	if(GameStart){
		this->removeChildByTag(100);
		schedule(schedule_selector(GameScene::update),1);
	}
}

bool GameScene::LimitInit(){
	bool ok = false;
	TimeNum += 2;
	switch ( currentLevel ){
		case 0:{
			Shana* shana = GlobalCtrl::getInstance()->shana;
			m_fHeroLocateX = shana->getPositionX();
			if ( TimeNum >= (m_iMapNum*800-m_fHeroLocateX-5*d_fCantMove)/PIXELPERMETER){
				TimeNum = (m_iMapNum*800-m_fHeroLocateX-5*d_fCantMove)/PIXELPERMETER;
				ok = true;
			}
		}
		break;
	default:
		if (TimeNum >= m_iLimitTimeNeed )
			ok = true;
		break;
	}
	int locatex = 0;
	if ( TimeNum < 10 )
		locatex = 78;
	else if ( TimeNum < 100 )
		locatex = 38;
	common::ShowNumber(m_pLimitBoard, TimeNum, 38, 65, locatex + d_LocateLimit, "tu4/limitN1.png");
	//计分
	if ( ok ){
		unschedule(schedule_selector(GameScene::setupInitTime));
		m_pLimitBoard->setScale(1.5f);
		Shana* shana = GlobalCtrl::getInstance()->shana;
		CCMoveTo* pAction1 = CCMoveTo::create(0.3f, ccp(shana->getPositionX(), shana->getPositionY() + m_pLimitBoard->getContentSize().height));
		CCScaleTo* pAction2 = CCScaleTo::create(0.3f, 0.65f);
		m_pLimitBoard->runAction(pAction1);
		m_pLimitBoard->runAction(pAction2);
	}
	return ok;
}

void GameScene::update(float delta){
	/*CCArray* ogreArray = GlobalCtrl::getInstance() ->pArray;
	bool flag = true;
	for (unsigned int i = 0; i <ogreArray->count(); ++i) {
		Ogre* pObj=(Ogre*)ogreArray->objectAtIndex(i);
		if(pObj -> redBlood > 0){
			flag = false;
		}
	} 
	if(flag){
		unschedule(schedule_selector(GameScene::update));
	}*/
	Shana* shana = GlobalCtrl::getInstance()->shana;
	m_fHeroLocateX = shana->getPositionX();
	switch ( currentLevel ){
		case 0:
			TimeNum = (m_iMapNum*800-m_fHeroLocateX-5*d_fCantMove)/PIXELPERMETER;
		break;
		default:
			gameTime++;
			TimeNum = m_iLimitTimeNeed - gameTime;
		break;
	}
	if ( TimeNum < 0 )
		TimeNum = 0;
	int locatex = 0;
	if ( TimeNum < 10 )
		locatex = 78;
	else if ( TimeNum < 100 )
		locatex = 38;
	common::ShowNumber(m_pLimitBoard, TimeNum, 38, 65, locatex + d_LocateLimit, "tu4/limitN1.png");
}

void GameScene::StartGame(int _level, int _difficult){
	currentLevel = _level;
	CCSprite* m_pBG = CCSprite::create(g_sBGPath[_level].c_str());
	m_pBG->setAnchorPoint(ccp(0.5f,0));
	m_pBG->setPosition(ccp(400, 0));
	this->addChild(m_pBG,0);
	//SetScale(m_pBG);
	//主角游戏层
	gameLayer = GameLayer::create();
	gameLayer->StartGameLevel(55+_level,_difficult);
	this->addChild(gameLayer, 0);
	schedule(schedule_selector(GameScene::rewardresult),1);
	//控制层
	operatorLayer = OperatorLayer::create();
		addChild( operatorLayer, 2 );
	GlobalCtrl::getInstance()->operatorLayer = operatorLayer;
	//关卡限定时间
	m_iLimitTimeNeed = StayTime[currentLevel];
	m_iMapNum = gameLayer->GetMapNums();
	if(currentLevel!=3 && currentLevel != 1){
		float updatetime = 1;
		if ( currentLevel == 0 ){
			m_pLimitBoard = CCSprite::create("tu4/limitM.png");
			updatetime = 0.1;
		}
		else if(currentLevel == 2){
			m_pLimitBoard = CCSprite::create("tu4/limitT.png");
		}
		m_pLimitBoard->setPosition(ccp(400, 240));
		addChild(m_pLimitBoard, 5);
		common::ShowNumber(m_pLimitBoard, TimeNum, 38, 65, d_LocateLimit, "tu4/limitN2.png", 889);
			schedule(schedule_selector(GameScene::setupInitTime));
		this->addChild(ShadeLayer::create(), 100, 100);
	}
	{
		m_pgameBoard = CCSprite::create("tu4/shijian.png");
		m_pgameBoard->setPosition(ccp(WINSIZE_W - m_pgameBoard->getContentSize().width/2 - 30, WINSIZE_H-m_pgameBoard->getContentSize().height/2));
		addChild(m_pgameBoard, 5);
		common::ShowNumber(m_pgameBoard, m_iGameMinute, 11, 15, 130, 10, "tu4/suzi.png", 802, 10, 1, true);
		common::ShowNumber(m_pgameBoard, m_iGameSecond/MAINFRAME, 11, 15, 160, 10, "tu4/suzi.png", 803, 10, 1, true);
		if(currentLevel == 2 || currentLevel == 3 || GameStart)
			schedule(schedule_selector(GameScene::showTime),1);
	}
}
void GameScene::showTime(float delta){
	m_iGameSecond++;
	if(m_iGameSecond>=60){
		m_iGameMinute++;
		m_iGameSecond=0;
	}
	common::ShowNumber(m_pgameBoard, m_iGameMinute, 11, 15, 130, 10, "tu4/suzi.png");
	common::ShowNumber(m_pgameBoard, m_iGameSecond, 11, 15, 160, 10, "tu4/suzi.png", 803, 10, 1, true);
}

void GameScene::rewardresult(float delta){
	if(GlobalCtrl::getInstance()->shana->isDead || ((currentLevel == 3 &&(gameLayer->getkillnum() >= 10)) || ((currentLevel==0 || currentLevel == 2) && TimeNum <= 0) /*|| (currentLevel == 1)*/)){
		unschedule(schedule_selector(GameScene::rewardresult));
		if(currentLevel == 3){
			CCUserDefault::sharedUserDefault()->setBoolForKey("level_style", !GlobalCtrl::getInstance()->shana->isDead);
			CCUserDefault::sharedUserDefault()->setIntegerForKey("level_killnum", gameLayer->getkillnum());
			CCUserDefault::sharedUserDefault()->setIntegerForKey("level_medal", m_iGameSecond);
			CCUserDefault::sharedUserDefault()->setIntegerForKey("level_rewardmedal", rand()%100);
			CCUserDefault::sharedUserDefault()->setIntegerForKey("currentlevelNum", currentLevel);

			CCUserDefault::sharedUserDefault()->setBoolForKey("overachieve1", !GlobalCtrl::getInstance()->shana->isDead);
			CCUserDefault::sharedUserDefault()->setBoolForKey("overachieve2", gameLayer->getkillnum() >= 20?true:false);
			CCUserDefault::sharedUserDefault()->setBoolForKey("overachieve3", m_iGameSecond < 120?true:false);
		}
		else if(currentLevel == 0){
			CCUserDefault::sharedUserDefault()->setBoolForKey("level_style", !GlobalCtrl::getInstance()->shana->isDead);
			CCUserDefault::sharedUserDefault()->setIntegerForKey("level_killnum", gameLayer->getkillnum());//
			CCUserDefault::sharedUserDefault()->setIntegerForKey("level_medal", m_iGameSecond);//
			CCUserDefault::sharedUserDefault()->setIntegerForKey("level_rewardmedal", rand()%100);//
			CCUserDefault::sharedUserDefault()->setIntegerForKey("currentlevelNum", currentLevel);

			CCUserDefault::sharedUserDefault()->setBoolForKey("overachieve1", !GlobalCtrl::getInstance()->shana->isDead);
			CCUserDefault::sharedUserDefault()->setBoolForKey("overachieve2", gameLayer->getkillnum() >= 10?true:false);
			CCUserDefault::sharedUserDefault()->setBoolForKey("overachieve3", m_iGameSecond < 60?true:false);
		}
		else if(currentLevel == 1){
			CCUserDefault::sharedUserDefault()->setBoolForKey("level_style", !GlobalCtrl::getInstance()->shana->isDead);
			CCUserDefault::sharedUserDefault()->setIntegerForKey("level_killnum", gameLayer->getkillnum());//
			CCUserDefault::sharedUserDefault()->setIntegerForKey("level_medal", 120);//
			CCUserDefault::sharedUserDefault()->setIntegerForKey("level_rewardmedal", rand()%100);//
			CCUserDefault::sharedUserDefault()->setIntegerForKey("currentlevelNum", currentLevel);

			CCUserDefault::sharedUserDefault()->setBoolForKey("overachieve1", !GlobalCtrl::getInstance()->shana->isDead);
			CCUserDefault::sharedUserDefault()->setBoolForKey("overachieve2", gameLayer->getkillnum() >= 30?true:false);
			CCUserDefault::sharedUserDefault()->setBoolForKey("overachieve3", userbloodnum < 3?false:true);
		}
		else if(currentLevel == 2){
			CCUserDefault::sharedUserDefault()->setBoolForKey("level_style", !GlobalCtrl::getInstance()->shana->isDead);
			CCUserDefault::sharedUserDefault()->setIntegerForKey("level_killnum", gameLayer->getkillnum());//
			CCUserDefault::sharedUserDefault()->setIntegerForKey("level_medal", 120);//
			CCUserDefault::sharedUserDefault()->setIntegerForKey("level_rewardmedal", rand()%100);//
			CCUserDefault::sharedUserDefault()->setIntegerForKey("currentlevelNum", currentLevel);

			CCUserDefault::sharedUserDefault()->setBoolForKey("overachieve1", !GlobalCtrl::getInstance()->shana->isDead);
			CCUserDefault::sharedUserDefault()->setBoolForKey("overachieve2", gameLayer->getkillnum() >= 30?true:false);
			CCUserDefault::sharedUserDefault()->setBoolForKey("overachieve3", userbloodnum < 1?false:true);
		}
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