#include"GameLayer.h"
#include"baseRes.h"
#include"RewardLayer.h"

GameLayer::GameLayer() :
	tilemap( NULL ){
	GlobalCtrl::getInstance();
	killnum = 0;
	ogreArray = GlobalCtrl::getInstance() ->pArray;
	rolehight = 0;
	currentLevel=0;
}
GameLayer::~GameLayer(void){
	CCNotificationCenter::sharedNotificationCenter()->removeObserver(this,"Attack");
	ogreArray->removeAllObjects();
};

bool GameLayer::init(){
	if(!CCLayer::init())
		return false;
	return true;
};

void GameLayer::StartGameLevel(int level, int difficut){
	this->initTileMap(level);
	currentLevel = level;
	this->addShana();
	schedule(schedule_selector(GameLayer::updateMonster),5);
    CCNotificationCenter::sharedNotificationCenter()->addObserver(this,callfuncO_selector(GameLayer::ObserverFunction),"Attack",NULL);
}

void GameLayer::updateMonster(float delta){
	this->addOgre();
}
//地图
void GameLayer::initTileMap(int _unLevel){
	char buffer[255];
	sprintf(buffer, "Tile/%d_0.tmx", 0);
	//sprintf(buffer, "Tile/%d_0.tmx", _unLevel);
	tilemap = CCTMXTiledMap::create(buffer);
	CCObject *pObject = NULL;
	CCARRAY_FOREACH(tilemap->getChildren(), pObject){
		CCTMXLayer *child = (CCTMXLayer*)pObject;
		child->getTexture()->setAliasTexParameters();
	}
	GlobalCtrl::getInstance()->tilemap = tilemap;
	this->addChild(tilemap);
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
															pObj->GetSprite()->getContentSize().height))){
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
	m_pMonsterArray = map->objectGroupNamed("pengzhuang")->getObjects();
	m_pMonsterArray->retain();
	CCDictionary* obj = (CCDictionary*)m_pMonsterArray->objectAtIndex(0);
	shana = Shana::create();
	rolehight =((CCString*)obj->objectForKey("height"))->floatValue() + shana->getSprite()->getContentSize().height/2;
	shana->setPosition( CCPoint(100, rolehight));
	CCLOG("=================%d", rolehight);
	this->addChild( shana );
	GlobalCtrl::getInstance()->shana = shana;
	shana->StartListen();
}

int GameLayer::getkillnum(){
	return killnum;
}
//怪物
void GameLayer::addOgre() {
	CCObject *pObject = NULL;
	CCARRAY_FOREACH(ogreArray, pObject){
		Ogre *child = (Ogre*)pObject;
		if(child->isDead){
			killnum++;
			ogreArray->removeObject(pObject);
		}
	}
	CCTMXTiledMap* map = GlobalCtrl::getInstance()->tilemap;
	m_pMonsterArray = map->objectGroupNamed("zuobiao2")->getObjects();
	m_pMonsterArray->retain();
	for(int i = 0; i < 5 && ogreArray->count() <= 10; ++i){
		int tempLevelnum = 3;
		if(currentLevel == 3)
			tempLevelnum = 4;
		CCDictionary* obj = (CCDictionary*)m_pMonsterArray->objectAtIndex(rand()%tempLevelnum);
		if(abs(((CCString*)obj->objectForKey("x"))->floatValue() - shana->getPositionX()+ tilemap->getPositionX()) <= WINSIZE_W / 2){
			ogre = Ogre::create();
			ogreArray->addObject(ogre);
			this->addChild( ogre );
			ogre -> StartListen();
			ogre->setPosition(ccp(((CCString*)obj->objectForKey("x"))->floatValue(), rolehight));
			CCSize visibleSize = CCEGLView::sharedOpenGLView()->getVisibleSize();
		}
	}
}

int GameLayer::GetMapNums(){
	return tilemap->getMapSize().width*tilemap->getTileSize().width/800;
}
