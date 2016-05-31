#include"RewardLayer.h"
#include"AppDelegate.h"
#include "GameScene.h"
#include"baseRes.h"
#include"Common.h"
#include"MainMenu.h"

#define d_LocateHealX			865
#define d_LocateHealY			1047
#define d_fGameOverNumLocate1	1054, 588
#define d_fGameOverNumLocate2	1019, 501
#define d_fGameOverNumLocate4	973, 405
#define d_fGameOverNumLocate31	1039, 480
#define d_fGameOverNumLocate32	1060, 480
#define d_fGameOverNumLocate33	1081, 480

RewardLayer::RewardLayer(){
	m_bNowKill		= true;
	m_bNowMedal		= true;
	m_bNowGold		= true;
	m_bComboMoney	= true;
	m_bStartAddCombo= true;
	m_bOverAddCombo	= true;
	Visible = CCUserDefault::sharedUserDefault()->getBoolForKey("level_style");//boss星星
	m_iNowKill		= CCUserDefault::sharedUserDefault()->getIntegerForKey("level_killnum");
	m_iNowTime	= CCUserDefault::sharedUserDefault()->getIntegerForKey("level_medal");
	//m_iNowScore		= CCUserDefault::sharedUserDefault()->getIntegerForKey("level_rewardmedal");
	m_iNowScore = 0;
	otherScore = CCUserDefault::sharedUserDefault()->getIntegerForKey("level_rewardmedal");
	//levelScore = (m_iNowKill + 60 - m_iNowTime);//关卡的总分数计算方式=星级*（怪物数 + 60 – 通关时间）
	overachieve[0] = CCUserDefault::sharedUserDefault()->getBoolForKey("overachieve1");//第一成就，通关
	overachieve[1] = CCUserDefault::sharedUserDefault()->getBoolForKey("overachieve2");
	overachieve[2] = CCUserDefault::sharedUserDefault()->getBoolForKey("overachieve3");
	LevelNum = CCUserDefault::sharedUserDefault()->getIntegerForKey("currentlevelNum");
	m_iAllStar = 0;
}

RewardLayer::~RewardLayer(){
	CCUserDefault::sharedUserDefault()->setBoolForKey("level_style", false);
	CCUserDefault::sharedUserDefault()->flush();
};

CCScene* RewardLayer::scene(CCRenderTexture* sqr, int num, int redBlood){
	RewardLayer*rewardlayer =  new RewardLayer();
    CCScene *scene = CCScene::create();
    RewardLayer *layer = RewardLayer::create();
	scene->addChild(layer,1);//把游戏层放上面，我们还要在这上面放按钮
	//增加部分：使用Game界面中截图的sqr纹理图片创建Sprite
	//并将Sprite添加到GamePause场景层中
	//得到窗口的大小
	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	CCSprite *back_spr = CCSprite::createWithTexture(sqr->getSprite()->getTexture());  
	back_spr->setPosition(ccp(visibleSize.width/2,visibleSize.height/2)); //放置位置,这个相对于中心位置。
	back_spr->setFlipY(true);            //翻转，因为UI坐标和OpenGL坐标不同
	back_spr->setColor(cocos2d::ccGRAY); //图片颜色变灰色
	scene->addChild(back_spr);
	//添加游戏暂停背景小图，用来放按钮
	//Win
	
	rewardlayer->setRewardLayerInfo(true, true, true, true, 0, 0, 0, 0);
    return scene;
}

void RewardLayer::setRewardLayerInfo(bool visible, bool condition1, bool condition2, bool condition3, int killnum, int attackcombomnum, int Getmoney,int rewardmoney){
	Visible = visible;
}


void RewardLayer::SetPositionStart(float x, float y){
	
}

bool RewardLayer::init(){
	if(!CCLayer::init()){
		return false;
	}
	if(overachieve[0]){
		back_small_spr = CCSprite::create("tu5/shengli.png");
		xingxingBack = CCSprite::create("tu5/xiasheng.png");
		xingxingBack->setAnchorPoint(ccp(0,0));
		xingxingBack->setPosition(ccp(back_small_spr->getContentSize().width/2,0));
		//xingxingBack->setPosition(ccp(WINSIZE_W/3,WINSIZE_H/3));
		back_small_spr->addChild(xingxingBack);
	
		AppDelegate::AudioPlayBgm("MS/Music/EfWinBG.mp3", false);
		//成功条件框
		CCDictionary *strings = CCDictionary::createWithContentsOfFileThreadSafe("Tile/QustionStrings.xml");
		for ( int i = 0; i < 3; i++ ){
			CCSprite* pSprite = NULL;
			//达成框
			if ( overachieve[i] ){
				pSprite = CCSprite::create("tu5/kuai.png");
				m_iAllStar++;
			}
			else
				pSprite = CCSprite::create("tu5/kuai2.png");
			pSprite->setAnchorPoint(ccp(0.5, 0.5));
			back_small_spr->addChild(pSprite);
			pSprite->setPosition(ccp(pSprite->getContentSize().height/2,pSprite->getContentSize().height*i+20));
			char buffer[255];
			sprintf(buffer, "Tile/QuestionInfo/%d.png", LevelNum*3+i);
			CCSprite* pLaber = CCSprite::create(buffer);
			if ( pLaber ){
				pLaber->setAnchorPoint(ccp(0.0f, 0.0f));
				pLaber->setPosition(ccp(pSprite->getContentSize().height, pSprite->getContentSize().height/2-10));
				//pLaber->setColor( ccc3(0, 0, 0) );
				pSprite->addChild(pLaber);
			}
		}
		//计算得分
		m_iNowScore = 10 * m_iAllStar * (m_iNowKill + 60 - m_iNowTime);
		//星星背景（黑色）
		CCSprite* pSprite1 = CCSprite::create("tu5/xingxing/hei.png");
		CCSprite* pSprite2 = CCSprite::create("tu5/xingxing/hei.png");
		CCSprite* pSprite3 = CCSprite::create("tu5/xingxing/hei.png");
		fStarLocateX1 = back_small_spr->getContentSize().width/3 - pSprite2->getContentSize().width/3;
		fStarLocateX2 = back_small_spr->getContentSize().width/3 + pSprite2->getContentSize().width/3;
		fStarLocateX3 = back_small_spr->getContentSize().width/3 + pSprite2->getContentSize().width;
		float tempy1 = pSprite2->getContentSize().height;
		float tempy2 = tempy1/3;
		fStarLocateY1 = tempy2 + tempy1/2;
		fStarLocateY2 = tempy1 + tempy1/2;
		fStarLocateY3 = tempy2 + tempy1/2;
		pSprite1->setPosition(ccp(fStarLocateX1,fStarLocateY1));
		pSprite2->setPosition(ccp(fStarLocateX2,fStarLocateY2));
		pSprite3->setPosition(ccp(fStarLocateX3,fStarLocateY3));
		xingxingBack->addChild(pSprite1);
		xingxingBack->addChild(pSprite2);
		xingxingBack->addChild(pSprite3);
		CCSprite*pSprite4 = CCSprite::create("tu5/boss/hei.png");
		fStarLocateX = back_small_spr->getContentSize().width/2 - pSprite4->getContentSize().width /2;
		fStarLocateY = pSprite4->getContentSize().height;
		pSprite4->setPosition(ccp(fStarLocateX,fStarLocateY));
		xingxingBack->addChild(pSprite4);
		scheduleOnce(schedule_selector(RewardLayer::StartDigit), 1.50f);
		pSprite1->setVisible(Visible);
		pSprite2->setVisible(Visible);
		pSprite3->setVisible(Visible);
		pSprite4->setVisible(!Visible);
	}
	else{
		scheduleOnce(schedule_selector(RewardLayer::ShowOverBtn), 1.00f);
		back_small_spr = CCSprite::create("tu5/shibai.png");
	}
	SetScaleY(back_small_spr);
	back_small_spr->setPosition(ccp(WINSIZE_W/2,WINSIZE_H/2));
	this->addChild(back_small_spr);
	return true;
}

//继续重玩
void RewardLayer::OnContinueLevel(CCObject* pSender){
	GameScene* pscene = GameScene::create();
	pscene->StartGame(LevelNum,0);
	AppDelegate::ChangeScene(pscene);
}

void RewardLayer::OnGoToMainLevel(CCObject* pSender){
	AppDelegate::ChangeScene(CMainMenu::StartMenu());
}

void RewardLayer::StartDigit( float _t ){
	schedule(schedule_selector(RewardLayer::Timer), 0.01f);
}

void RewardLayer::Timer( float _t ){
	if ( m_bNowGold && m_bNowMedal && m_bNowKill && m_bComboMoney ){
		unschedule(schedule_selector(RewardLayer::Timer));
		if(Visible){
			ShowStar();
		}
		else{ 
			scheduleOnce(schedule_selector(RewardLayer::ShowStarBoss),1.0f);
	
		}
	}
	//杀敌
	common::ShowNumber(xingxingBack, m_iNowKill, 20, 19, (fStarLocateX2 + fStarLocateX3) /2 + 20, fStarLocateY2 * 9 / 3, "tu5/suzi.png", 801);
	//连击
	common::ShowNumber(xingxingBack, m_iNowTime, 20, 19,fStarLocateX2 + 20, fStarLocateY2 * 7 / 3, "tu5/suzi.png", 802, 0, 1.1f);
	////金钱，奖励
	common::ShowNumber(xingxingBack, m_iNowScore, 20, 19, (fStarLocateX1 + fStarLocateX2) / 2 + 10,fStarLocateY2 * 5 / 3, "tu5/suzi.png", 804, 0, 1.2f);
	CCSprite* pSprite = CCSprite::create("tu5/jia.png");
	int i = 0;
	if ( m_iNowScore < 100 )
		i = 1;
	else if ( m_iNowScore < 1000 )
		i = 2;
	else if ( m_iNowScore < 10000 )
		i = 3;
	pSprite->setPosition(CCPoint(46 + 19*i +  (fStarLocateX1 + fStarLocateX2) / 2 + 10,fStarLocateY2 * 5 / 3 + 8));
	//common::ShowNumber(xingxingBack, m_iNowScore, 20, 19,  (fStarLocateX1 + fStarLocateX2) / 2 + 10,fStarLocateY2 * 5 / 3, "tu5/suzi.png", 804, 0, 1.2f);
	common::ShowNumber(pSprite, otherScore, 20, 19, 15, 0, "tu5/suzi.png", 804, 0, 1.2f);
	xingxingBack->addChild(pSprite, 0, 19);
	pSprite->getChildByTag(804)->runAction(CCSequence::create(CCDelayTime::create(1.0f), CCFadeOut::create(0.5f), NULL));
	pSprite->runAction( CCSequence::create(CCDelayTime::create(1.0f), CCFadeOut::create(0.5f), 
		CCCallFunc::create(this, callfunc_selector(RewardLayer::AddOver)), NULL) );
}

void RewardLayer::AddOver(){
	//加上后总金币
	common::ShowNumber(xingxingBack, m_iNowScore + otherScore, 20, 19,(fStarLocateX1 + fStarLocateX2) / 2 + 10,fStarLocateY2 * 5 / 3, "tu5/suzi.png", 804, 0, 1.2f);
	//加号
	xingxingBack->getChildByTag(19)->removeFromParentAndCleanup(true);
	m_bOverAddCombo = true;
}
void RewardLayer::ShowStar()
{
	if (true){
		scheduleOnce(schedule_selector(RewardLayer::ShowOverBtn), 0.60f+m_iAllStar*0.70f);
		if ( m_iAllStar > 0 )
			scheduleOnce(schedule_selector(RewardLayer::ShowStarMovie1), 0.30f);
		if ( m_iAllStar > 1 )
			scheduleOnce(schedule_selector(RewardLayer::ShowStarMovie2), 1.00f);
		if ( m_iAllStar > 2 )
			scheduleOnce(schedule_selector(RewardLayer::ShowStarMovie3), 1.70f);
	}
	else{
		scheduleOnce(schedule_selector(RewardLayer::ShowOverBtn), 1.00f);
	}
}

void RewardLayer::ShowOverBtn( float _dt ){
	//按钮
	CCMenuItemImage* menuChooseItem1 = CCMenuItemImage::create("tu5/anniu/guakayemian.png", "tu5/anniu/guankayemian2.png",  this, menu_selector(RewardLayer::OnGoToMainLevel));
	CCMenu* menu1 = CCMenu::create( menuChooseItem1,NULL );
	CCMenuItemImage* menuChooseItem = NULL;
	if(overachieve[0])
		menuChooseItem = CCMenuItemImage::create("tu5/anniu/jixu.png", "tu5/anniu/jixu2.png",  this, menu_selector(RewardLayer::OnContinueLevel));
	else
		menuChooseItem = CCMenuItemImage::create("tu5/anniu/chongwan.png", "tu5/anniu/chongwan2.png",  this, menu_selector(RewardLayer::OnContinueLevel));
	//CCMenuItemImage* menuChooseItem = CCMenuItemImage::create("tu5/anniu/chongwan.png", "tu5/anniu/chongwan.png",  this, menu_selector(RewardLayer::MenuSettingCallback));
	CCMenu* menu = CCMenu::create( menuChooseItem,NULL );
	/*if(overachieve[0]){
		menu1 -> setPosition(ccp(fStarLocateX3 * 5 / 4 + 20,fStarLocateY3 + 50
		menu -> setPosition(ccp(fStarLocateX3 * 5 / 4 + 20,fStarLocateY3 - 20));
	}
	else{*/
		menu1 -> setPosition(ccp(	WINSIZE_W - 70,	50));
		menu -> setPosition(ccp(	WINSIZE_W - 70, 120));
		this->addChild(menu);
		this->addChild(menu1);
	//}
}

void RewardLayer::ShowStarMovie1( float _dt ){
	AppDelegate::AudioPlayEffect("MS3/star.mp3");
#ifndef GameTypeC
	CCSprite* pStar = CCSprite::create("tu5/xingxing/3.png");
	//pStar->setScale(8.0f
	pStar->setScale(0.5f);
	CCActionInterval* actionTo1 = CCScaleTo::create(0.2f, 1.0f);
	CCActionInterval* actionTo2 = CCMoveTo::create(0.2f, ccp(fStarLocateX1, fStarLocateY1));
	//CCActionInterval* actionTo2 = CCMoveTo::create(0.2f, ccp(d_fStarLocateX1, d_fStarLocateY1));
	CCAnimate* pAnimate = CCAnimate::create( 
		common::CreateAnimationFrame("tu5/xingxing/", 12, CCRect(0,0,154,140), 0.1f) );
	pStar->setPosition(ccp(WINSIZE_W/2, WINSIZE_H/2));
	pStar->runAction( CCSequence::create(
		CCSpawn::create(actionTo1, actionTo2, NULL),
		pAnimate, NULL) );
#else
	CCSprite* pStar = CCSprite::create("tu5/xingxing/12.png");
	//pStar->setScale(8.0f);
	pStar->setScale(0.5f);
	CCActionInterval* actionTo1 = CCScaleTo::create(0.2f, 1.0f);
	CCActionInterval* actionTo2 = CCMoveTo::create(0.2f, ccp(fStarLocateX1, fStarLocateY1));
	pStar->setPosition(ccp(WINSIZE_W/2, WINSIZE_H/2));
	pStar->runAction( CCSpawn::create(actionTo1, actionTo2, NULL) );
#endif
	xingxingBack->addChild(pStar,24);
	//m_iStar++;
}

void RewardLayer::ShowStarMovie2( float _dt )
{
	AppDelegate::AudioPlayEffect("MS3/star.mp3");
#ifndef GameTypeC
	CCSprite* pStar = CCSprite::create("tu5/xingxing/3.png");
	pStar->setScale(8.0f);
	CCActionInterval* actionTo1 = CCScaleTo::create(0.2f, 1.0f);
	CCActionInterval* actionTo2 = CCMoveTo::create(0.2f, ccp(fStarLocateX2, fStarLocateY2));
	CCAnimate* pAnimate = CCAnimate::create( 
		common::CreateAnimationFrame("tu5/xingxing/", 12, CCRect(0,0,154,140), 0.1f) );
	pStar->setPosition(ccp(d_fStarLocateX, d_fStarLocateY));
	pStar->runAction( CCSequence::create(
		CCSpawn::create(actionTo1, actionTo2, NULL),
		pAnimate, NULL) );
#else
	CCSprite* pStar = CCSprite::create("tu5/xingxing/12.png");
	pStar->setScale(8.0f);
	CCActionInterval* actionTo1 = CCScaleTo::create(0.2f, 1.0f);
	CCActionInterval* actionTo2 = CCMoveTo::create(0.2f, ccp(fStarLocateX2, fStarLocateY2));
	pStar->setPosition(ccp(d_fStarLocateX, d_fStarLocateY));
	pStar->runAction( CCSpawn::create(actionTo1, actionTo2, NULL) );
#endif
	xingxingBack->addChild(pStar,24);
	//m_iStar++;
}

void RewardLayer::ShowStarMovie3( float _dt )
{
	AppDelegate::AudioPlayEffect("MS3/star.mp3");
#ifndef GameTypeC
	CCSprite* pStar = CCSprite::create("tu5/xingxing/3.png");
	pStar->setScale(8.0f);
	CCActionInterval* actionTo1 = CCScaleTo::create(0.2f, 1.0f);
	CCActionInterval* actionTo2 = CCMoveTo::create(0.2f, ccp(fStarLocateX3, fStarLocateY3));
	CCAnimate* pAnimate = CCAnimate::create( 
		common::CreateAnimationFrame("tu5/xingxing/", 12, CCRect(0,0,154,140), 0.1f) );
	pStar->setPosition(ccp(d_fStarLocateX, d_fStarLocateY));
	pStar->runAction( CCSequence::create(
		CCSpawn::create(actionTo1, actionTo2, NULL),
		pAnimate, NULL) );
#else
	CCSprite* pStar = CCSprite::create("tu5/xingxing/12.png");
	pStar->setScale(8.0f);
	CCActionInterval* actionTo1 = CCScaleTo::create(0.2f, 1.0f);
	CCActionInterval* actionTo2 = CCMoveTo::create(0.2f, ccp(fStarLocateX3, fStarLocateX3));
	pStar->setPosition(ccp(d_fStarLocateX, d_fStarLocateY));
	pStar->runAction( CCSpawn::create(actionTo1, actionTo2, NULL) );
#endif
	xingxingBack->addChild(pStar,24);
	//m_iStar++;
}

void RewardLayer::ShowStarBoss( float _dt )
{
	AppDelegate::AudioPlayEffect("MS3/star.mp3");
#ifndef GameTypeC
	CCSprite* pStar = CCSprite::create("tu5/boss/ku1.png");
	pStar->setScale(8.0f);
	CCActionInterval* actionTo1 = CCScaleTo::create(0.2f, 1.0f);
	CCActionInterval* actionTo2 = CCMoveTo::create(0.2f, ccp(fStarLocateX, fStarLocateY));
	CCAnimate* pAnimate = CCAnimate::create( 
		common::CreateAnimationFrame("tu5/boss/ku", 2, CCRect(0,0,129,123), 0.1f) );
	pStar->setPosition(ccp(d_fStarLocateX, d_fStarLocateY));
	pStar->runAction( CCSequence::create(
		CCSpawn::create(actionTo1, actionTo2, NULL), CCCallFunc::create(this, callfunc_selector(RewardLayer::ShowStarBoss1)),
		pAnimate, NULL) );
	xingxingBack->addChild(pStar,25);
#endif
}

void RewardLayer::ShowStarBoss1()
{
#ifndef GameTypeC
	CCSprite* pSprite = CCSprite::create("tu5/boss/1.png");
	pSprite->setScale(1.5f);
	pSprite->setPosition(ccp(fStarLocateX, fStarLocateY-30));
	pSprite->setAnchorPoint(ccp(0.46f, 0.5f));
	CCAnimate* pAction = CCAnimate::create(common::CreateAnimationFrame("tu5/boss/", 8, CCRect(0,0,361,235)));
	pSprite->runAction(CCSequence::create(pAction, CCCallFuncN::create(this, callfuncN_selector(RewardLayer::CallBackRemoveSelf)), NULL));
	xingxingBack->addChild(pSprite,24);
#endif
}

void RewardLayer::CallBackRemoveSelf( CCNode* _pNode, void* data ){
	CCSprite* pObject = (CCSprite*)data;
	if ( fabs(pObject->getPositionX()-d_LocateHealX) < 80.0f &&
		fabs(pObject->getPositionY()-d_LocateHealY) < 10.0f ){
		_pNode->stopAllActions();
		_pNode->setScale(2.0f);
		CCScaleTo* pAction1 = CCScaleTo::create(0.3f, 1.0f);
		_pNode->runAction( CCSequence::create(pAction1, CCDelayTime::create(1.0f),
			CCCallFuncN::create(this, callfuncN_selector(RewardLayer::CallBackRemoveSelf2)), NULL) );
#ifndef GameTypeC
		CCSprite* pSprite = common::CreateAnimation("Animation/gethealbox/1.png", ccp(33, 21), ccp(0.5f, 0.5f),
			"Animation/gethealbox/", 5, CCRect(0, 0, 181, 127), false, false, 0.1f, 
			CCCallFuncN::create(this, callfuncN_selector(RewardLayer::CallBackRemoveSelf)));
		_pNode->addChild(pSprite, -1);
#endif
	}
	else{
		_pNode->removeFromParentAndCleanup(true);
	}
}

//移除动画
void RewardLayer::CallBackRemoveSelf2( CCNode* _pNode ){
	//ShowHealBox();
	_pNode->removeFromParentAndCleanup(true);
}
void RewardLayer::CallBackRemoveSelf( CCNode* _pNode ){
	_pNode->stopAllActions();
	_pNode->removeFromParent();
}