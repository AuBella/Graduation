#include"OperatorLayer.h"

OperatorLayer::OperatorLayer(void){};
OperatorLayer::~OperatorLayer(void){
	CCNotificationCenter::sharedNotificationCenter()->removeObserver(this,"Hurt");
};

bool OperatorLayer::init(){
	if(!CCLayer::init()){
		return false;
	}
	heroBloodBar = CommonBloodBar::create();
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	heroBloodBar->setPosition(80+heroBloodBar->getContentSize().width, winSize.height - heroBloodBar->getContentSize().height- 25);
	heroBloodBar->setScale(0.5);
	this->addChild(heroBloodBar);
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
	CCNotificationCenter::sharedNotificationCenter()->addObserver(this,callfuncO_selector(OperatorLayer::ObserverFunction),"Hurt",NULL);  
	return true;
};


void OperatorLayer::setUITouchEnabled(bool flag){
	joyStick->setTouchEnabled(flag);
	skillButton->setTouchEnabled(flag);
}

//添加目标通知观察者之后调用的事件  
void OperatorLayer::ObserverFunction(CCObject * object){
	CCLog("Hurt--------------->>>>>>>>>>>>>>>>>>>>> %d ", (int)object);
	int num = (int)object;
	heroBloodBar->setRedBloodBar(num);
}