#include "settingScene.h"
#include"AppDelegate.h"
#include "baseRes.h"
#include "Common.h"
#include"GlobalCtrl.h"
 
PopScene::PopScene(){
	m_sNameSave = "";
	canEnter = false;
}
//ÒôÐ§ÉèÖÃ
bool PopScene::init(){
	if(!CCLayer::init()){
		return false;
	}
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	CCSprite * background = CCSprite::create("Common/settingbg.png");
	CCMenuItemImage* closeicon = CCMenuItemImage::create( 
		"Common/btn_pre_clo.png", "Common//btn_nor_clo.png", this, menu_selector(PopScene::closeButton));
	CCMenu* closeiconMenu = CCMenu::create(closeicon, NULL);
	closeicon->setPosition(ccp(- background->getContentSize().width/2 +120,-background->getContentSize().height/2));
	background->addChild(closeiconMenu);
    background->setPosition(ccp(winSize.width/2,winSize.height/2+50));
    this->addChild(background);
	CCSprite* pBoard = CCSprite::create("Common/ying.png");
	pBoard->setPosition(ccp(pBoard->getContentSize().width / 2 + 70,pBoard->getContentSize().height-25));
	background->addChild(pBoard, 1, 10);
    m_pItemVoice = CCMenuItemToggle::createWithTarget(this, 
		menu_selector(PopScene::setTitle), 
		CCMenuItemImage::create( "Common/guan.png", "Common/guan.png" ),
		CCMenuItemImage::create( "Common/kai.png", "Common/kai.png" ),
		NULL );
	m_pItemVoice->setPosition(ccp(238,10));
	m_pItemVoice->setSelectedIndex(AppDelegate::s_VoiceOpen);

	CCMenuItemImage* m_pNameBtn = CCMenuItemImage::create( 
		"Common/xiugai.png", "Common//xiugai.png", this, menu_selector(PopScene::InputName));
	m_pNameBtn->setPosition(ccp(142,120));
	CCMenu* pMenu = CCMenu::create(m_pItemVoice, m_pNameBtn, NULL);
	pMenu->setPosition(ccp(50,50));
	pBoard->addChild(pMenu);


	m_sNameSave = CCUserDefault::sharedUserDefault()->getStringForKey("name");
	if ( m_sNameSave == "" )
		m_sNameSave = "New Player";
	m_pNameInput = (CCTextFieldTTF*)CCTextFieldTTF::textFieldWithPlaceHolder("Your Name", "Thonburi", 36);
	m_pNameInput->setPosition(ccp(253, 170));
	m_pNameInput->setString(m_sNameSave.c_str());
	pBoard->addChild(m_pNameInput);
   return true;
}
 
void PopScene::registerWithTouchDispatcher(){
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this,
       kCCMenuHandlerPriority*2,true);
}
 
bool PopScene::ccTouchBegan(CCTouch * touch,CCEvent * pevent){
    return true;
}

void PopScene::setTitle(CCObject* sender){
	AppDelegate::AudioSwitch();
	m_pItemVoice->setSelectedIndex(AppDelegate::s_VoiceOpen);
	if ( AppDelegate::s_VoiceOpen )
		AppDelegate::AudioPlayBgm("sound/mainscene_1.mp3");
	else
		AppDelegate::AudioStopBgm();
}
void PopScene::setContent(CCObject* psender){}

void PopScene::closeButton(CCObject * psender){
	CCUserDefault::sharedUserDefault()->setStringForKey("name", m_pNameInput->getString());
	m_pNameInput->detachWithIME();
	GlobalCtrl::getInstance()->canEnter = true;
    this->removeFromParentAndCleanup(true);	
}
 
void PopScene::InputName( cocos2d::CCObject* sender ){
     m_pNameInput->attachWithIME();
}
