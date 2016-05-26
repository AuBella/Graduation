#include"CommonMonsterBloodBar.h"

CommonMonsterBloodBar::CommonMonsterBloodBar(){
}
CommonMonsterBloodBar::~CommonMonsterBloodBar(){}

bool CommonMonsterBloodBar::init(){
	if(!CCNode::init()){
		return false;
	}
	CCSprite* commonbackBlood = CCSprite::create("Monster/xue1.png");
	CCSprite* redProgress = CCSprite::create("Monster/xue2.png"); 
	redBloodProgress = CCProgressTimer::create(redProgress);
	redBloodProgress->setType(kCCProgressTimerTypeBar);
	redBloodProgress->setMidpoint(ccp(0,1));
	redBloodProgress->setBarChangeRate(CCPoint(1, 0));
	redBloodProgress->setPercentage(100);
	redBloodProgress->setAnchorPoint(ccp(0,0));
	redBloodProgress->setPosition(ccp(-5,5));
	commonbackBlood->addChild(redBloodProgress);
	this->addChild(commonbackBlood);
	return true;
}

void CommonMonsterBloodBar::setRedBloodBar(int num){
	redBloodProgress->setPercentage(1.0*num);
}

void CommonMonsterBloodBar::setRedBloodBarType(bool flag){
	if(flag)
		redBloodProgress->setMidpoint(ccp(0,1));
	else{
		redBloodProgress->setMidpoint(ccp(1,0));
	}
	heroIcon->setVisible(flag);
	monsterIconBg->setVisible(!flag);
}

	
void CommonMonsterBloodBar::setupHeroIcon(char* name){
	/*CCSize winSize = CCDirector::sharedDirector() -> getWinSize();
	CCSprite* monsterIcon = CCSprite::create("Common/817_hoodle.png");
	monsterIcon->setScale(2 * 0.7);
	monsterIcon->setPosition(ccp(monsterIcon->getContentSize().width / 2 + 15, heroIcon->getContentSize().height / 2));
	monsterIconBg->addChild(monsterIcon);*/
}