#include "ControlerMenu.h"
#include "baseRes.h"
#include "AppDelegate.h"

using namespace cocos2d;
using namespace cocos2d::extension;

ccbControlMenu::ccbControlMenu()
	: m_AnimationManager(NULL)
{
	m_iTime			= 0;
	m_bGameStart	= false;
	m_pBloodGrid1 = CCSprite::create("tu4/zhengchang.png");
	m_pBloodGrid2 = CCSprite::create("tu4/hong.png");
	m_pBloodGrid1->setPosition( ccp(d_fBloodLocateX,480-d_fBloodLocateY) );
	m_pBloodGrid2->setPosition( ccp(d_fBloodLocateX,480-d_fBloodLocateY) );
	m_pBloodGrid1->setVisible(false);
	m_pBloodGrid2->setVisible(false);
	addChild(m_pBloodGrid1 ,4);
	addChild(m_pBloodGrid2 ,4);
}

ccbControlMenu::~ccbControlMenu()
{
	CC_SAFE_RELEASE_NULL(m_AnimationManager);
}

void ccbControlMenu::onNodeLoaded(cocos2d::CCNode * pNode,  cocos2d::extension::CCNodeLoader * pNodeLoader) 
{
	CCNode*	pBlood = pNode->getChildByTag(3012);
	pBlood->setZOrder(10);

	CCSprite* pLoadingBar1 = CCSprite::create("tu4/xue1.png");
	m_pProgressBar1= CCProgressTimer::create(pLoadingBar1);
	m_pProgressBar1->setPosition( ccp(d_fBloodX,480-d_fBloodY) );
	m_pProgressBar1->setType(kCCProgressTimerTypeBar);//
	m_pProgressBar1->setMidpoint(ccp(0, 1));
	m_pProgressBar1->setBarChangeRate(ccp(0, 1));
	m_pProgressBar1->setPercentage(100);
	m_pProgressBar1->setVisible(false); 
	addChild(m_pProgressBar1, 5);

	CCSprite* pLoadingBar2 = CCSprite::create("tu4/xue2.png");
	m_pProgressBar2= CCProgressTimer::create(pLoadingBar2);
	m_pProgressBar2->setPosition( ccp(d_fBloodX,480-d_fBloodY) );
	m_pProgressBar2->setType(kCCProgressTimerTypeBar);//
	m_pProgressBar2->setMidpoint(ccp(0, 1));
	m_pProgressBar2->setBarChangeRate(ccp(0, 1));
	m_pProgressBar2->setPercentage(100); 
	m_pProgressBar2->setVisible(false);
	addChild(m_pProgressBar2, 5);

	CCSprite* pLoadingBar3 = CCSprite::create("tu4/xue3.png");
	m_pProgressBar3= CCProgressTimer::create(pLoadingBar3);
	m_pProgressBar3->setPosition( ccp(d_fBloodX,480-d_fBloodY) );
	m_pProgressBar3->setType(kCCProgressTimerTypeBar);//
	m_pProgressBar3->setMidpoint(ccp(0, 1));
	m_pProgressBar3->setBarChangeRate(ccp(0, 1));
	m_pProgressBar3->setPercentage(100); 
	m_pProgressBar3->setVisible(false);
	addChild(m_pProgressBar3, 5);
}

SEL_MenuHandler ccbControlMenu::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char * pSelectorName) 
{
	return NULL;    
}

SEL_CCControlHandler ccbControlMenu::onResolveCCBCCControlSelector(CCObject * pTarget, const char * pSelectorName) 
{
	return NULL;
}

bool ccbControlMenu::onAssignCCBMemberVariable(CCObject * pTarget, const char * pMemberVariableName, CCNode * pNode) 
{
	return false;
}

bool ccbControlMenu::onAssignCCBCustomProperty(CCObject* pTarget, const char* pMemberVariableName, cocos2d::extension::CCBValue* pCCBValue)
{
	bool bRet = false;
	return bRet;
}

void ccbControlMenu::setAnimationManager(CCBAnimationManager *pAnimationManager, int _level)
{
	CC_SAFE_RELEASE_NULL(m_AnimationManager);
	m_AnimationManager = pAnimationManager;
	CC_SAFE_RETAIN(m_AnimationManager);
	m_iLevel = _level;
}

void ccbControlMenu::Appear()
{
	int a = m_iLevel;
	scheduleOnce(schedule_selector(ccbControlMenu::GameStart), 1.50f);
	if ( CGameControler::GetGameControler()->m_iLevelType == 1 || CGameControler::GetGameControler()->m_iLevelType == 3 )
		m_AnimationManager->runAnimationsForSequenceNamedTweenDuration("Default Timeline2", 0.0f);
	else
		m_AnimationManager->runAnimationsForSequenceNamedTweenDuration("Default Timeline", 0.0f);
}

void ccbControlMenu::SetGame( CGameControler* p )
{
	m_pGameControler = p;
}

void ccbControlMenu::ShowBlood( int _hp )
{
	if ( !m_bGameStart )
		return;
	m_iHP = _hp;
	if ( m_iHP < d_iBloodLess )
	{
		m_pProgressBar1->setVisible(false);
		m_pProgressBar2->setVisible(false);
		m_pProgressBar3->setVisible(true);
		m_pProgressBar3->setPercentage(m_iHP); 
	}
	else if ( m_iHP < d_iBloodNormal )
	{
		m_pProgressBar1->setVisible(false);
		m_pProgressBar2->setVisible(true);
		m_pProgressBar3->setVisible(false);
		m_pProgressBar2->setPercentage(m_iHP); 
	}
	else
	{
		m_pProgressBar1->setVisible(true);
		m_pProgressBar2->setVisible(false);
		m_pProgressBar3->setVisible(false);
		m_pProgressBar1->setPercentage(m_iHP); 
	}
	ShowBloodGrid();
}

void ccbControlMenu::ShowBloodGrid()
{
	if ( m_iHP < d_iBloodLess )
	{
		m_iTime++;
		if ( m_iTime > 200 )
			m_iTime = 1;
		int iShow = (m_iTime/8)%2;
		bool bShowGrid;
		if ( iShow )
			bShowGrid = true;
		else
			bShowGrid = false;
		m_pBloodGrid1->setVisible(bShowGrid);
		m_pBloodGrid2->setVisible(!bShowGrid);
	}
	else
	{
		m_pBloodGrid1->setVisible(true);
		m_pBloodGrid2->setVisible(false);
	}
}

void ccbControlMenu::GameStart( float _t )
{
	m_bGameStart = true;
}

void ccbControlMenu::SetType( int _type )
{
	char buffer[255];
	sprintf(buffer, "Default Timeline%d", _type+3);
	m_AnimationManager->runAnimationsForSequenceNamedTweenDuration(buffer, 0.0f);
}
