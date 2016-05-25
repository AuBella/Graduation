/*对话框场景类的头文件*/
//#ifndef _POP_SCENE_H_
//#define _POP_SCENE_H_
#include "cocos2d.h"
 
using namespace cocos2d;
 
class paihangbangScene : public CCLayer{
public:
	void ShowRank();
    bool init();
	cocos2d::CCNode*			m_pRankList;
	void ShowRank(int _type);
    void closeButton(CCObject * object);
	int rank_rank[6];
	std::string rank_name[6];
	int rank_score[6];
	void OnRank1(cocos2d::CCObject* sender);
	void OnRank2(cocos2d::CCObject* sender);
	void OnRank3(cocos2d::CCObject* sender);
	void OnRank4(cocos2d::CCObject* sender);
	cocos2d::CCMenuItemToggle* m_pRank1;
	cocos2d::CCMenuItemToggle* m_pRank2;
	cocos2d::CCMenuItemToggle* m_pRank3;
	cocos2d::CCMenuItemToggle* m_pRank4;
    CREATE_FUNC(paihangbangScene);
};
//#endif