#include"CommonBloodBar.h"

CommonBloodBar::CommonBloodBar(){
}
CommonBloodBar::~CommonBloodBar(){}

//��init��ֱ�ӵ��� ����������ʹ��
//
//this->getBloodbar(guan1,20.0f);
bool CommonBloodBar::init(){
	if(!CCNode::init()){
		return false;
	}
	//CCSprite *pBloodKongSp = CCSprite::create("b.png");//��Ѫ��
	//pBloodKongSp->setPosition(Vec2(guaisprite->getContentSize().width / 2, guaisprite->getContentSize().height / 1.1));
	//guaisprite->addChild(pBloodKongSp);
	//CCSprite *pBloodManSp = CCSprite::create("z.png");//��Ѫ��
	//CCProgressTimer *pBloodProGress = CCProgressTimer::create(pBloodManSp);
	//pBloodProGress->setType(kCCProgressTimerTypeBar);
	//pBloodProGress->setBarChangeRate(Vec2(1, 0));
	//pBloodProGress->setMidpoint(Vec2(0, 0));
	//pBloodProGress->setPosition(Vec2(guaisprite->getContentSize().width / 2, guaisprite->getContentSize().height / 1.1));
	//pBloodProGress->setPercentage(a);
	//guaisprite->addChild(pBloodProGress, 1, 1);
	CCSprite* commonbackBlood = CCSprite::create("HeroState4.png");
	CCSprite* heroIcon = CCSprite::create("HeroState1.png");
	CCSprite* redProgress = CCSprite::create("HeroState2.png");
	CCSprite* blueProgress = CCSprite::create("HeroState3.png");
	heroIcon->setAnchorPoint(ccp(0, 0));
	commonbackBlood->addChild(heroIcon);
	//CCProgressTimer *pBloodProGress = CCProgressTimer::create(pBloodManSp);
	redBloodProgress = CCProgressTimer::create(blueProgress);
	redBloodProgress->setType(kCCProgressTimerTypeBar);
	redBloodProgress->setBarChangeRate(CCPoint(1, 0));
	redBloodProgress->setPercentage(100);
	redBloodProgress->setAnchorPoint(ccp(0,0));
	commonbackBlood->addChild(redBloodProgress);
	this->addChild(commonbackBlood);
	return true;
}

void CommonBloodBar::setRedBloodBar(int num){
	redBloodProgress->setPercentage(1.0*num);
}