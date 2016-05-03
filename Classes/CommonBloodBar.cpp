#include"CommonBloodBar.h"

CommonBloodBar::CommonBloodBar(){
}
CommonBloodBar::~CommonBloodBar(){}

bool CommonBloodBar::init(){
	if(!CCNode::init()){
		return false;
	}
	CCSprite* commonbackBlood = CCSprite::create("Common/Boss_bg_middle.png");
	CCSprite* commonbackBlood_1 = CCSprite::create("Common/boss_bg_head.png");
	CCSprite* commonbackBlood_2 = CCSprite::create("Common/Boss_bg_back.png");
	heroIcon = CCSprite::create("Common/commonIconBg.png");
	monsterIconBg = CCSprite::create("Common/commonIconBg.png");
	setupHeroIcon("sss");
	//CCSprite* monsterIcon = CCSprite::create("
	heroIcon->setScale(0.7);
	monsterIconBg->setScale(0.7);
	
	CCSprite* redProgress = CCSprite::create("Common/hp_monster_r.png"); 
	//CCTexture2D* texture = CCTextureCache::sharedTextureCache()->addImage("Common/hp_monster_y.png");
 //   redProgress->setTexture(texture);
	CCSprite* redProgress_1 = CCSprite::create("Common/hp_monster_y.png");
	CCSprite* redProgress_2 = CCSprite::create("Common/hp_monster_b.png");
	CCSprite* redProgress_3 = CCSprite::create("Common/hp_monster_g.png");
	commonbackBlood->setPosition(ccp(100, 0));
	commonbackBlood_1->setPosition(ccp(-70, 0));
	commonbackBlood_2->setPosition(ccp(commonbackBlood->getContentSize().width - 60, 0));

	redBloodProgress = CCProgressTimer::create(redProgress);
	redBloodProgress->setType(kCCProgressTimerTypeBar);
	redBloodProgress->setMidpoint(ccp(0,1));
	redBloodProgress->setBarChangeRate(CCPoint(1, 0));
	redBloodProgress->setPercentage(100);
	redBloodProgress->setAnchorPoint(ccp(0,0));
	redBloodProgress->setPosition(ccp(-5,5));

	heroIcon->setPosition(ccp(-50,0));
	monsterIconBg->setPosition(ccp(50,0));
	monsterIconBg->setVisible(false);
	commonbackBlood->addChild(redBloodProgress);
	commonbackBlood->addChild(heroIcon);
	this->addChild(commonbackBlood_1);
	this->addChild(commonbackBlood_2);
	commonbackBlood_2->addChild(monsterIconBg);
	this->addChild(commonbackBlood);
	return true;
}

void CommonBloodBar::setRedBloodBar(int num){
	redBloodProgress->setPercentage(1.0*num);
}

void CommonBloodBar::setRedBloodBarType(bool flag){
	if(flag)
		redBloodProgress->setMidpoint(ccp(0,1));
	else{
		redBloodProgress->setMidpoint(ccp(1,0));
	}
	heroIcon->setVisible(flag);
	monsterIconBg->setVisible(!flag);
}

	
void CommonBloodBar::setupHeroIcon(char* name){
	CCSize winSize = CCDirector::sharedDirector() -> getWinSize();
	CCSprite* monsterIcon = CCSprite::create("Common/817_hoodle.png");
	monsterIcon->setScale(2 * 0.7);
	monsterIcon->setPosition(ccp(monsterIcon->getContentSize().width / 2 + 15, heroIcon->getContentSize().height / 2));
	monsterIconBg->addChild(monsterIcon);
}