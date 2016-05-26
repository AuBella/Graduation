#ifndef _CCB_CCB_CONTROLER_H_
#define _CCB_CCB_CONTROLER_H_

#include "cocos2d.h"
#include "cocos-ext.h"
#include "GameControler.h"

#define d_iBloodLess	35
#define d_iBloodNormal	79

class ccbControlMenu
	: public cocos2d::CCLayer
	, public cocos2d::extension::CCBSelectorResolver
	, public cocos2d::extension::CCBMemberVariableAssigner
	, public cocos2d::extension::CCNodeLoaderListener
{
public:
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(ccbControlMenu, create);

	ccbControlMenu();
	virtual ~ccbControlMenu();

	virtual cocos2d::SEL_MenuHandler onResolveCCBCCMenuItemSelector(cocos2d::CCObject * pTarget, const char * pSelectorName);
	virtual cocos2d::extension::SEL_CCControlHandler onResolveCCBCCControlSelector(cocos2d::CCObject * pTarget, const char * pSelectorName);
	virtual bool onAssignCCBMemberVariable(cocos2d::CCObject * pTarget, const char * pMemberVariableName, cocos2d::CCNode * pNode);
	virtual bool onAssignCCBCustomProperty(cocos2d::CCObject* pTarget, const char* pMemberVariableName, cocos2d::extension::CCBValue* pCCBValue);
	virtual void onNodeLoaded(cocos2d::CCNode * pNode, cocos2d::extension::CCNodeLoader * pNodeLoader);

	void setAnimationManager(cocos2d::extension::CCBAnimationManager *pAnimationManager, int _level);
	void SetGame(CGameControler* p);

	void Appear();
	void GameStart(float _t);

	void ShowBlood(int _hp);
	void ShowBloodGrid();

	void SetType(int _type);

private:
	int	m_iLevel;
	cocos2d::CCNode*		m_pMenuNode;
	CGameControler*	m_pGameControler;
	cocos2d::extension::CCBAnimationManager* m_AnimationManager;

	int		m_iHP;
	int		m_iTime;
	bool	m_bGameStart;
	cocos2d::CCSprite*			m_pBloodGrid1;
	cocos2d::CCSprite*			m_pBloodGrid2;
	cocos2d::CCProgressTimer*	m_pProgressBar1;
	cocos2d::CCProgressTimer*	m_pProgressBar2;
	cocos2d::CCProgressTimer*	m_pProgressBar3;
};

class CCBReader;
class ccbControlMenuLoader : public cocos2d::extension::CCLayerLoader 
{
public:
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(ccbControlMenuLoader, loader);
	CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(ccbControlMenu);
};

#endif
