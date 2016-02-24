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
	//int iManSceneTag = CCDirector::sharedDirector()->getRunningScene()->getTag();//如果是主场景，则退出
	//if (MAIN_SCENE_TAG == iManSceneTag) {
	/*	CCDirector::sharedDirector()->end();
		#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
			exit(0);
		#endif*/
	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	CCRenderTexture *renderTexture = CCRenderTexture::create(visibleSize.width,visibleSize.height);

	//遍历当前类的所有子节点信息，画入renderTexture中。
	//这里类似截图。
	renderTexture->begin(); 
	this->getParent()->visit();
	renderTexture->end();

	//将游戏界面暂停，压入场景堆栈。并切换到GamePause界面
	CCDirector::sharedDirector()->pushScene(Gamepause::scene(renderTexture));
	CCLOG("==================>>>>>>>>>>>>>>>>>>>>>>>>>>> keyBackclicked" );
	//}
}
void OperatorLayer::keyMenuClicked() {

}

void OperatorLayer::setUITouchEnabled(bool flag){
	joyStick->setTouchEnabled(flag);
	skillButton->setTouchEnabled(flag);
}

//添加目标通知观察者之后调用的事件  
void OperatorLayer::ObserverFunction(CCObject * object){
	CCLog("Hurt--------------->>>>>>>>>>>>>>>>>>>>> %d ", (int)object);
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
	CCLOG("=======================enter menu +++++++++++++++++++ ");
	////得到窗口的大小
	//CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	//CCRenderTexture *renderTexture = CCRenderTexture::create(visibleSize.width,visibleSize.height);

	////遍历当前类的所有子节点信息，画入renderTexture中。
	////这里类似截图。
	//renderTexture->begin(); 
	//this->getParent()->visit();
	//renderTexture->end();

	////将游戏界面暂停，压入场景堆栈。并切换到GamePause界面
	//CCDirector::sharedDirector()->pushScene(Gamepause::scene(renderTexture));
	MenuChoose();
}
void OperatorLayer::MenuChoose(){
	CCLOG("=======================enter menu +++++++++++++++++++ ");
	//得到窗口的大小
	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	CCRenderTexture *renderTexture = CCRenderTexture::create(visibleSize.width,visibleSize.height);

	//遍历当前类的所有子节点信息，画入renderTexture中。
	//这里类似截图。
	renderTexture->begin(); 
	this->getParent()->visit();
	renderTexture->end();

	//将游戏界面暂停，压入场景堆栈。并切换到GamePause界面
	CCDirector::sharedDirector()->pushScene(Gamepause::scene(renderTexture));
}