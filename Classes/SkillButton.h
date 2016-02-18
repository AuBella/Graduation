#pragma once

#include "cocos2d.h"
#include "GlobalCtrl.h"
#include "Shana.h"

USING_NS_CC;

class SkillButton : public CCNode{
public:
	SkillButton();
	~SkillButton();

	virtual bool init();

	CREATE_FUNC( SkillButton );
	
	void setShana(Shana* name);
    virtual void setTouchEnabled(bool value);
private:
	void skillMenuCallback( CCObject* pSender );
	Shana* shana;
	CCMenu* menu;
};

