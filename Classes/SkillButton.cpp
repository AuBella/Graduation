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
	menu = CCMenu::create( skillItem, NULL );
	menu->setPosition( CCPoint(0,0) );
	this->addChild( menu );
	GlobalCtrl::getInstance()->menu = menu;
	return true;
}

void SkillButton::setShana(Shana *shana2){
	shana = shana2;
}

void SkillButton::setTouchEnabled(bool value){
	menu->setTouchEnabled(value);
}

void SkillButton::skillMenuCallback( CCObject* pSender ) {
	if( (!(shana->isHurt)) && (!(shana->shanaisAttack)) && (!(shana->isRunning))){
		int num = rand() % 100;
		CCNotificationCenter::sharedNotificationCenter()->postNotification("Attack",(CCObject *)num);
	
		if ( shana->getCanMutilAttack() ) {
		
			shana->shanaisAttack = true;
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
				shana->shanaisAttack = true;
			}
		}
	}
}