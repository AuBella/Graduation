#include"OperatorLayer.h"

OperatorLayer::OperatorLayer(void){};
OperatorLayer::~OperatorLayer(void){
	CCNotificationCenter::sharedNotificationCenter()->removeObserver(this,"Hurt");
};

bool OperatorLayer::init(){
	if(!CCLayer::init()){
		return false;
	}
	//HeroBloodBar
	heroBloodBar = CommonBloodBar::create();
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	heroBloodBar->setPosition(80+heroBloodBar->getContentSize().width, winSize.height - heroBloodBar->getContentSize().height- 15);
	heroBloodBar->setScale(0.5);
	this->addChild(heroBloodBar);
	//MonsterBloodBar
	monsterBloodBar = CommonBloodBar::create();
	monsterBloodBar->setPosition(winSize.width - 200 -monsterBloodBar->getContentSize().width, winSize.height - monsterBloodBar->getContentSize().height- 15);
	monsterBloodBar->setScale(0.5);
	monsterBloodBar->setRedBloodBarType(false);
	monsterBloodBar->setVisible(false);
	this->addChild(monsterBloodBar);
	
	/*CCMenuItemImage* skillItem = CCMenuItemImage::create( "Encourage.png",
											"skillDown.png",this,
											menu_selector( SkillButton::skillMenuCallback ) );*/

	//MenuChoose
	CCMenuItemImage* menuItem = CCMenuItemImage::create("Common/btn_normal_stop.png", "Common/btn_press_stop.png", "Common/btn_stop.png", this, menu_selector(OperatorLayer::MenuChooseCallback));
	menuItem->setScale(0.5);
	
	//menuItem->setPosition(ccp(winSize.width  - menuItem->getContentSize().width / 2, winSize.height - 15));
	menu = CCMenu::create( menuItem, NULL );
	
	//menu->setPosition(ccp(winSize.width  - menuItem->getContentSize().width / 2, winSize.height - 15));
	menu -> setPosition(ccp(winSize.width - /*menuItem->getContentSize().width / 2*/15, winSize.height - 25));
	//menu->setScale(0.5);
	this->addChild(menu);
	//Controller
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

	this->setKeypadEnabled(true);
	return true;
};


void OperatorLayer::keyBackClicked() {
	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	CCRenderTexture *renderTexture = CCRenderTexture::create(visibleSize.width,visibleSize.height);
	renderTexture->begin(); 
	this->getParent()->visit();
	renderTexture->end();
	CCDirector::sharedDirector()->pushScene(Gamepause::scene(renderTexture));
}
void OperatorLayer::keyMenuClicked() {}

void OperatorLayer::setUITouchEnabled(bool flag){}

void OperatorLayer::ObserverFunction(CCObject * object){
	int num = (int)object;
	if(num / 100 >= 10){
		if(num % 100 == 0)
			joyStick->setTouchEnabled(false);
		else
			joyStick->setTouchEnabled(true);
		heroBloodBar->setRedBloodBar(num % 100);
	}
	else {
		monsterBloodBar->setRedBloodBar(num % 100);
		if(num % 100!= 0)
			monsterBloodBar->setVisible(true);
		else
			monsterBloodBar->setVisible(false);
	}
}

void OperatorLayer::MenuChooseCallback(CCObject* psender){
	MenuChoose();
}
void OperatorLayer::MenuChoose(){
	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	CCRenderTexture *renderTexture = CCRenderTexture::create(visibleSize.width,visibleSize.height);
	renderTexture->begin(); 
	this->getParent()->visit();
	renderTexture->end();
	CCDirector::sharedDirector()->pushScene(Gamepause::scene(renderTexture));
}