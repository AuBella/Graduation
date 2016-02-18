#include"OperatorLayer.h"

OperatorLayer::OperatorLayer(void){};
OperatorLayer::~OperatorLayer(void){};

bool OperatorLayer::init(){
	if(!CCLayer::init()){
		return false;
	}
	
	/*auto shana = GlobalCtrl::getInstance()->shana;
	if(!(shana->isHurt) && !(shana->isAttack)){*/
	joyStick = JoyStick::create( "joystickBg.png", "joystick.png" );
	joyStick->setPosition( 60, 50 );
	this->addChild( joyStick );
	GlobalCtrl::getInstance()->joyStick = joyStick;

	skillButton = SkillButton::create();
	skillButton->setShana(GlobalCtrl::getInstance()->shana);
	CCSize visibleSize = CCEGLView::sharedOpenGLView()->getVisibleSize();
	skillButton->setPosition( CCPoint( visibleSize.width - 60, 50 ) );
	addChild( skillButton );
	
	GlobalCtrl::getInstance()->skillButton = skillButton;
	//SkillButton* skillButton1 = SkillButton::create();
	//CCSize visibleSize = CCEGLView::sharedOpenGLView()->getVisibleSize();
	/*skillButton1->setPosition( CCPoint( visibleSize.width - 60, 100 ) );
	skillButton1->setShana(GlobalCtrl::getInstance()->shana1);
	addChild( skillButton1 );*/
	return true;
};


void OperatorLayer::setUITouchEnabled(bool flag){
	joyStick->setTouchEnabled(flag);
	skillButton->setTouchEnabled(flag);
}