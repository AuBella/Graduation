#include "GameLoading.h"
#include "GameLoadingMenu.h"
#include "GameLoading.h"
#include "AppDelegate.h"
#include"GameScene.h"
//#include "baseRes.h"

using namespace cocos2d;
using namespace cocos2d::extension;

CGameLoading* CGameLoading::GetGameLoadingLayer(cocos2d::CCScene* _pScene, int _level, int _difficult){
	//AppDelegate::AudioStopBgm();
	CGameLoading* pLayer = new CGameLoading;
	pLayer->autorelease();
	pLayer->m_pScene		= _pScene;
	pLayer->m_iLevel		= _level;
	pLayer->m_iDifficult	= _difficult;

	CCNodeLoaderLibrary* ccNodeLoaderLibrary = CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
	ccNodeLoaderLibrary->registerCCNodeLoader("ccbLoadingMenu", ccbGameLoadingMenuLoader::loader());
	cocos2d::extension::CCBReader* ccbReader = new cocos2d::extension::CCBReader(ccNodeLoaderLibrary);
	pLayer->m_pNode = ccbReader->readNodeGraphFromFile("10.ccbi"/*, this*/);
	pLayer->m_pNode->setPosition(ccp(0,0));
	((ccbGameLoadingMenu*)pLayer->m_pNode)->setAnimationManager(ccbReader->getAnimationManager());
	((ccbGameLoadingMenu*)pLayer->m_pNode)->Appear();
	ccbReader->release();
	SetScale(pLayer->m_pNode);
	_pScene->addChild(pLayer->m_pNode, 21, 4);

	SetScale(pLayer);
	_pScene->addChild(pLayer, 20, 3);

	CCLayerColor* pLayerColor = CCLayerColor::create(ccc4(20,20,20,230), 800, 480);
	SetScale(pLayerColor);
	_pScene->addChild(pLayerColor, 19, 2);
	return pLayer;
}

CGameLoading::CGameLoading(){
	scheduleOnce(schedule_selector(CGameLoading::Movie1), 0.90f);
}

CGameLoading::~CGameLoading(){}

void CGameLoading::Movie1( float _t ){
	((ccbGameLoadingMenu*)m_pNode)->Loading();
	scheduleOnce(schedule_selector(CGameLoading::Loading1), 0.80f);
}

void CGameLoading::Loading1( float _t ){
	//Õ½¶·
	m_pLayer = CGameControler::NewGameControler(m_pScene, m_iLevel, m_iDifficult);
	//AppDelegate::ChangeScene( CMainMenu::StartGame(level + 53, CMainMenu::GetDifficult()) );
			 
	scheduleOnce(schedule_selector(CGameLoading::Loading2), 1.20f);
}

void CGameLoading::Loading2( float _t ){
	((ccbGameLoadingMenu*)m_pNode)->Loading();
	m_pLayer->GameLoadingSecond();
	scheduleOnce(schedule_selector(CGameLoading::LoadingOver), 2.35f);
}

void CGameLoading::LoadingOver( float _t ){
	((ccbGameLoadingMenu*)m_pNode)->Disappear();
	scheduleOnce(schedule_selector(CGameLoading::Start), 0.80f);
	m_pScene->removeChildByTag(2);
}

void CGameLoading::Start( float _t ){
	int LevelNum = CCUserDefault::sharedUserDefault()->getIntegerForKey("currentlevelNum");
	GameScene* pscene = GameScene::create();
	pscene->StartGame(3-LevelNum,0);
	AppDelegate::ChangeScene(pscene);
}
