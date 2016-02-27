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
    void ObserverFunction(CCObject * object);
	CommonBloodBar* heroBloodBar;
	CommonBloodBar* monsterBloodBar;
	void MenuChooseCallback(CCObject* pSender);
	void keyBackClicked();
	void keyMenuClicked();
	CCMenu* menu;
};