#include"MainScene.h"
#include "AppDelegate.h"
#include "MainMenu.h"
#include"GlobalCtrl.h"
#include "settingScene.h"
#include"paihangbangScene.h"
#include"RewardLayer.h"

MainScene::MainScene(void){
	AppDelegate::AudioInit1();
	AppDelegate::AudioPlayBgm("sound/mainscene_1.mp3", true);
};

MainScene::~MainScene(void){
	CocosDenshion::SimpleAudioEngine::sharedEngine()->stopBackgroundMusic("sound/mainscene_1.mp3");  
};

bool MainScene::init(){
	if(!CCScene::init())
		return false;
	//��ҳ����
	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	CCSprite* pSprite = CCSprite::create("res/MainSceneBg.png");
    pSprite->setPosition(ccp(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    this->addChild(pSprite, 0);
	//SetScale(pSprite);
	
	CCMenuItemImage* menuItem = CCMenuItemImage::create("Common/icon_nor_setting.png", "Common/icon_pre_setting.png", "Common/icon_dis_setting.png", this, menu_selector(MainScene::MenuSettingCallback));
	menuItem->setScale(winSize.width / 7 / menuItem->getContentSize().width);
	CCMenu* menu = CCMenu::create( menuItem, NULL );
	CCMenuItemImage* menuChooseItem = CCMenuItemImage::create("Common/paihangbang.png", "Common/paihangbang2.png",  this, menu_selector(MainScene::MenuSettingCallback2));
	CCMenuItemImage* menuChooseItem1 = CCMenuItemImage::create("Common/kaishiyouxi.png", "Common/kaishiyouxi2.png",  this, menu_selector(MainScene::MenuSettingCallback1));
	CCMenuItemImage* menuChooseItem2 = CCMenuItemImage::create("Common/kaishiyouxi.png", "Common/kaishiyouxi2.png",  this, menu_selector(MainScene::MenuSettingCallback3));
	CCMenu* menu1 = CCMenu::create( menuChooseItem,menuChooseItem1,menuChooseItem2, NULL );
	menuChooseItem1->setScale(winSize.width / 9 / menuItem->getContentSize().width);
	menuChooseItem->setScale(winSize.width / 7 / menuItem->getContentSize().width);
	//menuChooseItem1->setPositionY(menuChooseItem->getContentSize().height + 50 * winSize.width / 9 / menuItem->getContentSize().width);
	menuChooseItem1->setPositionY(menuChooseItem->getContentSize().height + menuChooseItem1->getContentSize().height + 50);
	menuChooseItem2->setPositionY(menuChooseItem->getContentSize().height + menuChooseItem1->getContentSize().height );
	menu1 ->setPosition(ccp(winSize.width/2 + origin.x,winSize.height/2 + origin.y));
	this->addChild(menu1);
	menu -> setPosition(ccp(menuItem->getContentSize().width,menuItem->getContentSize().height));
	this->addChild(menu, 1);
	SetScaleY(pSprite);
	//����
	return true;
};
//���а�ص�����
void MainScene::MenuSettingCallback2(CCObject* psender){
	if(GlobalCtrl::getInstance()->canEnter){
		GlobalCtrl::getInstance()->canSetting =false;
		GlobalCtrl::getInstance()->canEnter = false;
		paihangbangScene* paihang = paihangbangScene::create();
		this->addChild(paihang);
	}
}
//�ؿ��ص�����
void MainScene::MenuSettingCallback1(CCObject* psender){
	if(GlobalCtrl::getInstance()->canEnter){
		AppDelegate::ChangeScene(CMainMenu::StartMenu());
	}
}
//���ûص�����
void MainScene::MenuSettingCallback(CCObject* psender){
	if(GlobalCtrl::getInstance()->canSetting){
		GlobalCtrl::getInstance()->canEnter = false;
		GlobalCtrl::getInstance()->canSetting =false;
		PopScene* popLayer = PopScene::create();
		this->addChild(popLayer);
	}
}
void MainScene::MenuSettingCallback3(CCObject* psender){
		CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	CCRenderTexture *renderTexture = CCRenderTexture::create(visibleSize.width,visibleSize.height);
	renderTexture->begin(); 
	this->visit();
	//this->getParent()->visit();
	renderTexture->end();
	int TimeNum = 10;
	CCUserDefault::sharedUserDefault()->setBoolForKey("level_style", true);
	CCUserDefault::sharedUserDefault()->setIntegerForKey("level_killnum", 40);
	CCUserDefault::sharedUserDefault()->setIntegerForKey("level_medal", 20);
	CCUserDefault::sharedUserDefault()->setIntegerForKey("level_rewardmedal", 30);
	CCUserDefault::sharedUserDefault()->setBoolForKey("overachieve1", true);
	CCUserDefault::sharedUserDefault()->setBoolForKey("overachieve2", false);
	CCUserDefault::sharedUserDefault()->setBoolForKey("overachieve3", true);
	CCScene* pScene = RewardLayer::scene(renderTexture, TimeNum, 89);
	CCDirector::sharedDirector()->replaceScene(pScene);	
}
