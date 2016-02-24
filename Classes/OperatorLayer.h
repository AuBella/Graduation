#include"cocos2d.h"
#include "JoyStick.h"
#include "SkillButton.h"
#include"CommonBloodBar.h"
#include "Gamepause.h"  

USING_NS_CC;

class OperatorLayer:public CCLayer{
public:
	OperatorLayer(void);
	~OperatorLayer(void);
	virtual bool init();
	void setUITouchEnabled(bool flag);
	void MenuChoose();
	CREATE_FUNC(OperatorLayer);
private:
	JoyStick* joyStick;
	SkillButton* skillButton;   
	//添加目标通知观察者之后调用的事件  
    void ObserverFunction(CCObject * object);
	CommonBloodBar* heroBloodBar;
	CommonBloodBar* monsterBloodBar;
	void MenuChooseCallback(CCObject* pSender);
	void keyBackClicked();	//响应返回键
	void keyMenuClicked();	//响应Menu键
	CCMenu* menu;
};