//’Ω∂∑Ω·À„
#ifndef _CCB_CCB_GAMVEOVERBTN_H_
#define _CCB_CCB_GAMVEOVERBTN_H_

#include "cocos2d.h"
#include "cocos-ext.h"
#include "GameControler.h"
class ccbGameoverBtnMenu
	: public cocos2d::CCLayer
	, public cocos2d::extension::CCBSelectorResolver
	, public cocos2d::extension::CCBMemberVariableAssigner
	, public cocos2d::extension::CCNodeLoaderListener
{
public:
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(ccbGameoverBtnMenu, create);

	ccbGameoverBtnMenu();
	virtual ~ccbGameoverBtnMenu();

	virtual cocos2d::SEL_MenuHandler onResolveCCBCCMenuItemSelector(cocos2d::CCObject * pTarget, const char * pSelectorName);
	virtual cocos2d::extension::SEL_CCControlHandler onResolveCCBCCControlSelector(cocos2d::CCObject * pTarget, const char * pSelectorName);
	virtual bool onAssignCCBMemberVariable(cocos2d::CCObject * pTarget, const char * pMemberVariableName, cocos2d::CCNode * pNode);
	virtual bool onAssignCCBCustomProperty(cocos2d::CCObject* pTarget, const char* pMemberVariableName, cocos2d::extension::CCBValue* pCCBValue);
	virtual void onNodeLoaded(cocos2d::CCNode * pNode, cocos2d::extension::CCNodeLoader * pNodeLoader);

	void setAnimationManager(cocos2d::extension::CCBAnimationManager *pAnimationManager, CGameControler* _pGameControler);

	void OnContinue(cocos2d::CCObject *pSender);
	void OnShop(cocos2d::CCObject *pSender);
	void OnReplay(cocos2d::CCObject *pSender);
	void OnReturn(cocos2d::CCObject *pSender);
	void OnRechoseHero(cocos2d::CCObject *pSender = NULL);
	void OnGetAchieve(cocos2d::CCObject *pSender = NULL);
	void ReturnCallBack(float _t);

	void Win();
	void Lose();

	void Sell1();
	void Sell1Resume(cocos2d::CCObject *pSender = NULL);
	void Sell1Back(cocos2d::CCObject *pSender = NULL);
	void Sell1Enter(float _t);

	static ccbGameoverBtnMenu* s_pccbGameoverBtnMenu;
	bool m_bOnSell;
private:
	CGameControler*	m_pGameControler;
	cocos2d::extension::CCBAnimationManager* m_AnimationManager;
};

class CCBReader;
class ccbGameoverBtnMenuLoader : public cocos2d::extension::CCLayerLoader 
{
public:
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(ccbGameoverBtnMenuLoader, loader);
	CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(ccbGameoverBtnMenu);
};

#endif
