#include"cocos2d.h"

USING_NS_CC;

class CommonBloodBar:public CCNode{
public:
	CommonBloodBar();
	~CommonBloodBar();
	virtual bool init();
	void setRedBloodBar(int num);
	CREATE_FUNC(CommonBloodBar);
private:
	CCProgressTimer *redBloodProgress;
};