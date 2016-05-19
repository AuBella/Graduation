#include"RewardLayer.h"
#include "GameScene.h"
RewardLayer::RewardLayer(){}

RewardLayer::~RewardLayer(){};
CCScene* RewardLayer::scene(CCRenderTexture* sqr, int num, int redBlood){
    CCScene *scene = CCScene::create();
    RewardLayer *layer = RewardLayer::create();
		scene->addChild(layer,1);//把游戏层放上面，我们还要在这上面放按钮
	//增加部分：使用Game界面中截图的sqr纹理图片创建Sprite
	//并将Sprite添加到GamePause场景层中
	//得到窗口的大小
	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	CCSprite *back_spr = CCSprite::createWithTexture(sqr->getSprite()->getTexture());  
	back_spr->setPosition(ccp(visibleSize.width/2,visibleSize.height/2)); //放置位置,这个相对于中心位置。
	back_spr->setFlipY(true);            //翻转，因为UI坐标和OpenGL坐标不同
	back_spr->setColor(cocos2d::ccGRAY); //图片颜色变灰色
	scene->addChild(back_spr);


	//添加游戏暂停背景小图，用来放按钮
	CCSprite *back_small_spr = CCSprite::create("Common/rewardresult/bg.jpg");
	back_small_spr->setScale(0.1);
	back_small_spr->setPosition(ccp(visibleSize.width/2,visibleSize.height/2)); //放置位置,这个相对于中心位置。
	CCSprite* winBg = CCSprite::create("Common/rewardresult/win.png");
	//胜利位置
	float winPosHeight = back_small_spr->getContentSize().height - winBg->getContentSize().height* 2;
	winBg->setPosition(ccp(back_small_spr->getContentSize().width /2, winPosHeight));
	back_small_spr->addChild(winBg);
	//星星位置
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
	
	//计算星星数目，1~3星
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
