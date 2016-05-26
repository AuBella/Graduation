#include "GameControler.h"
#include "baseRes.h"
#include "AppDelegate.h"
#include "MainMenu.h"
#include "ControlerMenu.h"
#include "GameoverMenu.h"
#include "GameoverBtnMenu.h"
#include "GameLoading.h"
#include "Common.h"
#include "cocos-ext.h"
#include"Shana.h"
#include"GlobalCtrl.h"
#include"OperatorLayer.h"

using namespace cocos2d;
using namespace cocos2d::extension;

#define d_LocateHealBoard		665, 447
#define d_LocateHeartbeat		93, 35
#define d_sizeHeartbeat			156, 43
#define d_LocateHealBox(i)		593+i*52, 447
#define d_TagHealBoxHave		220
#define d_TagHealBoxUnhave		225
CGameControler* CGameControler::s_pGameControler = NULL;

CGameControler::CGameControler(){
	m_pScene		= NULL;
	m_iLevelType	= 0;
	m_iComboMax=0;
	m_iStateNumKill = 0;
	m_iStateNumMedal = 0;
	m_iStateNumGold = 0;
	m_iAllStar = 3;
	m_iStar = 1;
	m_iHealBox=3;	
	m_bAttack		= false;
	m_pMoveActionArray = new int[d_iActionNum];
	memset(m_pMoveActionArray, 0, sizeof(int)*d_iActionNum );
}
CGameControler::~CGameControler()
{
	m_pScene		= NULL;
	m_iLevelType	= 0;
}


CGameControler* CGameControler::NewGameControler(cocos2d::CCScene* _pScene, int _unLevel, int _difficult){
	CGameControler* pLayer = new CGameControler();
	s_pGameControler = pLayer;
	pLayer->init();
	pLayer->autorelease();
	pLayer->m_pScene	= _pScene;
	pLayer->m_unLevel	= _unLevel;
	pLayer->m_iDifficult= _difficult;

	SetScale(pLayer);
	_pScene->addChild(pLayer, 1, 1);
	pLayer->m_pCFrontgroud = CFrontground::Create(_unLevel);
	pLayer->m_iMapNum = pLayer->m_pCFrontgroud->GetMapNums();
	if ( pLayer->m_iLevelType == 6 ){
		pLayer->m_pBG = CCSprite::create("Tile/beijing2.png");
		pLayer->m_pBG->setAnchorPoint(ccp(0.5f,0));
		pLayer->m_pBG->setPosition(ccp(400, 0));
		CCLayer* pBGLayer = new CCLayer();
		pBGLayer->autorelease();
		pBGLayer->addChild(pLayer->m_pBG);
		SetScale(pBGLayer);
		_pScene->addChild(pBGLayer,0);
	}
	else
	{
		pLayer->m_pBG = CCSprite::create(g_sBGPath[_unLevel].c_str());
		pLayer->m_pBG->setAnchorPoint(ccp(0.5f,0));
		pLayer->m_pBG->setPosition(ccp(400, 0));
		CCLayer* pBGLayer = new CCLayer();
		pBGLayer->autorelease();
		pBGLayer->addChild(pLayer->m_pBG);
		SetScale(pBGLayer);
		_pScene->addChild(pBGLayer,0);
	}
	
	pLayer->m_pCBackgroud = CBackground::Create(_unLevel);
	SetScale(pLayer->m_pCBackgroud);
	_pScene->addChild(pLayer->m_pCBackgroud);

	SetScale(pLayer->m_pCFrontgroud);
	_pScene->addChild(pLayer->m_pCFrontgroud,0);
	return pLayer;
}

void CGameControler::GameLoadingSecond()
{
	CCNodeLoaderLibrary* ccNodeLoaderLibrary = CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
	ccNodeLoaderLibrary->registerCCNodeLoader("ccbControlMenu", ccbControlMenuLoader::loader());
	cocos2d::extension::CCBReader* ccbReader = new cocos2d::extension::CCBReader(ccNodeLoaderLibrary);
	m_pMenuNode = ccbReader->readNodeGraphFromFile("6.ccbi"/*, this*/);
	m_pMenuNode->setPosition(ccp(0,0));
	//SetScale(m_pMenuNode);
	((ccbControlMenu*)m_pMenuNode)->setAnimationManager(ccbReader->getAnimationManager(), m_unLevel);
	ccbReader->release();
	addChild(m_pMenuNode, 4, 50);
}

//button
void CGameControler::GameStart(){
	CCSprite* pHealBoard = CCSprite::create("tu4/di.png");
	pHealBoard->setPosition( CCPoint(d_LocateHealBoard) );
	addChild(pHealBoard, 5);
	CCSprite* pHeartbeat = common::CreateAnimation("Animation/heartbeat/1.png", CCPoint(d_LocateHeartbeat), ccp(0.5f, 0.5f),
		"Animation/heartbeat/", 6, CCRect(0,0,d_sizeHeartbeat), true);
	pHealBoard->addChild(pHeartbeat, 5);

	for ( int i = 0; i < d_iHealBoxMax; i++ )
	{
		CCSprite* pSprite1 = CCSprite::create("tu4/xuebao.png");
		pSprite1->setPosition( CCPoint(d_LocateHealBox(i)) );
		addChild(pSprite1, 5, d_TagHealBoxHave+i);
		CCSprite* pSprite2 = CCSprite::create("tu4/xuebao2.png");
		pSprite2->setPosition( CCPoint(d_LocateHealBox(i)) );
		addChild(pSprite2, 5, d_TagHealBoxUnhave+i);
	}
	ShowHealBox();
	schedule(schedule_selector(CGameControler::Timer));
	((ccbControlMenu*)m_pMenuNode)->Appear();
	for ( int i = 0; i < d_iActionNum; i++ ){
		CCSprite* pBtn =  CCSprite::create(g_sButtonPath[i].c_str());
		pBtn->setAnchorPoint(ccp(0.5f,0.5f));
		pBtn->setPosition(ccp(g_fButtonX[i],g_fButtonY[i]));
		addChild(pBtn,10, 20+i);

		CCSprite* pBtnPress = CCSprite::create(g_sButtonPressPath[i].c_str());
		pBtnPress->setPosition(ccp(g_fButtonX[i],g_fButtonY[i]));
		pBtnPress->setVisible(false);
		addChild(pBtnPress,10, 40+i);
	}
	setTouchEnabled(true);
}


void CGameControler::ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent)
{
	CCSetIterator iter = pTouches->begin();
	int digit = 1;
	for (; iter != pTouches->end(); iter++)
	{
		CCPoint location = ((CCTouch*)(*iter))->getLocation();
		digit = (*iter)->m_uID;

		e_ActionType iActionType = eAT_NULL;
		for ( int i = 0; i < d_iActionNum; i++ ){
			//if ( 6 == m_iLevelType )
			//{
			//	if ( i == 4 )//Ìø
			//		continue;
			//	bool vis = true;
			//	if ( getChildByTag(40+i) )
			//		vis = getChildByTag(40+i)->isVisible();
			//	if ( !getChildByTag(20+i)->isVisible() && !vis )
			//		continue;
			//}
			if ( fabs(location.x - g_fButtonX[i]*Scale_X) < g_fButtonW[i]*Scale_X
				&& fabs(location.y - g_fButtonY[i]*Scale_Y) < g_fButtonH[i]*Scale_Y ){
				iActionType = (e_ActionType)i;
				break;
			}
		}
		switch ( iActionType )
		{
		case eAT_MoveLeft:
			MoveCheck(0, digit);
			break;
		case eAT_MoveRight:
			MoveCheck(1, digit);
			break;
		case eAT_Jump:
			/*if ( !m_iHeroJumps )
			{
				AppDelegate::AudioPlayEffect("MS/Sound/EfJump.mp3");
				m_fHeroSpeedY = d_fHeroJump;
				m_iHeroJumps = 1;
				m_iJumpActionType = 2;
			}
			else if ( m_iHeroJumps == 1 )
			{
				AppDelegate::AudioPlayEffect("MS/Sound/EfJump.mp3");
				m_iHeroJumps ++;
				m_fHeroSpeedY		= d_fHeroJump;
				m_iJumpActionType	= 2;
			}
			else if ( m_iHeroJumps == 2 && m_iJumpCanTimes > 2 )
			{
				AppDelegate::AudioPlayEffect("MS/Sound/EfJump.mp3");
				m_iHeroJumps ++;
				m_fHeroSpeedY		= m_fJumpSpeedInit;
				m_iJumpActionType	= 2;
			}*/
			m_pMoveActionArray[3] = 20;
			break;
		case eAT_Attack:
			/*if ( m_bAttack || m_iGrenadeTime > 0 )
				break;*/
			m_bAttack		= true;
			m_pMoveActionArray[2] = digit;
			break;
		case eAT_PAUSE:{
			CCLOG("---------ENTER CLICLIK");
			PauseGame();
			}
			break;
		default:
			break;
		}
	}
}
//ÔÝÍ£
void CGameControler::PauseGame(int _type){
	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	CCRenderTexture *renderTexture = CCRenderTexture::create(visibleSize.width,visibleSize.height);
	renderTexture->begin(); 
	this->getParent()->visit();
	renderTexture->end();
	CCDirector::sharedDirector()->pushScene(Gamepause::scene(renderTexture));
}

void CGameControler::ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent){}

void CGameControler::ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent)
{
	CCSetIterator iter = pTouches->begin();
	for (; iter != pTouches->end(); iter++/*, digit++*/)
	{
		CCPoint location = ((CCTouch*)(*iter))->getLocation();
		{
			e_ActionType iActionType = eAT_NULL;
			for ( int i = 0; i < d_iActionNum; i++ )
			{
				if ( fabs(location.x - g_fButtonX[i]*Scale_X) < g_fButtonW[i]*Scale_X
					&& fabs(location.y - g_fButtonY[i]*Scale_Y) < g_fButtonH[i]*Scale_Y){
					iActionType = (e_ActionType)i;
					m_pMoveActionArray[i] = 0;
					break;
				}
			}
		}
	}
}

void CGameControler::Timer(float _dt){
		ButtonPressCheck();
}

//°´Å¥¿ØÖÆ
void CGameControler::ButtonPressCheck(){
	for ( int i = 0; i < d_iActionNum; i++ ){
		bool bShow = true;
		if ( i < 2 ){
			if ( m_pMoveActionArray[i] )
				bShow = false;
		}
		else if ( i == 2 ){
			if ( m_bAttack && m_pMoveActionArray[i] > 0)
				bShow = false;
		}
		else if ( m_pMoveActionArray[i] > 0 ){
			m_pMoveActionArray[i]--;
			bShow = false;
		}
		getChildByTag(20+i)->setVisible(bShow);
		getChildByTag(40+i)->setVisible(!bShow);
	}
}

//ÒÆ¶¯¼ì²â
void CGameControler::MoveCheck(int _un, int _digit){
	if ( !(m_pMoveActionArray[0] | m_pMoveActionArray[1]) ){
		m_pMoveActionArray[_un]	= _digit;
	}
}

//Ñª°ü
void CGameControler::ShowHealBox(){
	for ( int i = 0; i < d_iHealBoxMax; i++ ){
		bool bShow = false;
		if ( i < m_iHealBox )
			bShow = true;
		CCNode* pSprite1 = getChildByTag(d_TagHealBoxHave+i);
		pSprite1->setVisible(bShow);
		CCNode* pSprite2 = getChildByTag(d_TagHealBoxUnhave+i);
		pSprite2->setVisible(!bShow);
	}
}

CGameControler* CGameControler::GetGameControler(){
	return s_pGameControler;
}

bool CGameControler::init()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	this->setKeypadEnabled(true);
#endif
	//scheduleOnce(schedule_selector(CGameControler::Lose), 0);
	return true;
}


void CGameControler::Win(float _dt)
{
	CCLayerColor* pCCLayerColor = CCLayerColor::create(ccc4(20,20,20,230), 800, 480);
	addChild(pCCLayerColor, 16, 10);
	//((ccbGameoverMenu*)m_pGameoverNode)->Win( 100 );
}

void CGameControler::Lose(float _dt){
	//((ccbGameoverMenu*)m_pGameoverNode)->Lose( 42 );
}

void CGameControler::ShowStar()
{
	if ( m_unLevel%6 != 5 && m_unLevel < 49 )
	{
		//int iStarAll = 3;//ÏÖµÃÐÇÐÇÊý
		scheduleOnce(schedule_selector(CGameControler::ShowOverBtn), 0.60f+m_iAllStar*0.70f);
		if ( m_iAllStar > 0 )
			scheduleOnce(schedule_selector(CGameControler::ShowStarMovie1), 0.30f);
		if ( m_iAllStar > 1 )
			scheduleOnce(schedule_selector(CGameControler::ShowStarMovie2), 1.00f);
		if ( m_iAllStar > 2 )
			scheduleOnce(schedule_selector(CGameControler::ShowStarMovie3), 1.70f);
	}
	else
	{
#ifndef GameTypeC
		scheduleOnce(schedule_selector(CGameControler::ShowOverBtn), 1.30f);
		scheduleOnce(schedule_selector(CGameControler::ShowStarBoss), 0.30f);
#else
		scheduleOnce(schedule_selector(CGameControler::ShowOverBtn), 1.00f);
#endif
	}
}



void CGameControler::ShowStarMovie1( float _dt )
{
	AppDelegate::AudioPlayEffect("MS3/star.mp3");
#ifndef GameTypeC
	CCSprite* pStar = CCSprite::create("tu5/xingxing/3.png");
	pStar->setScale(8.0f);
	CCActionInterval* actionTo1 = CCScaleTo::create(0.2f, 1.0f);
	CCActionInterval* actionTo2 = CCMoveTo::create(0.2f, ccp(d_fStarLocateX1, d_fStarLocateY1));
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
	CCActionInterval* actionTo2 = CCMoveTo::create(0.2f, ccp(d_fStarLocateX1, d_fStarLocateY1));
	pStar->setPosition(ccp(d_fStarLocateX, d_fStarLocateY));
	pStar->runAction( CCSpawn::create(actionTo1, actionTo2, NULL) );
#endif
	addChild(pStar,24);
	m_iStar++;
}

void CGameControler::ShowStarMovie2( float _dt )
{
	AppDelegate::AudioPlayEffect("MS3/star.mp3");
#ifndef GameTypeC
	CCSprite* pStar = CCSprite::create("tu5/xingxing/3.png");
	pStar->setScale(8.0f);
	CCActionInterval* actionTo1 = CCScaleTo::create(0.2f, 1.0f);
	CCActionInterval* actionTo2 = CCMoveTo::create(0.2f, ccp(d_fStarLocateX2, d_fStarLocateY2));
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
	CCActionInterval* actionTo2 = CCMoveTo::create(0.2f, ccp(d_fStarLocateX2, d_fStarLocateY2));
	pStar->setPosition(ccp(d_fStarLocateX, d_fStarLocateY));
	pStar->runAction( CCSpawn::create(actionTo1, actionTo2, NULL) );
#endif
	addChild(pStar,24);
	m_iStar++;
}

void CGameControler::ShowStarMovie3( float _dt )
{
	AppDelegate::AudioPlayEffect("MS3/star.mp3");
#ifndef GameTypeC
	CCSprite* pStar = CCSprite::create("tu5/xingxing/3.png");
	pStar->setScale(8.0f);
	CCActionInterval* actionTo1 = CCScaleTo::create(0.2f, 1.0f);
	CCActionInterval* actionTo2 = CCMoveTo::create(0.2f, ccp(d_fStarLocateX3, d_fStarLocateY3));
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
	CCActionInterval* actionTo2 = CCMoveTo::create(0.2f, ccp(d_fStarLocateX3, d_fStarLocateY3));
	pStar->setPosition(ccp(d_fStarLocateX, d_fStarLocateY));
	pStar->runAction( CCSpawn::create(actionTo1, actionTo2, NULL) );
#endif
	addChild(pStar,24);
	m_iStar++;
}

void CGameControler::ShowStarBoss( float _dt )
{
	AppDelegate::AudioPlayEffect("MS3/star.mp3");
#ifndef GameTypeC
	CCSprite* pStar = CCSprite::create("tu5/boss/ku1.png");
	pStar->setScale(8.0f);
	CCActionInterval* actionTo1 = CCScaleTo::create(0.2f, 1.0f);
	CCActionInterval* actionTo2 = CCMoveTo::create(0.2f, ccp(d_fStarLocateX2, d_fStarLocateY2-30));
	CCAnimate* pAnimate = CCAnimate::create( 
		common::CreateAnimationFrame("tu5/boss/ku", 2, CCRect(0,0,129,123), 0.1f) );
	pStar->setPosition(ccp(d_fStarLocateX, d_fStarLocateY));
	pStar->runAction( CCSequence::create(
		CCSpawn::create(actionTo1, actionTo2, NULL), CCCallFunc::create(this, callfunc_selector(CGameControler::ShowStarBoss1)),
		pAnimate, NULL) );
	addChild(pStar,25);
#endif
}

void CGameControler::ShowStarBoss1()
{
#ifndef GameTypeC
	CCSprite* pSprite = CCSprite::create("tu5/boss/1.png");
	pSprite->setScale(1.5f);
	pSprite->setPosition(ccp(d_fStarLocateX2, d_fStarLocateY2-30));
	pSprite->setAnchorPoint(ccp(0.46f, 0.5f));
	CCAnimate* pAction = CCAnimate::create(common::CreateAnimationFrame("tu5/boss/", 8, CCRect(0,0,361,235)));
	addChild(pSprite,24);
#endif
}

void CGameControler::ShowOverBtn( float _dt ){}
