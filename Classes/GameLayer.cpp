#include"GameLayer.h"
#include"baseRes.h"
#include"RewardLayer.h"
#include"CHero.h"
#include"Common.h"
#include"CommonBloodBar.h"

CHero* hero;
GameLayer::GameLayer() :
	tilemap( NULL ){
	GlobalCtrl::getInstance();
	killnum = 0;
	ogreArray = GlobalCtrl::getInstance() ->pArray;
	ogreArray->retain();
	rolehight = 0;
	startGamevisible = true;
	currentLevel=0;
	hero = NULL;
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
	if(level == 0 || level == 2)
		startGamevisible = false;
	if(level!=0 && level != 2){
		this->addOgre();
	}
	int temptime = 1;
	if(level == 1){
		temptime = 2;
	}
	else if(level = 2){
		temptime = 2;
	}

	schedule(schedule_selector(GameLayer::updateMonster),temptime);
    CCNotificationCenter::sharedNotificationCenter()->addObserver(this,callfuncO_selector(GameLayer::ObserverFunction),"Attack",NULL);
}

void GameLayer::updateMonster(float delta){
	if(startGamevisible)
		this->addOgre();
}
//地图
void GameLayer::initTileMap(int _unLevel){
	char buffer[255];
	sprintf(buffer, "Tile/%d_0.tmx", _unLevel);
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
				if(currentLevel == 1)
					hero->HurtAnimation(num);
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

	if (currentLevel == 1 ){//保护关
		cocos2d::CCArray* viparray = map->objectGroupNamed("zuobiao2")->getObjects();
		viparray->retain();
		CCDictionary* objleft = (CCDictionary*)viparray->objectAtIndex(1);
		CCDictionary* objright = (CCDictionary*)viparray->objectAtIndex(3);
		int pParticle1 = ((CCString*)objleft->objectForKey("x"))->floatValue();
		int pParticle2 = ((CCString*)objright->objectForKey("x"))->floatValue();
		int vipposx = ( pParticle1+pParticle2)/2;
		CCSprite* pSprite = common::CreateAnimation("Animation/vip/1.png", ccp(vipposx,((CCString*)obj->objectForKey("height"))->floatValue()), 
			ccp(0.5f, 0.5f), "Animation/vip/", 6, CCRect(0,0,166,59), true);
		this->addChild(pSprite);
		hero = CHero::create();
		m_pVIP = hero->CreateVIP();
		this->addChild(hero);
		GlobalCtrl::getInstance()->hero = hero;
		m_pVIP->setPosition( ccp(vipposx,((CCString*)obj->objectForKey("height"))->floatValue()) );
		this->addChild(m_pVIP);
	}
}

int GameLayer::getkillnum(){
	return killnum;
}
void GameLayer::startMonsterlist(bool Visible){//第一关和第三关要用
	startGamevisible = true;
	/*if(currentLevel == 0 || currentLevel == 2){
		CCObject *pObject = NULL;
		CCARRAY_FOREACH(ogreArray, pObject){
			Ogre *child = (Ogre*)pObject;
			child -> StartListen();
		}
	}*/
}

//怪物
void GameLayer::addOgre() {
	CCObject *pObject = NULL;
	CCARRAY_FOREACH(ogreArray, pObject){
		Ogre *child = (Ogre*)pObject;
		if(child->isDead){
			killnum++;
			//限定怪物总数
			if(currentLevel != 0 || currentLevel != 2)
				ogreArray->removeObject(pObject);
		}
	}
	CCTMXTiledMap* map = GlobalCtrl::getInstance()->tilemap;
	if(currentLevel == 0){
		m_pMonsterArray = map->objectGroupNamed("zuobiao1")->getObjects();
	}
	else{
		m_pMonsterArray = map->objectGroupNamed("zuobiao2")->getObjects();
	}
	m_pMonsterArray->retain();
	for(int i = 0; i < rand() % 5 + 1 && ogreArray->count() <= (5 -currentLevel) * 10; ++i){
		int tempLevelnum = 3;
		if(currentLevel == 0 || currentLevel == 1)
			tempLevelnum = 4;
		CCDictionary* obj = (CCDictionary*)m_pMonsterArray->objectAtIndex(rand()%tempLevelnum);
		//if(currentLevel != 0){
			if(abs(((CCString*)obj->objectForKey("x"))->floatValue() - shana->getPositionX()+ tilemap->getPositionX()) <= WINSIZE_W / 2){
				ogre = Ogre::create();
				ogreArray->addObject(ogre);
				this->addChild( ogre );
				//if(currentLevel != 2)//生存模式有计时
					ogre -> StartListen();
				ogre->setPosition(ccp(((CCString*)obj->objectForKey("x"))->floatValue(), rolehight));
				CCSize visibleSize = CCEGLView::sharedOpenGLView()->getVisibleSize();
			}
		/*}
		else{*/
		if(currentLevel == 0){
			ogre = Ogre::create();
			ogreArray->addObject(ogre);
			this->addChild( ogre );
			ogre->StartListen();
			ogre->setPosition(ccp(shana->getPositionX()+ tilemap->getPositionX() + (rand() % 150 + 10), rolehight));
			CCSize visibleSize = CCEGLView::sharedOpenGLView()->getVisibleSize();
		}
	}
}

int GameLayer::GetMapNums(){
	return tilemap->getMapSize().width*tilemap->getTileSize().width/800;
}
