#include "MainMenu.h"
#include "MenuLoading.h"
#include "AppDelegate.h"
#include "MainScene.h"
#include "cocos-ext.h" 
#include "LevelMenu.h"
#include "GameLoading.h"

using namespace cocos2d;
using namespace cocos2d::extension;

int CMainMenu::m_iStatus			= 0;
int CMainMenu::m_iDifficult			= 0;
bool CMainMenu::m_bOnSell			= false;
CCNode*	CMainMenu::m_pNodeLevel		= NULL;
CCScene* CMainMenu::m_pScene		= NULL;
int CMainMenu::m_iArmatureDigit = 2;
CMainMenu::CMainMenu(){}

CMainMenu::~CMainMenu(){}

bool CMainMenu::init(){
	m_iStatus			= 0;
	m_iDifficult		= 0;
	m_pNodeLevel		= NULL;
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	this->setKeypadEnabled(true);
#endif
	return true;
}
//关卡选择
CCScene* CMainMenu::StartMenu(int _level, int _difficult, bool _bShop){
	m_iStatus = -1;
	CCScene* pScene = CCScene::create();
	CMenuLoading::GetMenuLoadingLayer(pScene, _level, _difficult, _bShop);
	return pScene;
}

CCScene* CMainMenu::StartGame(int _level, int _difficult){
	CCLOG("--------------->>>>>>>>>>>>>>>%d%d", _level, _difficult);
	CCScene* pScene = CCScene::create();
	CGameLoading::GetGameLoadingLayer(pScene, _level, _difficult);
	return pScene;
}

void CMainMenu::AllAdd( cocos2d::CCScene* _pScene ){
	m_pScene = _pScene;
	CMainMenu::m_iArmatureDigit = 2;
	CMainMenu* pLayer = CMainMenu::create();
	_pScene->addChild(pLayer);
	m_pNodeLevel		= NULL;
	CCNode* pNode3 = CreateMenuLevel();
	SetScale(pNode3);
	_pScene->addChild(pNode3);
	((ccbLevelMenu*)pNode3)->m_AnimationManager->runAnimationsForSequenceNamedTweenDuration("Default Timeline copy", 0.0f);
}

CCNode* CMainMenu::CreateMenuLevel(){
	if ( !m_pNodeLevel ){
		CCNodeLoaderLibrary* ccNodeLoaderLibrary = CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
		ccNodeLoaderLibrary->registerCCNodeLoader("ccbLevelMenu", ccbLevelMenuLoader::loader());//详细
		cocos2d::extension::CCBReader* ccbReader = new cocos2d::extension::CCBReader(ccNodeLoaderLibrary);
		m_pNodeLevel = ccbReader->readNodeGraphFromFile("2.ccbi"/*, this*/);
		((ccbLevelMenu*)m_pNodeLevel)->setAnimationManager(ccbReader->getAnimationManager());
		m_pNodeLevel->setPosition(ccp(0,0));
		ccbReader->release();
	}
	return m_pNodeLevel;
}

void CMainMenu::ccTouchesBegan(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent){
	CCSetIterator iter = pTouches->begin();
	int location = (int)((CCTouch*)(*iter))->getLocation().x;
	int i = (location - 60)/80;
	//AppDelegate::ChangeScene( StartGame(i, CMainMenu::GetDifficult()) );
}
void CMainMenu::keyBackClicked(){
	//CCScene* pScene = MainScene::create();
	AppDelegate::ChangeScene(MainScene::create());
}
void CMainMenu::SetStatus( int _stats ){
	m_iStatus = _stats;
}
cocos2d::CCNode* CMainMenu::GetMenuLevel(){
	return m_pNodeLevel;
}
int CMainMenu::GetStatus(){
	return m_iStatus;
}

void CMainMenu::SetDifficult( int _difficult ){
	m_iDifficult = _difficult;
}

int CMainMenu::GetDifficult(){
	return m_iDifficult;
}
//释放资源
void CMainMenu::ReleaseArmatureData(){
	CMainMenu::m_iArmatureDigit --;
	if ( CMainMenu::m_iArmatureDigit == 0 ){
		CCTextureCache::sharedTextureCache()->removeAllTextures();
		CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFrames();
	}
}
