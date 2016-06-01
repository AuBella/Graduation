#include "GameControler.h"
#include "baseRes.h"
#include "CHero.h"
#include "AppDelegate.h"
#include"CommonMonsterBloodBar.h"

//extern CFlashControl* g_pHero;
using namespace cs;
using namespace cocos2d;

std::string s_BotBone[] =
{
	"kaiqiangshou",
	"huohua1",
	"huohua2",
};
CommonMonsterBloodBar* vipheroBlood;
CHero::CHero(){
	redBlood = 100;
}

CHero::~CHero(){}

bool CHero::init(){
	if(!CCLayer::init()){
		return false;
	}
	CCArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo("Role/vip.png", "Role/vip.plist", "Role/vip.json");
	m_pVIP = CCArmature::create("nvrenzhidongzuo");	
	vipheroBlood = CommonMonsterBloodBar::create();
	vipheroBlood->setPosition(0, m_pVIP->getContentSize().height + 10);
	vipheroBlood->setRedBloodBar(redBlood);
	m_pVIP->addChild(vipheroBlood);
	return true;
}

 void CHero::HurtAnimation(int num){
	/*if(isDead)
		return;*/
	//isHurt = true;
	 CCLOG("================VIP HURT %d", num);
	redBlood-=10;
	redBlood <= 0?0:redBlood;
	vipheroBlood->setRedBloodBar(redBlood);
	//CCNotificationCenter::sharedNotificationCenter()->postNotification("Hurt",(CCObject *)( 100+ redBlood));
	if(redBlood > 0){
		//CocosDenshion::SimpleAudioEngine::sharedEngine()->stopEffect(effectId);
		/*runStandAnimation();
		isHurt = false;
		isAttack = false;*/
	}
	else{
		/*isDead = true;
		effectId = CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sound/0312_03AF.wav");
		runDeadAnimation();*/
	}
 }

CCArmature* CHero::CreateVIP(){
	return m_pVIP;
}