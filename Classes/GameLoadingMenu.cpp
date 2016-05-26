#include "GameLoadingMenu.h"
using namespace cocos2d;
using namespace cocos2d::extension;

#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#define CCLogError(...) __android_log_print(ANDROID_LOG_ERROR,"cocos2d-x", __VA_ARGS__)
#endif

#define TIP_MAX		18

ccbGameLoadingMenu::ccbGameLoadingMenu()
	: m_AnimationManager(NULL)
{
}

ccbGameLoadingMenu::~ccbGameLoadingMenu()
{
}

void ccbGameLoadingMenu::onNodeLoaded(cocos2d::CCNode * pNode,  cocos2d::extension::CCNodeLoader * pNodeLoader) {
	CCDictionary *strings = CCDictionary::createWithContentsOfFileThreadSafe("tips.xml");
	char buffer[255];
	sprintf(buffer, "%d", rand()%TIP_MAX);

	CCNode* pWordBoard = pNode->getChildByTag(1);
	CCLabelTTF* pLaber = CCLabelTTF::create(((CCString*)strings->objectForKey(buffer))->m_sString.c_str(), "Arial", 22,
		CCSizeMake(26, 306), kCCTextAlignmentCenter, kCCVerticalTextAlignmentCenter);
	pLaber->setAnchorPoint(ccp(0.0f, 0.0f));
	pLaber->setPosition(ccp(403, 89));
	pLaber->setColor( ccc3(0, 0, 0) );
	pWordBoard->addChild(pLaber);
	strings->release();
}

SEL_MenuHandler ccbGameLoadingMenu::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char * pSelectorName) 
{
	return NULL;    
}

SEL_CCControlHandler ccbGameLoadingMenu::onResolveCCBCCControlSelector(CCObject * pTarget, const char * pSelectorName) 
{
	return NULL;
}

bool ccbGameLoadingMenu::onAssignCCBMemberVariable(CCObject * pTarget, const char * pMemberVariableName, CCNode * pNode) 
{
	return false;
}

bool ccbGameLoadingMenu::onAssignCCBCustomProperty(CCObject* pTarget, const char* pMemberVariableName, cocos2d::extension::CCBValue* pCCBValue)
{
	bool bRet = false;
	return bRet;
}

void ccbGameLoadingMenu::setAnimationManager(CCBAnimationManager *pAnimationManager)
{
	CC_SAFE_RELEASE_NULL(m_AnimationManager);
	m_AnimationManager = pAnimationManager;
	CC_SAFE_RETAIN(m_AnimationManager);
}
//初始动画
void ccbGameLoadingMenu::Appear(){
	m_AnimationManager->runAnimationsForSequenceNamedTweenDuration("Default Timeline fanhui", 0.0f);
	return;
}
//转盘动画
void ccbGameLoadingMenu::Loading(){
	m_AnimationManager->runAnimationsForSequenceNamedTweenDuration("Default Timeline zhuan", 0.0f);
	return;
}
//分离
void ccbGameLoadingMenu::Disappear(){
	m_AnimationManager->runAnimationsForSequenceNamedTweenDuration("Default Timeline", 0.0f);
	return;
}
