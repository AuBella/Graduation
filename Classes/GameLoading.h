#ifndef _GAME_LOADING_H_
#define _GAME_LOADING_H_

#include "cocos2d.h"
#include "GameControler.h"

class CGameLoading : public cocos2d::CCLayer
{
public:
	CGameLoading();
	~CGameLoading();

	static CGameLoading* GetGameLoadingLayer(cocos2d::CCScene* _pScene, int _level, int _difficult);

	void Loading1(float _t);
	void Loading2(float _t);
	void LoadingOver(float _t);
	void Movie1(float _t);
	void Start(float _t);

	int					m_iLevel;
	cocos2d::CCScene*	m_pScene;
private:
	int					m_iDifficult;
	cocos2d::CCNode*	m_pNode;
	CGameControler*		m_pLayer;
};

#endif
