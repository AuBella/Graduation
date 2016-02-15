#include"GameLayer.h"

GameLayer::GameLayer() :
	tilemap( nullptr )
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
	//启动updata事件
	//this->scheduleUpdate();
	//注册Message，如果接收到了，执行ObserverFunction  
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

void GameLayer::ObserverFunction(CCObject * object)  
{  
    CCLOG("SecondLayer Receive num=%d",(int)object); 
	Shana* shana = GlobalCtrl::getInstance()->shana;
	//if(shana->isAttack){
	  CCLOG("update enter hurt 3");
	  //if(!monster1->Isdead)//怪物还没死
	  //{
		//CCLOG("update enter hurt 2");
	    if(abs(GlobalCtrl::getInstance()->shana->getPositionY()-monster2->getPositionY())<30)//怪物和英雄应该在一个差不多的水平高度上，攻击才有效
	    {
			
			CCLOG("update enter hurt 1");
         //检测是否碰撞到怪物
	      if (this->isRectCollision(CCRectMake(GlobalCtrl::getInstance()->shana->getPositionX(), GlobalCtrl::getInstance()->shana->getPositionY(),GlobalCtrl::getInstance()->shana->getContentSize().width-70, GlobalCtrl::getInstance()->shana->getContentSize().height-30),
			  //CCRectMake(monster1->getPositionX(), monster1->getPositionY(), monster1->GetSprite()->getContentSize().width-30,monster1->GetSprite()->getContentSize().height-20))) 
									CCRectMake(monster2->getPositionX(), monster2->getPositionY(), monster2->GetSprite()->getContentSize().width + 100,monster2->GetSprite()->getContentSize().height+100)))    
			{
				 CCLOG("update enter hurt ");
		        monster1->HurtAnimation("monster_hurt",2,monster1->MonsterDirecton);//受伤
				monster2->isHurt = true;
				monster2->HurtAnimation();
				//GlobalCtrl::getInstance()->shana1->runHurtAnimation();
	         }
	     //}
	  //}
	}
}  

void GameLayer::addShana() {
	CCTMXTiledMap* map = GlobalCtrl::getInstance()->tilemap;
	CCTMXObjectGroup*  objectGroup = map->objectGroupNamed( "Role");
	CCDictionary* obj = objectGroup->objectNamed( "shana" );
	//CCArray* array = objectGroup->getObjects();  
	//   CCDictionary* dict;  
	//   CCObject* pObj = NULL;  
	//int  count = 0;
	//CCARRAY_FOREACH(array, pObj){  
	//       dict = (CCDictionary*)pObj;  
	//       if (!dict)  
	//           continue;   
	//       // 读取所有形状的起始点  
	//       float x = ((CCString*)dict->objectForKey("x"))->floatValue();  
	//       float y = ((CCString*)dict->objectForKey("y"))->floatValue(); 
	//	printf("%d:  %f %f\n", count, x, y);
	//	count++;
	//}
	Shana* shana = Shana::create();
	shana->setPosition( CCPoint(
		((CCString*) obj->objectForKey("x"))->floatValue() - 100, 
		((CCString*) obj->objectForKey("y"))->floatValue()+shana->getSprite()->getContentSize().height/2 ));
	this->addChild( shana );
	GlobalCtrl::getInstance()->shana = shana;

	/*Shana* shana1 = Shana::create();
	shana1->setPosition( CCPoint(
		((CCString*) obj->objectForKey("x"))->floatValue() - 100, 
		((CCString*) obj->objectForKey("y"))->floatValue()+shana1->getSprite()->getContentSize().height/2 ));
	this->addChild( shana1 );

	GlobalCtrl::getInstance()->shana1 = shana1;*/

	
}

void GameLayer::addOgre() {
	CCTMXTiledMap* map = GlobalCtrl::getInstance()->tilemap;
	CCTMXObjectGroup*  objectGroup = map->objectGroupNamed( "Role");
	CCDictionary* obj = objectGroup->objectNamed( "shana" );
	Ogre* ogre = Ogre::create();
	/*this->setPosition( CCPoint(
		((CCString*) obj->objectForKey("x"))->floatValue() , 
		((CCString*) obj->objectForKey("y"))->floatValue() + 200));*/
	this->addChild( ogre );
	Shana* shana = GlobalCtrl::getInstance()->shana;
	ogre->setPosition(shana->getPositionX() + 200, shana->getPositionY());
	//GlobalCtrl::getInstance()->ogre = ogre;
	
	CCSize visibleSize = CCEGLView::sharedOpenGLView()->getVisibleSize();
	monster2 = ogre;
	monster2->StartListen();
	monster1=Monster::create();   
	monster1->InitMonsterSprite("monster.png","xue_back.png","xue_fore.png");  
	//monster1->InitMonsterSprite("monster.png");  
	//monster1->InitMonsterSprite("monster.png","xue_back.png","xue_fore.png");  
	monster1->setPosition(ccp(visibleSize.width-50,visibleSize.height/2));
	this->addChild(monster1);
	//GlobalCtrl::getInstance()->tilemap->addChild(monster1);//将怪物添加到地图中，这样怪物才能随地图移动  
	monster1->StartListen(GlobalCtrl::getInstance()->shana ,GlobalCtrl::getInstance()->tilemap);//非常重要，这是这一讲用到的  
}

//
//void GameLayer::update(float delta)
//{
//	//if(GlobalCtrl::getInstance()->shana->getCanMutilAttack())//英雄正在攻击
//	if(GlobalCtrl::getInstance()->shana->isHurt){
//	  //CCLOG("update enter hurt 3");
//	  //if(!monster1->Isdead)//怪物还没死
//	  //{
//		//CCLOG("update enter hurt 2");
//	    if(abs(GlobalCtrl::getInstance()->shana->getPositionY()-monster2->getPositionY())<30)//怪物和英雄应该在一个差不多的水平高度上，攻击才有效
//	    {
//			
//			//CCLOG("update enter hurt 1");
//         //检测是否碰撞到怪物
//	      if (this->isRectCollision(CCRectMake(GlobalCtrl::getInstance()->shana->getPositionX(), GlobalCtrl::getInstance()->shana->getPositionY(),GlobalCtrl::getInstance()->shana->getContentSize().width-70, GlobalCtrl::getInstance()->shana->getContentSize().height-30),
//			  //CCRectMake(monster1->getPositionX(), monster1->getPositionY(), monster1->GetSprite()->getContentSize().width-30,monster1->GetSprite()->getContentSize().height-20))) 
//									CCRectMake(monster2->getPositionX(), monster2->getPositionY(), monster2->GetSprite()->getContentSize().width + 100,monster2->GetSprite()->getContentSize().height+100)))    
//			{
//				 CCLOG("update enter hurt ");
//		        monster1->HurtAnimation("monster_hurt",2,monster1->MonsterDirecton);//受伤
//				
//		/*CCMenu* menu = GlobalCtrl::getInstance()->menu;
//		menu->setTouchEnabled(false);*/
//				monster2->HurtAnimation();
//				//GlobalCtrl::getInstance()->shana1->runHurtAnimation();
//	         }
//	     }
//	  //}
//	}
//
//}
///碰撞检测
bool GameLayer::isRectCollision (CCRect rect1, CCRect rect2)
{
	float x1 = rect1.origin.x;//矩形1中心点的横坐标
	float y1 = rect1.origin.y;//矩形1中心点的纵坐标
	float w1 = rect1.size.width;//矩形1的宽度
	float h1 = rect1.size.height;//矩形1的高度
	float x2 = rect2.origin.x;
	float y2 = rect2.origin.y;
	float w2 = rect2.size.width;
	float h2 = rect2.size.height;

	if (x1+w1*0.5<x2-w2*0.5)  
		return false;//矩形1在矩形2左方，两者无碰撞
	else if (x1-w1*0.5>x2+w2*0.5)
		return false;//矩形1在矩形2右方，两者无碰撞
	else if (y1+h1*0.5<y2-h2*0.5)
		return false;//矩形1在矩形2下方，两者无碰撞
	else if (y1-h1*0.5>y2+h2*0.5)
		return false;//矩形1在矩形2上方，两者无碰撞

	return true;
}
