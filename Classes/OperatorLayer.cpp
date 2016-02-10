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
	CCSize visibleSize = CCEGLView::sharedOpenGLView()->getVisibleSize();
	skillButton->setPosition( CCPoint( visibleSize.width - 60, 50 ) );
	addChild( skillButton );
	return true;
};