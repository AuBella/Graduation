#include "SkillButton.h"


SkillButton::SkillButton() {}


SkillButton::~SkillButton() {}


bool SkillButton::init() {
	if( !CCNode::init() )
		return false;
	CCMenuItemImage* skillItem = CCMenuItemImage::create( "Encourage.png",
											"skillDown.png",this,
											menu_selector( SkillButton::skillMenuCallback ) );
	//skillItem->setPosition( Vec2::ZERO );
	skillItem->setPosition( CCPoint(0,0) );
	CCMenu* menu = CCMenu::create( skillItem, nullptr );
	menu->setPosition( CCPoint(0,0) );
	this->addChild( menu );
	GlobalCtrl::getInstance()->menu = menu;
	return true;
}

void SkillButton::setShana(Shana *shana2){
	shana = shana2;
}

void SkillButton::skillMenuCallback( CCObject* pSender ) {
	auto shana = GlobalCtrl::getInstance()->shana;
	if(!shana->isHurt){
	int num = rand() % 100;
	CCNotificationCenter::sharedNotificationCenter()->postNotification("Attack",(CCObject *)num);
	
	CCLOG( "skill %f",shana->isHurt );
	shana->isAttack = true;
	if ( shana->getCanMutilAttack() ) {
		//this ->setTouchEnabled(false);
		//shana->setCanMutilAttack(true);
		switch ( shana->getCurSkillState() ) {
			case SKILL_A:
				if ( shana->getCurState() == AC_STAND ) {
					shana->runSkillBAnimation();
				}
				break;
			case SKILL_B:
				if ( shana->getCurState() == AC_STAND ) {
					shana->runSkillCAnimation();
				}
				break;
			case SKILL_C:
				if ( shana->getCurState() == AC_STAND ) {
					shana->runSkillDAnimation();
				}
			case SKILL_D:
				if ( shana->getCurState() == AC_STAND ) {
					shana->runSkillEAnimation();
				}
				break;
			default:
				break;
		}
	} else {
		if ( shana->getCurState() == AC_STAND ) {
			shana->runSkillAAnimation();
		}
	}
	}
}