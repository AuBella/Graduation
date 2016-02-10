#include "SkillButton.h"
#include "GlobalCtrl.h"
#include "Shana.h"


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
	return true;
}


void SkillButton::skillMenuCallback( CCObject* pSender ) {
	//log( "skill" );
	auto shana = GlobalCtrl::getInstance()->shana;
	if ( shana->getCanMutilAttack() ) {
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