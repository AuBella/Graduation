#include"RewardLayer.h"
#include "GameScene.h"
RewardLayer::RewardLayer(){}

RewardLayer::~RewardLayer(){};
CCScene* RewardLayer::scene(CCRenderTexture* sqr, int num, int redBlood){
    CCScene *scene = CCScene::create();
    RewardLayer *layer = RewardLayer::create();
		scene->addChild(layer,1);//����Ϸ������棬���ǻ�Ҫ��������Ű�ť
	//���Ӳ��֣�ʹ��Game�����н�ͼ��sqr����ͼƬ����Sprite
	//����Sprite��ӵ�GamePause��������
	//�õ����ڵĴ�С
	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	CCSprite *back_spr = CCSprite::createWithTexture(sqr->getSprite()->getTexture());  
	back_spr->setPosition(ccp(visibleSize.width/2,visibleSize.height/2)); //����λ��,������������λ�á�
	back_spr->setFlipY(true);            //��ת����ΪUI�����OpenGL���겻ͬ
	back_spr->setColor(cocos2d::ccGRAY); //ͼƬ��ɫ���ɫ
	scene->addChild(back_spr);


	//�����Ϸ��ͣ����Сͼ�������Ű�ť
	CCSprite *back_small_spr = CCSprite::create("Common/rewardresult/bg.jpg");
	back_small_spr->setScale(0.1);
	back_small_spr->setPosition(ccp(visibleSize.width/2,visibleSize.height/2)); //����λ��,������������λ�á�
	CCSprite* winBg = CCSprite::create("Common/rewardresult/win.png");
	//ʤ��λ��
	float winPosHeight = back_small_spr->getContentSize().height - winBg->getContentSize().height* 2;
	winBg->setPosition(ccp(back_small_spr->getContentSize().width /2, winPosHeight));
	back_small_spr->addChild(winBg);
	//����λ��
	CCSprite* starBg_1 = CCSprite::create("Common/rewardresult/bg_star.png");
	CCSprite* star_1 = CCSprite::create("Common/rewardresult/star.png");
	CCSprite* star_2 = CCSprite::create("Common/rewardresult/star.png");
	CCSprite* star_3 = CCSprite::create("Common/rewardresult/star.png");
	//CCArray* starArray = CCArray::createWithCapacity(100);
	//starArray->addObject(star_1);
	//starArray->addObject(star_2);
	//starArray->addObject(star_3);
	//
	//CCLOG("REward%d", starArray->count());
	////starArray->retain();

	starBg_1->setPosition(ccp(back_small_spr->getContentSize().width / 2 - 100, winPosHeight - 100));
	starBg_1->addChild(star_1);
	star_1->setAnchorPoint(ccp(0,0));
	back_small_spr->addChild(starBg_1);

	CCSprite* starBg_2 = CCSprite::create("Common/rewardresult/bg_star.png");
	starBg_2->setPosition(ccp(back_small_spr->getContentSize().width / 2, winPosHeight - 100));
	starBg_2->addChild(star_2);
	star_2->setAnchorPoint(ccp(0,0));
	back_small_spr->addChild(starBg_2);

	CCSprite* starBg_3 = CCSprite::create("Common/rewardresult/bg_star.png");
	starBg_3->setPosition(ccp(back_small_spr->getContentSize().width / 2 + 100, winPosHeight - 100));
	starBg_3->addChild(star_3);
	star_3->setAnchorPoint(ccp(0,0));
	//star_3->setVisible(false);
	back_small_spr->addChild(starBg_3);
	
	//����������Ŀ��1~3��
	int starnum = 3;
	if(num < 100){
		starnum--;
	}
	Shana* shana = GlobalCtrl::getInstance()->shana;
	if(num < 100 || redBlood < 90){
		starnum--;
	}
	//for(int i = starArray->count(); i > starnum;i--){
	//	CCSprite* tempstar = (CCSprite*)starArray->objectAtIndex(i);
	//	//tempstar->setVisible(false);
	//}
	if(starnum <= 2){
		star_3->setVisible(false);
	}
	else
		star_3->setVisible(true);
	if(starnum <= 1)
		star_2->setVisible(false);
	else
	star_2->setVisible(true);
	if(starnum <=0){
		star_1->setVisible(false);
	}
	else
		star_1->setVisible(true);
	scene->addChild(back_small_spr);
    return scene;
}

void RewardLayer::calculationStars(int Time){}


bool RewardLayer::init(){
	if(!CCLayer::init()){
		return false;
	}
	return true;
}
