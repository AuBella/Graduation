#include"OperatorLayer.h"
#include "JoyStick.h"
#include "SkillButton.h"

OperatorLayer::OperatorLayer(void){};
OperatorLayer::~OperatorLayer(void){};

bool OperatorLayer::init(){
	if(!CCLayer::init()){
		return false;
	}
	JoyStick* joyStick = JoyStick::create( "joystickBg.png", "joystick.png" );
	joyStick->setPosition( 60, 50 );
	this->addChild( joyStick );

	SkillButton* skillButton = SkillButton::create();
	skillButton->setShana(GlobalCtrl::getInstance()->shana);
	CCSize visibleSize = CCEGLView::sharedOpenGLView()->getVisibleSize();
	skillButton->setPosition( CCPoint( visibleSize.width - 60, 50 ) );
	addChild( skillButton );

	//SkillButton* skillButton1 = SkillButton::create();
	//CCSize visibleSize = CCEGLView::sharedOpenGLView()->getVisibleSize();
	/*skillButton1->setPosition( CCPoint( visibleSize.width - 60, 100 ) );
	skillButton1->setShana(GlobalCtrl::getInstance()->shana1);
	addChild( skillButton1 );*/
	return true;
};