#ifndef _CCB_CCB_LEVEL_H_
#define _CCB_CCB_LEVEL_H_

#include "cocos2d.h"
#include "cocos-ext.h"

class ccbLevelMenu
	: public cocos2d::CCLayer
	, public cocos2d::extension::CCBSelectorResolver
	, public cocos2d::extension::CCBMemberVariableAssigner
	, public cocos2d::extension::CCNodeLoaderListener
{
public:
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(ccbLevelMenu, create);

	ccbLevelMenu();
	virtual ~ccbLevelMenu();

	virtual cocos2d::SEL_MenuHandler onResolveCCBCCMenuItemSelector(cocos2d::CCObject * pTarget, const char * pSelectorName);
	virtual cocos2d::extension::SEL_CCControlHandler onResolveCCBCCControlSelector(cocos2d::CCObject * pTarget, const char * pSelectorName);
	virtual bool onAssignCCBMemberVariable(cocos2d::CCObject * pTarget, const char * pMemberVariableName, cocos2d::CCNode * pNode);
	virtual bool onAssignCCBCustomProperty(cocos2d::CCObject* pTarget, const char* pMemberVariableName, cocos2d::extension::CCBValue* pCCBValue);
	virtual void onNodeLoaded(cocos2d::CCNode * pNode, cocos2d::extension::CCNodeLoader * pNodeLoader);

	void setAnimationManager(cocos2d::extension::CCBAnimationManager *pAnimationManager);

	virtual void ccTouchesBegan(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);
	virtual void ccTouchesMoved(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);
	virtual void ccTouchesEnded(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);

	void Appear();
	void Return();
	void ShopReturn();
	void ReturnCallBack(float _t);
	void SetTouch(float _t);

	//void Sell1();
	void Sell1Resume(cocos2d::CCObject *pSender = NULL);
	void Sell1Back(cocos2d::CCObject *pSender = NULL);
	void tipdisappear();
	void Sell1Enter(float _t);
	static ccbLevelMenu* s_pccbLevelMenu;
	int					m_iChose;
	cocos2d::extension::CCBAnimationManager* m_AnimationManager;
private:
	int					m_iLevel;
	cocos2d::CCNode*	m_pNode[7];
};

class CCBReader;
class ccbLevelMenuLoader : public cocos2d::extension::CCLayerLoader {
public:
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(ccbLevelMenuLoader, loader);
	CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(ccbLevelMenu);
};

#endif
