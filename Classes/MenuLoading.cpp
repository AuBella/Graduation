#include "MenuLoading.h"
#include "AppDelegate.h"
#include "GameLoadingMenu.h"
#include"GameScene.h"
#include "cocos-ext.h"  
#include"LevelMenu.h"

using namespace cocos2d;
using namespace cocos2d::extension;

CMenuLoading* CMenuLoading::GetMenuLoadingLayer(cocos2d::CCScene* _pScene, int _iLevel, int _difficult, bool _bShop){
	AppDelegate::AudioStopBgm();
	CMenuLoading* pLayer = new CMenuLoading;
	pLayer->autorelease();
	pLayer->m_pScene		= _pScene;
	pLayer->m_iLevel		= _iLevel;
	pLayer->m_iDifficult	= _difficult;
	pLayer->m_bShop			= _bShop;

	CMainMenu::SetStatus(-1);

	//ccbLoadingMenu,10ccbi,界面加载，tu6
	CCNodeLoaderLibrary* ccNodeLoaderLibrary = CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
	ccNodeLoaderLibrary->registerCCNodeLoader("ccbLoadingMenu", ccbGameLoadingMenuLoader::loader());
	cocos2d::extension::CCBReader* ccbReader = new cocos2d::extension::CCBReader(ccNodeLoaderLibrary);
	pLayer->m_pNode = ccbReader->readNodeGraphFromFile("10.ccbi");
	pLayer->m_pNode->setPosition(ccp(0,0));
	((ccbGameLoadingMenu*)pLayer->m_pNode)->setAnimationManager(ccbReader->getAnimationManager());
	((ccbGameLoadingMenu*)pLayer->m_pNode)->Appear();
	ccbReader->release();
	SetScale(pLayer->m_pNode);
	_pScene->addChild(pLayer->m_pNode, 21, 4);
	_pScene->addChild(pLayer, 20, 3);
	return pLayer;
}

CMenuLoading::CMenuLoading(){
	scheduleOnce(schedule_selector(CMenuLoading::Loading), 0.90f);
}

CMenuLoading::~CMenuLoading(){}

void CMenuLoading::Loading( float _t ){
	((ccbGameLoadingMenu*)m_pNode)->Loading();
	CMainMenu::AllAdd(m_pScene);
	scheduleOnce(schedule_selector(CMenuLoading::Loading1), 0.50f);
}

void CMenuLoading::Loading1( float _t ){
	scheduleOnce(schedule_selector(CMenuLoading::LoadingOver), 2.50f);
}

void CMenuLoading::LoadingOver( float _t ){
	((ccbGameLoadingMenu*)m_pNode)->Disappear();
	scheduleOnce(schedule_selector(CMenuLoading::Start), 0.80f);
	m_pScene->removeChildByTag(2);
}
//入口
void CMenuLoading::Start( float _t ){
	//挑战关卡			
	CMainMenu::SetStatus(2);
	CMainMenu::SetDifficult(m_iDifficult);
	AppDelegate::AudioPlayBgm("MS/Music/mainmenu/LevelChose.mp3");
	((ccbLevelMenu*)CMainMenu::GetMenuLevel())->Appear();
}
