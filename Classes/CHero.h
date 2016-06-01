#ifndef _Hero_H_
#define _Hero_H_

#include "cocos2d.h"
//#include "CommonMonsterBloodBar.h"
#include"cocos-ext.h"
 USING_NS_CC_EXT;

class CHero : public cocos2d::CCLayer
{
public:
	CHero();
	~CHero();
	bool init();
	CCArmature* CreateVIP();
	CCArmature* m_pVIP;
	
	void HurtAnimation(int num);
	//CommonMonsterBloodBar* vipheroBlood;
	int redBlood;
	CREATE_FUNC(CHero);
//private:
};

#endif
