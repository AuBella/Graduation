#include"MainScene.h"

MainScene::MainScene(void){
	CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic("sound");
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("sound/mainscene_1.mp3", -1); 
};

MainScene::~MainScene(void){
	CocosDenshion::SimpleAudioEngine::sharedEngine()->stopBackgroundMusic("sound/mainscene_1.mp3");  
};

bool MainScene::init(){
	if(!CCScene::init())
		return false;
	//主页背景
	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	CCSprite* pSprite = CCSprite::create("res/MainSceneBg.png");
    pSprite->setPosition(ccp(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    this->addChild(pSprite, 0);

	
	CCMenuItemImage* menuChooseItem = CCMenuItemImage::create("Common/btn_pre_2.png", "Common/btn_nor_2.png", "Common/btn_dis_2.png", this, menu_selector(MainScene::MenuSettingCallback));
	char* name = getStringForUtf("存档");
	CCLabelTTF* pLabel = CCLabelTTF::create(name, "fonts/Marker Felt", 40);
	
	//CCLabelTTF* pLabel = CCLabelTTF::create("save file", "fonts/Marker Felt", 40);
	pLabel->setColor(ccc3(0,0,0));
	menuChooseItem->addChild(pLabel);
	pLabel->setPosition(ccp(menuChooseItem->getContentSize().width / 2, menuChooseItem->getContentSize().height / 2));
	CCMenuItemImage* menuChooseItem1 = CCMenuItemImage::create("Common/btn_pre_2.png", "Common/btn_nor_2.png", "Common/btn_dis_2.png", this, menu_selector(MainScene::MenuSettingCallback1));
	name = getStringForUtf("开始游戏");
	pLabel = CCLabelTTF::create(name, "fonts/Marker Felt", 40);
	//pLabel = CCLabelTTF::create("start game", "fonts/Marker Felt", 40);
	 
	pLabel->setPosition(ccp(menuChooseItem1->getContentSize().width / 2, menuChooseItem1->getContentSize().height / 2));
	pLabel->setColor(ccc3(0,0,0));
	menuChooseItem1->addChild(pLabel);
	//menuItem->setScale(winSize.width / 1000);
	CCMenu* menu1 = CCMenu::create( menuChooseItem,menuChooseItem1, NULL );
	menuChooseItem1->setPositionY(menuChooseItem->getContentSize().height + 10);
	menu1 ->setPosition(ccp(winSize.width/2,winSize.height/2));
	this->addChild(menu1);
	//主页button
	CCMenuItemImage* menuItem = CCMenuItemImage::create("Common/icon_nor_setting.png", "Common/icon_pre_setting.png", "Common/icon_dis_setting.png", this, menu_selector(MainScene::MenuSettingCallback));
	menuItem->setScale(winSize.width / 1000);
	
	CCMenu* menu = CCMenu::create( menuItem, NULL );
	menu -> setPosition(ccp(menuItem->getContentSize().width,menuItem->getContentSize().height));
	this->addChild(menu, 1);
	return true;
};
void MainScene::MenuSettingCallback1(CCObject* psender){
	GameScene* pScene = GameScene::create();
    CCDirector* pDirector = CCDirector::sharedDirector();
    pDirector->pushScene(pScene);
}
void MainScene::MenuSettingCallback(CCObject* psender){
	CCLabelTTF* pLabel = CCLabelTTF::create("BaiBai", "fonts/Helvetica", 40);//要显示的内容，字体，字号  
	pLabel->setString("TestTest");  
	pLabel->setColor(ccc3(0,0,0)); 
	pLabel->setPosition(ccp(520, 520));  
	this->addChild(pLabel, 1);  
}