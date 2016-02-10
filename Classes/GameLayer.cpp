#include"GameLayer.h"
#include "Shana.h"
#include "Ogre.h"
#include "GlobalCtrl.h"

GameLayer::GameLayer() :
	tilemap( nullptr )
{
	GlobalCtrl::getInstance();
}
GameLayer::~GameLayer(void){};

bool GameLayer::init(){
	if(!CCLayer::init())
		return false;
	this->initTileMap();
	this->addShana();
	this->addOgre();
	//����updata�¼�
	this->scheduleUpdate();
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
	//       // ��ȡ������״����ʼ��  
	//       float x = ((CCString*)dict->objectForKey("x"))->floatValue();  
	//       float y = ((CCString*)dict->objectForKey("y"))->floatValue(); 
	//	printf("%d:  %f %f\n", count, x, y);
	//	count++;
	//}
	Shana* shana = Shana::create();
	shana->setPosition( CCPoint(
		((CCString*) obj->objectForKey("x"))->floatValue(), 
		((CCString*) obj->objectForKey("y"))->floatValue()+shana->getSprite()->getContentSize().height/2 ));
	this->addChild( shana );
	GlobalCtrl::getInstance()->shana = shana;

	
}

void GameLayer::addOgre() {
	CCTMXTiledMap* map = GlobalCtrl::getInstance()->tilemap;
	CCTMXObjectGroup*  objectGroup = map->objectGroupNamed( "Role");
	CCDictionary* obj = objectGroup->objectNamed( "shana" );
	Ogre* ogre = Ogre::create();
	this->setPosition( CCPoint(
		((CCString*) obj->objectForKey("x"))->floatValue() + 200, 
		((CCString*) obj->objectForKey("y"))->floatValue() + 200));
	this->addChild( ogre );
	//GlobalCtrl::getInstance()->ogre = ogre;
	
	CCSize visibleSize = CCEGLView::sharedOpenGLView()->getVisibleSize();
	monster1=Monster::create();   
	//monster1->InitMonsterSprite("monster.png","xue_back.png","xue_fore.png");  
	//monster1->InitMonsterSprite("monster.png");  
	monster1->InitMonsterSprite("monster.png","xue_back.png","xue_fore.png");  
	monster1->setPosition(ccp(visibleSize.width-50,visibleSize.height/2));
	this->addChild(monster1);
	//GlobalCtrl::getInstance()->tilemap->addChild(monster1);//��������ӵ���ͼ�У���������������ͼ�ƶ�  
	monster1->StartListen(GlobalCtrl::getInstance()->shana ,GlobalCtrl::getInstance()->tilemap);//�ǳ���Ҫ��������һ���õ���  
}


void GameLayer::update(float delta)
{
	if(GlobalCtrl::getInstance()->shana->getCanMutilAttack())//Ӣ�����ڹ���
	{
	  CCLOG("update enter hurt 3");
	  if(!monster1->Isdead)//���ﻹû��
	  {
		CCLOG("update enter hurt 2");
	    if(abs(GlobalCtrl::getInstance()->shana->getPositionY()-monster1->getPositionY())<30)//�����Ӣ��Ӧ����һ������ˮƽ�߶��ϣ���������Ч
	    {
			
			CCLOG("update enter hurt 1");
         //����Ƿ���ײ������
	      if (this->isRectCollision(CCRectMake(GlobalCtrl::getInstance()->shana->getPositionX(), GlobalCtrl::getInstance()->shana->getPositionY(),GlobalCtrl::getInstance()->shana->getContentSize().width-70, GlobalCtrl::getInstance()->shana->getContentSize().height-30),
			  CCRectMake(monster1->getPositionX(), monster1->getPositionY(), monster1->GetSprite()->getContentSize().width-30,monster1->GetSprite()->getContentSize().height-20))) 
	         {
				 CCLOG("update enter hurt ");
		        monster1->HurtAnimation("monster_hurt",2,monster1->MonsterDirecton);//����
	         }
	     }
	  }
	}

}
///��ײ���
bool GameLayer::isRectCollision (CCRect rect1, CCRect rect2)
{
	float x1 = rect1.origin.x;//����1���ĵ�ĺ�����
	float y1 = rect1.origin.y;//����1���ĵ��������
	float w1 = rect1.size.width;//����1�Ŀ��
	float h1 = rect1.size.height;//����1�ĸ߶�
	float x2 = rect2.origin.x;
	float y2 = rect2.origin.y;
	float w2 = rect2.size.width;
	float h2 = rect2.size.height;

	if (x1+w1*0.5<x2-w2*0.5)  
		return false;//����1�ھ���2�󷽣���������ײ
	else if (x1-w1*0.5>x2+w2*0.5)
		return false;//����1�ھ���2�ҷ�����������ײ
	else if (y1+h1*0.5<y2-h2*0.5)
		return false;//����1�ھ���2�·�����������ײ
	else if (y1-h1*0.5>y2+h2*0.5)
		return false;//����1�ھ���2�Ϸ�����������ײ

	return true;
}
