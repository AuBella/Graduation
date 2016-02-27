#include"GameLayer.h"

GameLayer::GameLayer() :
	tilemap( NULL )
{
	GlobalCtrl::getInstance();
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

void GameLayer::ObserverFunction(CCObject * object){
	bool flag = false;
	if(abs(shana->getPositionY()-ogre->getPositionY())<30){
		if(shana->getHitBox().intersectsRect(CCRectMake(ogre->getPositionX() - ogre->GetSprite()->getContentSize().width / 2, 
														ogre->getPositionY() - ogre->GetSprite()->getContentSize().height /2,
														ogre->GetSprite()->getContentSize().width, 
														ogre->GetSprite()->getContentSize().height)
														)
											){
			ogre->isHurt = true;
			ogre->isAttack = true;
			ogre->HurtAnimation();
			flag = true;
	    }
	}
}  

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

void GameLayer::addOgre() {
	CCTMXTiledMap* map = GlobalCtrl::getInstance()->tilemap;
	CCTMXObjectGroup*  objectGroup = map->objectGroupNamed( "Role");
	CCDictionary* obj = objectGroup->objectNamed( "shana" );
	ogre = Ogre::create();
	this->addChild( ogre );
	ogre->setPosition(shana->getPositionX() + 200, shana->getPositionY());
	CCSize visibleSize = CCEGLView::sharedOpenGLView()->getVisibleSize();
	ogre -> StartListen();
}