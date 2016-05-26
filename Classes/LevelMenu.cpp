//关卡界面
#include "LevelMenu.h"
#include "baseRes.h"
#include "MainMenu.h"
#include "AppDelegate.h"
#include "GameScene.h"
#include "Common.h"

using namespace cocos2d;
using namespace cocos2d::extension;

#define NeedTime 100

ccbLevelMenu* ccbLevelMenu::s_pccbLevelMenu = NULL;
ccbLevelMenu::ccbLevelMenu()
	: m_AnimationManager(NULL)
	, m_iLevel(0)
{
	m_iChose	= -1;
}

ccbLevelMenu::~ccbLevelMenu(){
	s_pccbLevelMenu = NULL;
	CC_SAFE_RELEASE_NULL(m_AnimationManager);
}

void ccbLevelMenu::onNodeLoaded(cocos2d::CCNode * pNode,  cocos2d::extension::CCNodeLoader * pNodeLoader) {
	s_pccbLevelMenu = this;
	for ( int i = 0; i < 6; i ++ ){
		m_pNode[i] = pNode->getChildByTag(1+i);
	}
}

SEL_MenuHandler ccbLevelMenu::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char * pSelectorName) {
	return NULL;    
}

SEL_CCControlHandler ccbLevelMenu::onResolveCCBCCControlSelector(CCObject * pTarget, const char * pSelectorName) {
	return NULL;
}


bool ccbLevelMenu::onAssignCCBMemberVariable(CCObject * pTarget, const char * pMemberVariableName, CCNode * pNode) {
	return false;
}

bool ccbLevelMenu::onAssignCCBCustomProperty(CCObject* pTarget, const char* pMemberVariableName, cocos2d::extension::CCBValue* pCCBValue){
	bool bRet = false;
	return bRet;
}

void ccbLevelMenu::setAnimationManager(CCBAnimationManager *pAnimationManager){
	CC_SAFE_RELEASE_NULL(m_AnimationManager);
	m_AnimationManager = pAnimationManager;
	CC_SAFE_RETAIN(m_AnimationManager);
}

void ccbLevelMenu::ccTouchesBegan( cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent ){
	if ( -1 == m_iChose && 2 == CMainMenu::GetStatus()){
		CCSetIterator iter = pTouches->begin();
		CCPoint locationT = ((CCTouch*)(*iter))->getLocation();
		for ( int i = 0; i < 4; i++ ){
			CCPoint locationP = m_pNode[i]->getPosition();
			if ( abs(locationT.x - locationP.x*Scale_X) < d_fLevelPicW
				&& abs(locationT.y - locationP.y*Scale_Y) < d_fLevelPicH ){
				m_iChose = i;
				break;
			}
		}
	}
}

void ccbLevelMenu::ccTouchesMoved( cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent ){}

//关卡开始
void ccbLevelMenu::ccTouchesEnded( cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent ){
		int level = m_iChose;
		CMainMenu::SetStatus(0);
		s_pccbLevelMenu = NULL;
		if(level!=3)
			AppDelegate::ChangeScene( CMainMenu::StartGame(level + m_iLevel*6, CMainMenu::GetDifficult()) );
		else{
			//AppDelegate::ChangeScene( CMainMenu::StartGame(level + 53, CMainMenu::GetDifficult()) );
			 GameScene* pscene = GameScene::create();
			 pscene->StartGame(0,0);
			AppDelegate::ChangeScene(pscene);
		}
}

void ccbLevelMenu::tipdisappear(){}

void ccbLevelMenu::Appear(){
	m_iLevel = 0;
	CCSprite* bg = CCSprite::create(g_sBGPath[m_iLevel].c_str());
	this->addChild(bg, -10);
	SetScale(bg);
	for ( int i = 0; i < 4; i ++ ){
		if ( m_pNode[i]->getChildByTag(10) )
		{
			for ( int j = 7; j < 14; j++ )
				if ( m_pNode[i]->getChildByTag(j) )
					m_pNode[i]->getChildByTag(j)->removeFromParent();
		}
		CCSprite* pSprite	= NULL;
		CCSprite* pNum		= NULL;
			if ( i == 3 )
			{
				pSprite = CCSprite::create("tu2/di2.png");
				char boss[50];
#ifdef GameTypeC
				sprintf(boss, "tu2/suzi/boss1.png");
#else
				sprintf(boss, "tu2/suzi/boss%d.png", m_iLevel+1);
#endif
				CCSprite* pBoss = CCSprite::create(boss);
				pBoss->setPosition(ccp(100, 53));
				pSprite->addChild(pBoss);
			}
			else
			{
				pSprite = CCSprite::create("tu2/xiaoguankai.png");
				CCSprite* pBoss = CCSprite::create("tu2/suzi/tou.png");
				pBoss->setPosition(ccp(110, 53));
				pSprite->addChild(pBoss);
			}
		pSprite->setPosition(ccp(0,0));
		m_pNode[i]->removeChildByTag(10);
		m_pNode[i]->addChild(pSprite,0,10);

		CCSprite* pSpriteNum = CCSprite::create("tu2/suzi/shang.png");
		pSpriteNum->setPosition(ccp(0,0));
		m_pNode[i]->addChild(pSpriteNum, 1, 9);

		char buffer[50] ;
		sprintf(buffer,"tu2/suzi/%d.png",i+1);
		pNum= CCSprite::create(buffer);
		pNum->setPosition(CCPoint(50, 79));
		pSpriteNum->addChild(pNum);
	}

	m_iChose = -1;
	m_AnimationManager->runAnimationsForSequenceNamedTweenDuration("Default Timeline", 0.0f);
	scheduleOnce(schedule_selector(ccbLevelMenu::SetTouch), 0.7f);
}

void ccbLevelMenu::Return(){}

void ccbLevelMenu::ShopReturn()
{
	m_AnimationManager->runAnimationsForSequenceNamedTweenDuration("Default Timeline copy", 0.0f);
}

void ccbLevelMenu::ReturnCallBack( float _t ){}

void ccbLevelMenu::SetTouch( float _t ){
	setTouchEnabled(true);
}

void ccbLevelMenu::Sell1Resume( cocos2d::CCObject *pSender){}

void ccbLevelMenu::Sell1Enter(float _t){}

void ccbLevelMenu::Sell1Back( cocos2d::CCObject *pSender ){}