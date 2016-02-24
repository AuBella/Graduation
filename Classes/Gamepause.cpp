#include "Gamepause.h"
#include "GameScene.h"
//����һ��CCrenderTexture 
//�൱��һ���������е���Ϸ�Ľ�ͼ��Ϊ�����ͣ�Ի���ı��� 
//�����Ϳ��������ǶԻ�������Ϸ����֮�ϣ�һ����Ϸ���ж���������д�ġ�
CCScene* Gamepause::scene(CCRenderTexture* sqr)
{

    CCScene *scene = CCScene::create();
    Gamepause *layer = Gamepause::create();
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
	CCSprite *back_small_spr = CCSprite::create("back_pause.png");
	back_small_spr->setPosition(ccp(visibleSize.width/2,visibleSize.height/2)); //����λ��,������������λ�á�
	scene->addChild(back_small_spr);


    return scene;
}

bool Gamepause::init()
{

    if ( !CCLayer::init() )
    {
        return false;
    }
	//�õ����ڵĴ�С
	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	//ԭ������
	CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

	//������Ϸ��ť
	CCMenuItemImage *pContinueItem = CCMenuItemImage::create(
		"pause_continue.png",
		"pause_continue.png",
		this,
		menu_selector(Gamepause::menuContinueCallback));

	pContinueItem->setPosition(ccp( visibleSize.width/2 ,visibleSize.height/2+30));

	//���¿�ʼ��Ϸ��ť
	CCMenuItemImage *pRestartItem = CCMenuItemImage::create(
		"pause_restart.png",
		"pause_restart.png",
		this,
		menu_selector(Gamepause::menuRestart));

	pRestartItem->setPosition(ccp( visibleSize.width/2 ,visibleSize.height/2-20));

	//��������
	CCMenuItemImage *pLoginItem = CCMenuItemImage::create(
		"pause_login.png",
		"pause_login.png",
		this,
		menu_selector(Gamepause::menuLogin));

	pLoginItem->setPosition(ccp( visibleSize.width/2 ,visibleSize.height/2-70));


	// create menu, it's an autorelease object
	CCMenu* pMenu = CCMenu::create(pContinueItem,pRestartItem,pLoginItem,NULL);
	pMenu->setPosition(CCPointZero);
	this->addChild(pMenu, 2);



	


    return true;
}
void Gamepause::menuContinueCallback(CCObject* pSender)
{
	CCDirector::sharedDirector()->popScene();

}
//���¿�ʼ��Ϸ
void  Gamepause::menuRestart(CCObject* pSender)
{
	CCDirector::sharedDirector()->replaceScene(GameScene::create());
}
//��������
void  Gamepause::menuLogin(CCObject* pSender)
{

}






