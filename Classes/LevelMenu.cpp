#include "LevelMenu.h"
#include "baseRes.h"
#include "MainMenu.h"
#include "AppDelegate.h"
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
		for ( int i = 0; i < 6; i++ ){
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

void ccbLevelMenu::ccTouchesEnded( cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent ){
	/*if ( -1 != m_iChose && 2 == CMainMenu::GetStatus() )
	{
		CCSetIterator iter = pTouches->begin();
		CCPoint locationT = ((CCTouch*)(*iter))->getLocation();
		for ( int i = 0; i < 6; i++ )
		{
			CCPoint locationP = m_pNode[i]->getPosition();
			if ( abs(locationT.x - locationP.x*Scale_X) < d_fLevelPicW
				&& abs(locationT.y - locationP.y*Scale_Y) < d_fLevelPicH )
			{
				if ( m_iChose == i )
				{
					if ( !AppDelegate::s_LevelOpen[i+m_iLevel*6] || ((ccbLayer*)CMainMenu::GetMenuMain())->m_bShare )
					{
						m_iChose = -1;
						return;
					}
					if ( AppDelegate::s_FirstLogin == 4 )
					{
						if ( m_iChose != 0 )
						{
							m_iChose = -1;
							return;
						}
						AppDelegate::s_FirstLogin = 5;
						AppDelegate::SaveGuide();
					}
					if ( m_iChose + m_iLevel*6 >= LevelLimit*6 )
					{
						if ( getChildByTag(410) )
						{
							getChildByTag(410)->stopAllActions();
							removeChildByTag(410);
						}
						CCSprite* pSprite = CCSprite::create("tu14/qidai.png");
						pSprite->setPosition(ccp(400, 240));
						CCFadeOut* pAction = CCFadeOut::create(1.0f);
						pSprite->runAction(CCSequence::create(pAction,
							CCCallFunc::create(this, callfunc_selector(ccbLevelMenu::tipdisappear)), NULL));
						addChild(pSprite, 25, 410);
						return;
					}
					int level = m_iChose;
					CMainMenu::SetStatus(0);
					s_pccbLevelMenu = NULL;
					ccbShopMenu::s_pccbShopMenu = NULL;
					AppDelegate::ChangeScene( CMainMenu::StartGame(level + m_iLevel*6, CMainMenu::GetDifficult()) );
				}
				break;
			}
		}	}*/
		int level = m_iChose;
		CMainMenu::SetStatus(0);
		s_pccbLevelMenu = NULL;
		AppDelegate::ChangeScene( CMainMenu::StartGame(level + m_iLevel*6, CMainMenu::GetDifficult()) );
}

void ccbLevelMenu::tipdisappear(){}

void ccbLevelMenu::Appear(){
	m_iLevel = 0;
	CCSprite* bg = CCSprite::create(g_sBGPath[m_iLevel].c_str());
	this->addChild(bg, -10);
	SetScale(bg);
	for ( int i = 0; i < 4; i ++ )
	{
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