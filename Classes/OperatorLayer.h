#include"cocos2d.h"
#include "JoyStick.h"
#include "SkillButton.h"

USING_NS_CC;

class OperatorLayer:public CCLayer{
public:
	OperatorLayer(void);
	~OperatorLayer(void);
	virtual bool init();
	void setUITouchEnabled(bool flag);
	CREATE_FUNC(OperatorLayer);
private:
	JoyStick* joyStick;
	SkillButton* skillButton;
};