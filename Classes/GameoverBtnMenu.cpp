#include "GameoverBtnMenu.h"
#include "MainMenu.h"
#include "AppDelegate.h"
#include "Common.h"
//#include "ChoseHero.h"

using namespace cocos2d;
using namespace cocos2d::extension;

ccbGameoverBtnMenu* ccbGameoverBtnMenu::s_pccbGameoverBtnMenu = NULL;

ccbGameoverBtnMenu::ccbGameoverBtnMenu()
	: m_AnimationManager(NULL)
{
	s_pccbGameoverBtnMenu = this;
	m_bOnSell = false;
}

ccbGameoverBtnMenu::~ccbGameoverBtnMenu()
{
	s_pccbGameoverBtnMenu = NULL;
	CC_SAFE_RELEASE_NULL(m_AnimationManager);
}

void ccbGameoverBtnMenu::onNodeLoaded(cocos2d::CCNode * _pNode,  cocos2d::extension::CCNodeLoader * pNodeLoader) 
{
}

SEL_MenuHandler ccbGameoverBtnMenu::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char * pSelectorName) 
{
	CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "On1", ccbGameoverBtnMenu::OnContinue );
	CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "On2", ccbGameoverBtnMenu::OnShop );
	CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "On3", ccbGameoverBtnMenu::OnReplay );
	CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "On4", ccbGameoverBtnMenu::OnReturn );
	CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "On5", ccbGameoverBtnMenu::OnRechoseHero );
	return NULL;    
}

SEL_CCControlHandler ccbGameoverBtnMenu::onResolveCCBCCControlSelector(CCObject * pTarget, const char * pSelectorName) 
{
	return NULL;
}


bool ccbGameoverBtnMenu::onAssignCCBMemberVariable(CCObject * pTarget, const char * pMemberVariableName, CCNode * pNode) 
{
	return false;
}

bool ccbGameoverBtnMenu::onAssignCCBCustomProperty(CCObject* pTarget, const char* pMemberVariableName, cocos2d::extension::CCBValue* pCCBValue)
{
	bool bRet = false;
	return bRet;
}

void ccbGameoverBtnMenu::setAnimationManager(CCBAnimationManager *pAnimationManager, CGameControler* _pGameControler)
{
	CC_SAFE_RELEASE_NULL(m_AnimationManager);
	m_AnimationManager = pAnimationManager;
	CC_SAFE_RETAIN(m_AnimationManager);
	m_pGameControler = _pGameControler;
}

void ccbGameoverBtnMenu::Win()
{
	m_AnimationManager->runAnimationsForSequenceNamedTweenDuration("Default Timeline2", 0.0f);
}

void ccbGameoverBtnMenu::Lose()
{
	m_AnimationManager->runAnimationsForSequenceNamedTweenDuration("Default Timeline", 0.0f);
}

void ccbGameoverBtnMenu::OnContinue( cocos2d::CCObject *pSender )
{/*
	if ( m_pGameControler->m_bEndPress && pSender )
		return;*/
	/*if ( m_bOnSell )
		return;*/
//#ifdef GameTypeA
//#ifdef Plat_MM
//	if ( AppDelegate::m_Sell1 == 0 && m_pGameControler->m_unLevel > 4 )
//#else
//	if ( AppDelegate::m_Sell1 == 0 )
//#endif
//	{
//		Sell1();
//	}
//	else if ( m_pGameControler->m_unLevel < LevelLimit*6-1 )//测试,正式需修改
//	{
//		m_bOnSell = true;
//#else
//	if ( m_pGameControler->m_unLevel < 11 )//测试,正式需修改
//	{
//		m_bOnSell = true;
//#endif
//		AppDelegate::ChangeScene( CMainMenu::StartGame(m_pGameControler->m_unLevel+1, m_pGameControler->m_iDifficult) );
//	}
//	else
//	{
//		m_bOnSell = true;
//		AppDelegate::ChangeScene( CMainMenu::StartMenu() );
//	}
}

void ccbGameoverBtnMenu::OnShop( cocos2d::CCObject *pSender )
{
	/*if ( m_pGameControler->m_bEndPress && pSender )
		return;
	if ( m_bOnSell )
		return;
	m_bOnSell = true;
	int level = m_pGameControler->m_unLevel/6;
	AppDelegate::ChangeScene( CMainMenu::StartMenu(level, m_pGameControler->m_iDifficult, true) );*/
}

void ccbGameoverBtnMenu::OnReplay( cocos2d::CCObject *pSender )
{
	/*if ( m_pGameControler->m_bEndPress && pSender )
		return;
	if ( m_bOnSell )
		return;
	m_bOnSell = true;
	AppDelegate::ChangeScene( CMainMenu::StartGame(m_pGameControler->m_unLevel, m_pGameControler->m_iDifficult) );*/
}

void ccbGameoverBtnMenu::OnReturn(cocos2d::CCObject *pSender)
{
	/*if ( m_pGameControler->m_bEndPress && pSender )
		return;
	if ( m_bOnSell )
		return;
	m_bOnSell = true;
	m_pGameControler->GameOver(0.0f);*/
}

void ccbGameoverBtnMenu::OnRechoseHero( cocos2d::CCObject *pSender /*= NULL*/ )
{
}

void ccbGameoverBtnMenu::OnGetAchieve( cocos2d::CCObject *pSender /*= NULL*/ )
{
}

void ccbGameoverBtnMenu::ReturnCallBack( float _t )
{
}

void ccbGameoverBtnMenu::Sell1(){/*
#ifdef Plat_Telecom_Demo
	Sell1Resume();
	return;
#endif
	if ( m_bOnSell )
		return;
	m_bOnSell = true;

	CCLayerColor* pCCLayerColor = CCLayerColor::create(ccc4(20,20,20,230), 800, 480);
	m_pGameControler->addChild(pCCLayerColor, 49, 694);
	CCMenuItem* pItem1 = CCMenuItemImage::create("sell/huode2-1.png", "sell/huode2-2.png", this, menu_selector(ccbGameoverBtnMenu::Sell1Resume));
	CCMenuItem* pItem2 = CCMenuItemImage::create("sell/guan.png", "sell/guan.png", this, menu_selector(ccbGameoverBtnMenu::Sell1Back));
	pItem1->setPosition(ccp(725,195));
	pItem2->setPosition(ccp(728,437));
	CCMenu* pMenu = CCMenu::create(pItem1, pItem2, NULL);
	pMenu->setPosition(ccp(0,0));
	m_pGameControler->addChild(pMenu, 50, 697);

	CCSprite* pSprite1 = CCSprite::create("sell/di1.png");
	pSprite1->setPosition(ccp(400, 240));
	m_pGameControler->addChild(pSprite1, 51, 699);
	CCSprite* pSprite4 = CCSprite::create("sell/vip/tu.png");
	pSprite4->setPosition(ccp(400, 240));
	m_pGameControler->addChild(pSprite4, 51, 698);
	CCSprite* pSprite2 = common::CreateAnimation("sell/vip/meizi1.png", ccp(265, 190), ccp(0.5f, 0.5f),
		"sell/vip/meizi", 2, CCRect(0,0,282,284), true);
	m_pGameControler->addChild(pSprite2, 51, 696);
	CCSprite* pSprite3 = CCSprite::create("sell/vip/dang.png");
	pSprite3->setPosition(ccp(265, 50));
	m_pGameControler->addChild(pSprite3, 51, 695);*/
}

void ccbGameoverBtnMenu::Sell1Resume( cocos2d::CCObject *pSender)
{
	/*if ( pSender )
	{
	}
	else
	{
#ifndef Plat_Telecom_Demo
		AppDelegate::m_Sell1		= 1;
		AppDelegate::s_WeaponOwn[6] = 1;
		AppDelegate::s_WeaponOwn[9] = 1;
		if ( AppDelegate::s_HeroType == 0 )
		{
			AppDelegate::s_WeaponUse[0] = 6;
			AppDelegate::s_WeaponUse[1] = 9;
		}
		AppDelegate::s_BulletNum[9] += 100;
		if ( AppDelegate::s_BulletNum[9] > 999 )
			AppDelegate::s_BulletNum[9] = 999;
		AppDelegate::s_Healbox = 3;
		AppDelegate::s_GrenadeNum = 10;
		AppDelegate::s_Money += 9999;
		AppDelegate::SaveStatus();
#endif
		scheduleOnce(schedule_selector(ccbGameoverBtnMenu::Sell1Enter), 0.1f);
	}*/
}

void ccbGameoverBtnMenu::Sell1Enter(float _t)
{
	//AppDelegate::ChangeScene( CMainMenu::StartGame(m_pGameControler->m_unLevel+1, m_pGameControler->m_iDifficult) );
}

void ccbGameoverBtnMenu::Sell1Back( cocos2d::CCObject *pSender /*= NULL*/ )
{
	/*m_bOnSell = false;
	if ( m_pGameControler->getChildByTag(694) )
		m_pGameControler->getChildByTag(694)->removeFromParentAndCleanup(true);
	if ( m_pGameControler->getChildByTag(696) )
		m_pGameControler->getChildByTag(696)->removeFromParentAndCleanup(true);
	if ( m_pGameControler->getChildByTag(695) )
		m_pGameControler->getChildByTag(695)->removeFromParentAndCleanup(true);
	if ( m_pGameControler->getChildByTag(697) )
		m_pGameControler->getChildByTag(697)->removeFromParentAndCleanup(true);
	if ( m_pGameControler->getChildByTag(698) )
		m_pGameControler->getChildByTag(698)->removeFromParentAndCleanup(true);
	if ( m_pGameControler->getChildByTag(699) )
		m_pGameControler->getChildByTag(699)->removeFromParentAndCleanup(true);*/
}
