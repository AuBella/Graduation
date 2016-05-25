#ifndef _CCB_CCB_GAMVEOVER_H_
#define _CCB_CCB_GAMVEOVER_H_

#include "cocos2d.h"
#include "cocos-ext.h"
#include "GameControler.h"

class ccbGameoverMenu
	: public cocos2d::CCLayer
	, public cocos2d::extension::CCBSelectorResolver
	, public cocos2d::extension::CCBMemberVariableAssigner
	, public cocos2d::extension::CCNodeLoaderListener
{
public:
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(ccbGameoverMenu, create);

	ccbGameoverMenu();
	virtual ~ccbGameoverMenu();

	virtual cocos2d::SEL_MenuHandler onResolveCCBCCMenuItemSelector(cocos2d::CCObject * pTarget, const char * pSelectorName);
	virtual cocos2d::extension::SEL_CCControlHandler onResolveCCBCCControlSelector(cocos2d::CCObject * pTarget, const char * pSelectorName);
	virtual bool onAssignCCBMemberVariable(cocos2d::CCObject * pTarget, const char * pMemberVariableName, cocos2d::CCNode * pNode);
	virtual bool onAssignCCBCustomProperty(cocos2d::CCObject* pTarget, const char* pMemberVariableName, cocos2d::extension::CCBValue* pCCBValue);
	virtual void onNodeLoaded(cocos2d::CCNode * pNode, cocos2d::extension::CCNodeLoader * pNodeLoader);
	virtual cocos2d::SEL_CallFuncN onResolveCCBCCCallFuncSelector(cocos2d::CCObject * pTarget, const char* pSelectorName);

	void setAnimationManager(cocos2d::extension::CCBAnimationManager *pAnimationManager, int _level);
	void SetGame(CGameControler* p);	
	void Next(cocos2d::CCNode* sender);
	void Over(cocos2d::CCNode* sender);
	void OnShop(cocos2d::CCObject *pSender);
	void OnReplay(cocos2d::CCObject *pSender);
	void OnReturn(cocos2d::CCObject *pSender);
	void OnRechoseHero(cocos2d::CCObject *pSender = NULL);

	void Win(int _complate);
	void Lose(int _complate);

	void StartDigit(float _t);
	void Timer(float _t);
	void StartBtn();
	void AddOver();

	bool	m_bWin;
private:
	bool	m_bOverAddCombo;
	bool	m_bStartAddCombo;
	bool	m_bNowKill;
	bool	m_bNowMedal;
	bool	m_bNowGold;
	bool	m_bComboMoney;
	int		m_iNowKill;
	int		m_iNowMedal;
	int		m_iNowGold;
	int		m_iStateNowTime;
	int		m_iLevel;
	int		m_iWeapon;
	cocos2d::CCNode* m_pBoard;
	cocos2d::CCNode* m_pNode;
	cocos2d::CCSprite* m_pSprite;
	CGameControler*	m_pGameControler;
	cocos2d::extension::CCBAnimationManager* m_AnimationManager;
};

class CCBReader;
class ccbGameoverMenuLoader : public cocos2d::extension::CCLayerLoader 
{
public:
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(ccbGameoverMenuLoader, loader);
	CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(ccbGameoverMenu);
};

#endif
