#ifndef _CCB_CCB_GAMVELOADING_H_
#define _CCB_CCB_GAMVELOADING_H_

#include "cocos2d.h"
#include "cocos-ext.h"

class ccbGameLoadingMenu : public cocos2d::CCLayer, public cocos2d::extension::CCBSelectorResolver, public cocos2d::extension::CCBMemberVariableAssigner, public cocos2d::extension::CCNodeLoaderListener{
public:
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(ccbGameLoadingMenu, create);
	ccbGameLoadingMenu();
	virtual ~ccbGameLoadingMenu();

	virtual cocos2d::SEL_MenuHandler onResolveCCBCCMenuItemSelector(cocos2d::CCObject * pTarget, const char * pSelectorName);
	virtual cocos2d::extension::SEL_CCControlHandler onResolveCCBCCControlSelector(cocos2d::CCObject * pTarget, const char * pSelectorName);
	virtual bool onAssignCCBMemberVariable(cocos2d::CCObject * pTarget, const char * pMemberVariableName, cocos2d::CCNode * pNode);
	virtual bool onAssignCCBCustomProperty(CCObject* pTarget, const char* pMemberVariableName, cocos2d::extension::CCBValue* pCCBValue);
	virtual void onNodeLoaded(cocos2d::CCNode * pNode, cocos2d::extension::CCNodeLoader * pNodeLoader);

	void setAnimationManager(cocos2d::extension::CCBAnimationManager *pAnimationManager);

	void Appear();
	void Loading();
	void Disappear();

private:
	cocos2d::extension::CCBAnimationManager* m_AnimationManager;
};

//CCBReader,¶Áµµ
class CCBReader;
class ccbGameLoadingMenuLoader : public cocos2d::extension::CCLayerLoader 
{
public:
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(ccbGameLoadingMenuLoader, loader);
	CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(ccbGameLoadingMenu);
};

#endif
