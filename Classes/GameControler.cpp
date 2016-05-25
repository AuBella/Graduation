#include "GameControler.h"
#include "baseRes.h"
//#include "MonsterInfo.h"
#include "AppDelegate.h"
#include "MainMenu.h"
//#include "ControlerMenu.h"
//#include "PauseMenu.h"
#include "GameoverMenu.h"
#include "GameoverBtnMenu.h"
//#include "GameBossLoading.h"
#include "GameLoading.h"
#include "Common.h"
//#include "GameStartMenu.h"
//#include "GameSkillLayer.h"
//#include "SimpleAudioEngine.h"
//#include "GameStart.h"
//#include "AchieveAdd.h"
//#include "BossBox.h"
//#include "GetItemLayer.h"
//#include "ChoseHero.h"
//#include "ShopMenu.h"
//#include "PayService.h"
#include "cocos-ext.h"

//extern CFlashControl* g_pHero;
using namespace cocos2d;
using namespace cocos2d::extension;


CGameControler::CGameControler()
{
	m_pScene		= NULL;
	m_iLevelType	= 0;
	m_iComboMax=0;
	m_iStateNumKill = 0;
	m_iStateNumMedal = 0;
	m_iStateNumGold = 0;
	m_iAllStar = 3;
	
	m_iStar = 1;
}
CGameControler::~CGameControler()
{
	m_pScene		= NULL;
	m_iLevelType	= 0;
}


CGameControler* CGameControler::NewGameControler(cocos2d::CCScene* _pScene, int _unLevel, int _difficult)
{
	CGameControler* pLayer = new CGameControler();
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
	pLayer->m_pCBackgroud->setPosition(0, 0);
	SetScale(pLayer->m_pCBackgroud);
	_pScene->addChild(pLayer->m_pCBackgroud);

	pLayer->m_pCFrontgroud->setPosition(0, 0);
	SetScale(pLayer->m_pCFrontgroud);
	_pScene->addChild(pLayer->m_pCFrontgroud,0);
	
	//ShowOverBtn(0.1f);
	//CCNodeLoaderLibrary* ccNodeLoaderLibrary3 = CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
	//ccNodeLoaderLibrary3->registerCCNodeLoader("ccbGameoverBtnMenu", ccbGameoverBtnMenuLoader::loader());
	//cocos2d::extension::CCBReader* ccbReader3 = new cocos2d::extension::CCBReader(ccNodeLoaderLibrary3);
	//m_pGameoverBtnNode = ccbReader3->readNodeGraphFromFile("9.ccbi"/*, this*/);
	//m_pGameoverBtnNode->setPosition(ccp(0,0));
	////SetScale(m_pGameoverBtnNode);
	//((ccbGameoverBtnMenu*)m_pGameoverBtnNode)->setAnimationManager(ccbReader3->getAnimationManager(), this);
	//ccbReader3->release();
	//addChild(m_pGameoverBtnNode, 23, 53);
	return pLayer;
}

bool CGameControler::init()
{
	//m_cSize = cocos2d::CCDirector::sharedDirector()->getWinSize();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	this->setKeypadEnabled(true);
#endif
	
	scheduleOnce(schedule_selector(CGameControler::Lose), 0);
	return true;
}


void CGameControler::Win(float _dt)
{
	//if ( 6 == m_iLevelType )
	//{
	//	AppDelegate::s_FirstLogin = 2;
	//	AppDelegate::SaveGuide();
	//	AppDelegate::SaveStatus();
	//	//AppDelegate::ChangeScene( ccbChoseHero::CreateScene() );
	//	return;
	//}

	//if ( m_bPerfect )
	//	//AchieveAdd::Add(17, 0, m_unLevel);
	//if ( m_bUnFire )
	//	AchieveAdd::Add(22, 0, m_unLevel);
	//if ( AppDelegate::s_HeroType == 1 )
	//	AchieveAdd::Add(26, 0, m_unLevel);
	//else if ( AppDelegate::s_HeroType == 2 )
	//	AchieveAdd::Add(28, 0, m_unLevel);

	/*if ( m_unLevel%6 != 5 )
	{
		if ( m_structQuestion.type[0] )
		{
			if ( m_iGameMinute*60 + m_iGameSecond/MAINFRAME <= m_structQuestion.num[0] )
			{
				m_iAllStar++;
				m_structQuestion.complate[0] = 1;
			}
		}
		if ( m_structQuestion.type[1] )
		{
			if ( 0 < m_structQuestion.num[1] )
			{ 
				m_iAllStar++;
				m_structQuestion.complate[1] = 1;
			}
		}
		if ( m_structQuestion.type[3] )
		{
			m_iAllStar++;
			m_structQuestion.complate[3] = 1;
		}
		if ( m_structQuestion.type[4] )
		{
			if ( m_structQuestion.complate[4] )
			{
				m_iAllStar++;
			}
		}
		if ( m_structQuestion.type[5] )
		{
			if ( m_iVIPHp >= m_structQuestion.num[5] )
			{
				m_iAllStar++;
				m_structQuestion.complate[5] = 1;
			}
		}
		if ( AppDelegate::s_LevelStar[m_unLevel] < m_iAllStar )
			AppDelegate::s_LevelStar[m_unLevel] = m_iAllStar;
	}
*/
	//m_bPause = true;
	CCLayerColor* pCCLayerColor = CCLayerColor::create(ccc4(20,20,20,230), 800, 480);
	addChild(pCCLayerColor, 16, 10);
	//重玩
	//CCNodeLoaderLibrary* ccNodeLoaderLibrary6 = CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
	//ccNodeLoaderLibrary6->registerCCNodeLoader("ccbGetItemLayer", ccbGetItemLayerLoader::loader());
	//cocos2d::extension::CCBReader* ccbReader6 = new cocos2d::extension::CCBReader(ccNodeLoaderLibrary6);
	//m_pGetItemCCB = ccbReader6->readNodeGraphFromFile("25.ccbi"/*, this*/);
	//m_pGetItemCCB->setVisible(false);
	//m_pGetItemCCB->setPosition(ccp(0,0));
	////SetScale(m_pSkillNode);
	//((ccbGetItemLayer*)m_pGetItemCCB)->setAnimationManager(ccbReader6->getAnimationManager(), this);
	//ccbReader6->release();
	//addChild(m_pGetItemCCB, 25, 56);

	((ccbGameoverMenu*)m_pGameoverNode)->Win( 100 );
}

void CGameControler::Lose(float _dt)
{
	//CCNodeLoaderLibrary* ccNodeLoaderLibrary6 = CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
	//ccNodeLoaderLibrary6->registerCCNodeLoader("ccbGetItemLayer", ccbGetItemLayerLoader::loader());
	//cocos2d::extension::CCBReader* ccbReader6 = new cocos2d::extension::CCBReader(ccNodeLoaderLibrary6);
	//m_pGetItemCCB = ccbReader6->readNodeGraphFromFile("25.ccbi"/*, this*/);
	//m_pGetItemCCB->setVisible(false);
	//m_pGetItemCCB->setPosition(ccp(0,0));
	////SetScale(m_pSkillNode);
	//((ccbGetItemLayer*)m_pGetItemCCB)->setAnimationManager(ccbReader6->getAnimationManager(), this);
	//ccbReader6->release();
	//addChild(m_pGetItemCCB, 25, 56);

	//CCLayerColor* pCCLayerColor = CCLayerColor::create(ccc4(20,20,20,230), 800, 480);
	//addChild(pCCLayerColor, 16, 10);
	((ccbGameoverMenu*)m_pGameoverNode)->Lose( 42 );
}

void CGameControler::ShowStar()
{
	if ( m_unLevel%6 != 5 && m_unLevel < 49 )
	{
		//int iStarAll = 3;//现得星星数
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
	//pSprite->runAction(CCSequence::create(pAction, CCCallFuncN::create(this, callfuncN_selector(CGameControler::CallBackRemoveSelf)), NULL));
	addChild(pSprite,24);
#endif
}

void CGameControler::ShowOverBtn( float _dt )
{
	//if ( ((ccbGameoverMenu*)m_pGameoverNode)->m_bWin )
	/*{
		((ccbGameoverBtnMenu*)m_pGameoverBtnNode)->Win();
		((ccbGameoverMenu*)m_pGameoverNode)->StartBtn();
		((ccbGetItemLayer*)m_pGetItemCCB)->Appear1(1);
	}
	else*/
	{
		((ccbGameoverBtnMenu*)m_pGameoverBtnNode)->Lose();
		//((ccbGetItemLayer*)m_pGetItemCCB)->Appear2(0);
	}
}
