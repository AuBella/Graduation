#include"GameLayer.h"

GameLayer::GameLayer() :
	tilemap( NULL )
{
	GlobalCtrl::getInstance();
	ogreArray = GlobalCtrl::getInstance() ->pArray;
	//ogreArray = CCArray::createWithCapacity(100);
}
GameLayer::~GameLayer(void){
	CCNotificationCenter::sharedNotificationCenter()->removeObserver(this,"Attack");
};

bool GameLayer::init(){
	if(!CCLayer::init())
		return false;
	this->initTileMap();
	this->addShana();
	this->addOgre();
    CCNotificationCenter::sharedNotificationCenter()->addObserver(this,callfuncO_selector(GameLayer::ObserverFunction),"Attack",NULL);  
	return true;
};

//地图
void GameLayer::initTileMap(){
	tilemap = CCTMXTiledMap::create("tilemap.tmx");
	CCObject *pObject = NULL;
	CCARRAY_FOREACH(tilemap->getChildren(), pObject){
		CCTMXLayer *child = (CCTMXLayer*)pObject;
		child->getTexture()->setAliasTexParameters();
	}
	GlobalCtrl::getInstance()->tilemap = tilemap;
	this->addChild(tilemap, -10);
};
//观察者模式
void GameLayer::ObserverFunction(CCObject * object){
	int num = (int)object;
	bool flag = false;
	for (unsigned int i = 0; i <ogreArray->count(); ++i) {
    Ogre* pObj=(Ogre*)ogreArray->objectAtIndex(i);

	if(abs(shana->getPositionY()-pObj->getPositionY())<30){
		if(shana->getHitBox().intersectsRect(CCRectMake(pObj->getPositionX() - pObj->GetSprite()->getContentSize().width / 2, 
														pObj->getPositionY() - pObj->GetSprite()->getContentSize().height /2,
														pObj->GetSprite()->getContentSize().width, 
														pObj->GetSprite()->getContentSize().height)
														)
											){
			pObj->isHurt = true;
			pObj->isAttack = true;
			pObj->HurtAnimation(num);
			flag = true;
	    }
	}
	}
}

void GameLayer::output(){
	CCLOG("--------------->>>>>>>>>>>>>> %d", ogreArray->count());
}
//英雄
void GameLayer::addShana() {
	CCTMXTiledMap* map = GlobalCtrl::getInstance()->tilemap;
	CCTMXObjectGroup*  objectGroup = map->objectGroupNamed( "Role");
	CCDictionary* obj = objectGroup->objectNamed( "shana" );

	shana = Shana::create();
	shana->setPosition( CCPoint(
		((CCString*) obj->objectForKey("x"))->floatValue() - 100, 
		((CCString*) obj->objectForKey("y"))->floatValue()+shana->getSprite()->getContentSize().height/2 ));
	this->addChild( shana );
	GlobalCtrl::getInstance()->shana = shana;
	shana->StartListen();
}
//怪物
void GameLayer::addOgre() {
	CCTMXTiledMap* map = GlobalCtrl::getInstance()->tilemap;
	CCTMXObjectGroup*  objectGroup = map->objectGroupNamed( "Role");
	CCDictionary* obj = objectGroup->objectNamed( "shana" );
	for(int i = 0; i < 2; ++i){
		ogre = Ogre::create();
		ogreArray->addObject(ogre);
		this->addChild( ogre );
		ogre->setPosition(shana->getPositionX() + 200 * i, i * 10 + shana->getPositionY());
		CCSize visibleSize = CCEGLView::sharedOpenGLView()->getVisibleSize();
		ogre -> StartListen();
	}
}