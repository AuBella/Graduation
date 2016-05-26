//#include "GameoverMenu.h"
//#include "AppDelegate.h"
//#include "GameoverBtnMenu.h"
//#include "Common.h"
////#include "GameControler.h"
//#include "baseRes.h"
////#include "GetItemLayer.h"
//
//using namespace cocos2d;
//using namespace cocos2d::extension;
//
//#define d_fGameOverNumLocate1	654, 388
//#define d_fGameOverNumLocate2	619, 301
//#define d_fGameOverNumLocate4	573, 205
//#define d_fGameOverNumLocate31	639, 280
//#define d_fGameOverNumLocate32	660, 280
//#define d_fGameOverNumLocate33	681, 280
//
//ccbGameoverMenu::ccbGameoverMenu()
//	: m_AnimationManager(NULL)
//{
//	m_bWin			= false;
//	m_bNowKill		= false;
//	m_bNowMedal		= false;
//	m_bNowGold		= false;
//	m_bComboMoney	= false;
//	m_bStartAddCombo= false;
//	m_bOverAddCombo	= false;
//	m_iWeapon		= 0;
//	m_iNowKill		= 0;
//	m_iNowMedal		= 0;
//	m_iNowGold		= 0;
//	m_iStateNowTime = 0;
//	m_pSprite		= NULL;
//}
//
//ccbGameoverMenu::~ccbGameoverMenu()
//{
//	CC_SAFE_RELEASE_NULL(m_AnimationManager);
//}
//
//void ccbGameoverMenu::onNodeLoaded(cocos2d::CCNode * pNode,  cocos2d::extension::CCNodeLoader * pNodeLoader) 
//{
//	m_pNode = pNode;
//	m_pBoard = pNode->getChildByTag(8);
//}
//
//SEL_MenuHandler ccbGameoverMenu::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char * pSelectorName) 
//{
//	CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "On1", ccbGameoverMenu::OnShop );
//	CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "On2", ccbGameoverMenu::OnReturn );
//	CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "On3", ccbGameoverMenu::OnReplay );
//	return NULL;    
//}
//
//SEL_CCControlHandler ccbGameoverMenu::onResolveCCBCCControlSelector(CCObject * pTarget, const char * pSelectorName) 
//{
//	return NULL;
//}
//
//bool ccbGameoverMenu::onAssignCCBMemberVariable(CCObject * pTarget, const char * pMemberVariableName, CCNode * pNode) 
//{
//	return false;
//}
//
//bool ccbGameoverMenu::onAssignCCBCustomProperty(CCObject* pTarget, const char* pMemberVariableName, cocos2d::extension::CCBValue* pCCBValue)
//{
//	bool bRet = false;
//	return bRet;
//}
//
//cocos2d::SEL_CallFuncN ccbGameoverMenu::onResolveCCBCCCallFuncSelector( CCObject * pTarget, const char* pSelectorName )
//{
//	CCB_SELECTORRESOLVER_CALLFUNC_GLUE(this, "repeat", ccbGameoverMenu::Next);
//	CCB_SELECTORRESOLVER_CALLFUNC_GLUE(this, "over", ccbGameoverMenu::Over);
//	return NULL;
//}
//
//void ccbGameoverMenu::setAnimationManager(CCBAnimationManager *pAnimationManager, int _level)
//{
//	CC_SAFE_RELEASE_NULL(m_AnimationManager);
//	m_AnimationManager = pAnimationManager;
//	CC_SAFE_RETAIN(m_AnimationManager);
//	m_iLevel = _level;
//}
//
//void ccbGameoverMenu::SetGame( CGameControler* p )
//{
//	m_pGameControler = p;
//}
//
//void ccbGameoverMenu::Win(int _complate)
//{
//	m_bWin = true;
//	/*if ( m_iLevel + 1 < d_iLevelNum*6 )
//	{
//		if ( AppDelegate::s_LevelOpen[m_iLevel+1] == 0 )
//			AppDelegate::s_LevelOpen[m_iLevel+1] = 1;
//	}*/
//	//AppDelegate::s_LevelOpen[m_iLevel] = 2;
//	scheduleOnce(schedule_selector(ccbGameoverMenu::StartDigit), 3.50f);
//	m_AnimationManager->runAnimationsForSequenceNamedTweenDuration("Default Timeline2", 0.0f);
//	//AppDelegate::AudioStopBgm();
//	AppDelegate::AudioPlayBgm("MS/Music/EfWinBG.mp3", false);
//
//	if ( m_iLevel%6 != 5 && m_iLevel < 49 )
//	{
//		//CCDictionary *strings = CCDictionary::createWithContentsOfFileThreadSafe("Tile/QustionStrings.xml");
//		for ( int i = 0; i < 3; i++ )
//		{
//			CCSprite* pSprite;
//			//if ( m_pGameControler->m_structQuestion.complate[m_pGameControler->m_structQuestion.index[i]-1] )
//				pSprite = CCSprite::create("tu5/kuai.png");
//			/*else
//				pSprite = CCSprite::create("tu5/kuai2.png");*/
//			pSprite->setAnchorPoint(ccp(0.5f, 0.5f));
//			m_pNode->getChildByTag(201+i)->addChild(pSprite);
//
//			char buffer[255];
//			//sprintf(buffer, "%d", m_iLevel*3+i);
//			////const char* str = ((CCString*)strings->objectForKey(buffer))->m_sString.c_str();
//			//CCLabelTTF* pLaber = CCLabelTTF::create(str, "Arial", 26,
//			//	CCSizeMake(260, 26), kCCTextAlignmentLeft, kCCVerticalTextAlignmentCenter);
//			sprintf(buffer, "Tile/QuestionInfo/%d.png", m_pGameControler->m_unLevel*3+i);
//			CCSprite* pLaber = CCSprite::create(buffer);
//			if ( pLaber )
//			{
//				pLaber->setAnchorPoint(ccp(0.0f, 0.0f));
//				pLaber->setPosition(ccp(-124, -12));
//				//pLaber->setColor( ccc3(0, 0, 0) );
//				m_pNode->getChildByTag(201+i)->addChild(pLaber);
//			}
//		}
//	}
//
//	if ( m_iLevel%6 != 5 && m_iLevel < 49 && m_iLevel != 30 )
//	{
//		CCSprite* pSprite1 = CCSprite::create("tu5/xingxing/hei.png");
//		CCSprite* pSprite2 = CCSprite::create("tu5/xingxing/hei.png");
//		CCSprite* pSprite3 = CCSprite::create("tu5/xingxing/hei.png");
//		pSprite1->setPosition(ccp(d_fStarLocateX1+2-m_pBoard->getPositionX()+308, d_fStarLocateY1-1));
//		pSprite2->setPosition(ccp(d_fStarLocateX2+2-m_pBoard->getPositionX()+308, d_fStarLocateY2-1));
//		pSprite3->setPosition(ccp(d_fStarLocateX3+2-m_pBoard->getPositionX()+308, d_fStarLocateY3-1));
//		m_pBoard->addChild(pSprite1);
//		m_pBoard->addChild(pSprite2);
//		m_pBoard->addChild(pSprite3);
//	}
//	else
//	{
//#ifndef GameTypeC
//		CCSprite* pSprite = CCSprite::create("tu5/boss/hei.png");
//		pSprite->setPosition(ccp(d_fStarLocateX2-m_pBoard->getPositionX()+310, d_fStarLocateY2-30));
//		m_pBoard->addChild(pSprite);
//#endif
//	}
//	//AppDelegate::s_Money += m_pGameControler->m_iMoneyTo + m_pGameControler->m_iComboMax*10;
//	////AppDelegate::s_Medal += m_pGameControler->m_iStateNumMedal;
//	//AppDelegate::s_GrenadeNum	= m_pGameControler->m_iGrenadeNum;
//	//AppDelegate::s_Healbox		= m_pGameControler->m_iHealBox;
//	//AppDelegate::s_BulletNum[AppDelegate::s_WeaponUse[1]] = m_pGameControler->m_iBulletNum[0];
//	////AppDelegate::s_BulletNum[AppDelegate::s_WeaponUse[2]] = m_pGameControler->m_iBulletNum[1];
//	//AppDelegate::s_SkillEnergy[0] = m_pGameControler->m_iStateSkill[0];
//	//AppDelegate::s_SkillEnergy[1] = m_pGameControler->m_iStateSkill[1];
//	//AppDelegate::s_KillMonster += m_pGameControler->m_iStateNumKill;
//	//AppDelegate::m_Sell2 = m_pGameControler->m_iSkillCanUse;
//	//AppDelegate::SaveStatus();
//	//AppDelegate::SaveLevel(m_iLevel);
//	//AppDelegate::SaveAchievement();
//	//InitBtn();
//}
//
//void ccbGameoverMenu::Lose(int _complate)
//{
//}
//
//void ccbGameoverMenu::StartDigit( float _t )
//{
//	schedule(schedule_selector(ccbGameoverMenu::Timer), 0.01f);
//}
//
//void ccbGameoverMenu::Timer( float _t )
//{
//	if ( m_bNowGold && m_bNowMedal && m_bNowKill && m_bComboMoney )
//	{
//		unschedule(schedule_selector(ccbGameoverMenu::Timer));
//		m_pGameControler->ShowStar();
//	}
//
//	bool bEffect = false;
//
//	m_iStateNowTime ++;
//		m_bNowKill = true;
//	common::ShowNumber(this, m_iNowKill/*AppDelegate::s_Money*/, 20, 19, d_fGameOverNumLocate1, "tu5/suzi.png", 801);
//
//	if ( m_iStateNowTime > 30 )
//	{
//			m_bNowMedal = true;
//		common::ShowNumber(this, m_iNowMedal/*AppDelegate::s_Money*/, 20, 19, d_fGameOverNumLocate2, "tu5/suzi.png", 802, 0, 1.1f);
//	}
//
//	if ( m_iStateNowTime > 60 && !m_bNowGold )
//	{
//		int digit = 10;
//		{
//			bEffect = true;
//			m_iNowGold += digit;
//		}
//		common::ShowNumber(this, m_iNowGold/*AppDelegate::s_Money*/, 20, 19, d_fGameOverNumLocate4, "tu5/suzi.png", 804, 0, 1.2f);
//	}
//
//	if ( m_bNowGold && !m_bStartAddCombo )
//	{
//		m_bStartAddCombo = true;
//		CCSprite* pSprite = CCSprite::create("tu5/jia.png");
//		int i = 0;
//		if ( m_iNowGold < 100 )
//			i = 1;
//		else if ( m_iNowGold < 1000 )
//			i = 2;
//		else if ( m_iNowGold < 10000 )
//			i = 3;
//		pSprite->setPosition(CCPoint(46 + 19*i + d_fGameOverNumLocate4 + 8));
//		common::ShowNumber(pSprite, m_pGameControler->m_iComboMax*10, 20, 19, 15, 0, "tu5/suzi.png", 804, 0, 1.2f);
//		addChild(pSprite, 0, 19);
//		pSprite->getChildByTag(804)->runAction(CCSequence::create(CCDelayTime::create(1.0f), CCFadeOut::create(0.5f), NULL));
//		pSprite->runAction( CCSequence::create(CCDelayTime::create(1.0f), CCFadeOut::create(0.5f), 
//			CCCallFunc::create(this, callfunc_selector(ccbGameoverMenu::AddOver)), NULL) );
//	}
//	else if ( m_bStartAddCombo && m_bOverAddCombo && !m_bComboMoney )
//	{
//		int digit = 5;
//		if ( m_pGameControler->m_iComboMax < 10 )
//			digit = 1;
//		{
//			m_iNowGold = m_pGameControler->m_iStateNumGold + m_pGameControler->m_iComboMax*10;
//			m_bComboMoney = true;
//		}
//		common::ShowNumber(this, m_iNowGold/*AppDelegate::s_Money*/, 20, 19, d_fGameOverNumLocate4, "tu5/suzi.png", 804, 0, 1.2f);
//	}
//
//	if ( bEffect )
//		AppDelegate::AudioPlayEffect("MS4/numadd.mp3");
//}
//
//void ccbGameoverMenu::AddOver()
//{
//	getChildByTag(19)->removeFromParentAndCleanup(true);
//	m_bOverAddCombo = true;
//}
//
//void ccbGameoverMenu::Next( CCNode* sender )
//{
//	m_AnimationManager->runAnimationsForSequenceNamedTweenDuration("Default Timeline copy", 0.0f);
//}
//
//void ccbGameoverMenu::Over( CCNode* sender )
//{
//	m_AnimationManager->runAnimationsForSequenceNamedTweenDuration("Default Timeline copy", 0.0f);
//}
//
//void ccbGameoverMenu::OnShop( cocos2d::CCObject *pSender )
//{
//}
//
//void ccbGameoverMenu::OnReplay( cocos2d::CCObject *pSender )
//{
//}
//
//void ccbGameoverMenu::OnReturn( cocos2d::CCObject *pSender )
//{
//}
//
//void ccbGameoverMenu::OnRechoseHero( cocos2d::CCObject *pSender /*= NULL*/ )
//{
//}
//
//void ccbGameoverMenu::StartBtn()
//{
//	m_AnimationManager->runAnimationsForSequenceNamedTweenDuration("Default Timeline2 copy", 0.0f);
//}