#include"cocos2d.h"

USING_NS_CC;

class CommonMonsterBloodBar:public CCNode{
public:
	CommonMonsterBloodBar();
	~CommonMonsterBloodBar();
	virtual bool init();
	void setRedBloodBar(int num);
	void setRedBloodBarType(bool flag);
	void setupHeroIcon(char* name);
	CREATE_FUNC(CommonMonsterBloodBar);
private:
	CCProgressTimer *redBloodProgress;
	CCSprite* heroIcon;
	CCSprite* monsterIconBg;
};