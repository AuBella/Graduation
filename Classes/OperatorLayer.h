#include"cocos2d.h"
#include "JoyStick.h"
#include "SkillButton.h"
#include"CommonBloodBar.h"

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
	//���Ŀ��֪ͨ�۲���֮����õ��¼�  
    void ObserverFunction(CCObject * object);
	CommonBloodBar* heroBloodBar;
};