#ifndef _Menu_LOADING_H_
#define _Menu_LOADING_H_

#include "cocos2d.h"
#include "MainMenu.h"

class CMenuLoading : public cocos2d::CCLayer
{
public:
	CMenuLoading();
	~CMenuLoading();

	static CMenuLoading* GetMenuLoadingLayer(cocos2d::CCScene* _pScene, int _iLevel = -1, int _difficult = -1, bool bShop = false);

	void Loading(float _t);
	void Loading1(float _t);
	void LoadingOver(float _t);
	void Start(float _t);

	int					m_iLevel;
	cocos2d::CCScene*	m_pScene;
private:
	int					m_iDifficult;
	bool				m_bShop;
	cocos2d::CCNode*	m_pNode;
	CMainMenu*			m_pLayer;
};

#endif
