#include "Frontground.h"
#include "baseRes.h"
#include"GlobalCtrl.h"
//#include "GameControler.h"

using namespace cocos2d;

CFrontground::CFrontground()
{
	m_pObjectArray		= NULL;
	m_pMonsterArray		= NULL;
	m_pCrashRectArray	= NULL;
	m_pCrashTriaArray	= NULL;
	m_unObjectArrayNum	= 0;
}

CFrontground::~CFrontground()
{
	m_pCrashRectArray->release();
	m_pCrashTriaArray->release();
	if ( m_pMonsterArray )
		m_pMonsterArray->release();
	SAFEDELETEARRAY(m_pObjectArray);
	VECTORCLEAN(m_vecObjectArray, MonsterObject);
}

CFrontground* CFrontground::Create(int _unLevel)
{
	CFrontground* pBackgroud = new CFrontground;
	pBackgroud->m_unLevel = _unLevel;
	pBackgroud->init();
	pBackgroud->autorelease();

	return pBackgroud;
}

bool CFrontground::init(){
	//m_pTileMap			= common::CTiledLayer::create(g_sTilePath[m_unLevel].c_str());
	if ( m_unLevel < 0 )
		m_pTileMap = CCTMXTiledMap::create("Tile/yindao.tmx");
	else{
#ifdef Old_Map
		m_pTileMap	= CCTMXTiledMap::create(g_sTilePath[m_unLevel].c_str());
#else
		char buffer[255];
		sprintf(buffer, "Tile/%d_0.tmx", m_unLevel);
		m_pTileMap = CCTMXTiledMap::create(buffer);
#endif
	}
	////////////////////////
	//CCObject *pObject = NULL;
	//CCARRAY_FOREACH(m_pTileMap->getChildren(), pObject){
	//	CCTMXLayer *child = (CCTMXLayer*)pObject;
	//	child->getTexture()->setAliasTexParameters();
	//}
	//GlobalCtrl::getInstance()->tilemap = m_pTileMap;
	///////////////////////
	addChild(m_pTileMap);
	GetMapInfo();
	return true;
}

CCArray* CFrontground::GetCrashRectArray()
{
	return m_pCrashRectArray;
}

CCArray* CFrontground::GetCrashTriaArray()
{
	return m_pCrashTriaArray;
}

CCTMXTiledMap* CFrontground::GetTileMap()
{
	return m_pTileMap;
}

MapObject* CFrontground::GetMapObjects()
{
	return m_pObjectArray;
}

int CFrontground::GetObjectNum()
{
	return m_unObjectArrayNum;
}

void CFrontground::ChangeMap( const char* _path )
{
	CCNode* pNode = m_pTileMap->getParent();

	m_pTileMap->removeAllChildrenWithCleanup(false);
	m_pTileMap->removeFromParentAndCleanup(true);

	m_pTileMap = CCTMXTiledMap::create(_path);
	m_pTileMap->setPosition(ccp(0,0));
	pNode->addChild(m_pTileMap);
	GetMapInfo();
}

void CFrontground::GetMapInfo()
{
	if ( m_pCrashRectArray )
		m_pCrashRectArray->release();
	m_pCrashRectArray	= m_pTileMap->objectGroupNamed("pengzhuang")->getObjects();
	m_pCrashRectArray->retain();
	if ( m_pCrashTriaArray )
		m_pCrashTriaArray->release();
	m_pCrashTriaArray	= m_pTileMap->objectGroupNamed("zuobiao3")->getObjects();
	m_pCrashTriaArray->retain();
	if ( m_unLevel < 49 )
		m_pTileMap->reorderChild((CCSpriteBatchNode*)m_pTileMap->getChildren()->objectAtIndex(3),5);
	else if ( m_unLevel < 55 )
	{
		m_pTileMap->reorderChild((CCSpriteBatchNode*)m_pTileMap->getChildren()->objectAtIndex(1),0);
		m_pTileMap->reorderChild((CCSpriteBatchNode*)m_pTileMap->getChildren()->objectAtIndex(2),1);
		m_pTileMap->reorderChild((CCSpriteBatchNode*)m_pTileMap->getChildren()->objectAtIndex(3),1);
		m_pTileMap->reorderChild((CCSpriteBatchNode*)m_pTileMap->getChildren()->objectAtIndex(4),2);
		m_pTileMap->reorderChild((CCSpriteBatchNode*)m_pTileMap->getChildren()->objectAtIndex(5),2);
		m_pTileMap->reorderChild((CCSpriteBatchNode*)m_pTileMap->getChildren()->objectAtIndex(6),5);
		m_pTileMap->reorderChild((CCSpriteBatchNode*)m_pTileMap->getChildren()->objectAtIndex(7),5);
	}

	if ( m_pObjectArray )
	{
		delete[] m_pObjectArray;
		m_pObjectArray = NULL;
	}
	CCArray* pObjectArray = m_pTileMap->objectGroupNamed("zuobiao1")->getObjects();
	m_unObjectArrayNum = pObjectArray->count();
	if ( m_unObjectArrayNum )
	{
		m_pObjectArray = new MapObject[m_unObjectArrayNum];
		for ( int i = 0; i < m_unObjectArrayNum; i++ )
		{
			CCDictionary* pObject = (CCDictionary*)pObjectArray->objectAtIndex(i);
			int kind = pObject->valueForKey("id")->uintValue();
			m_pObjectArray[i].unKind	= kind;
			m_pObjectArray[i].x			= pObject->valueForKey("x")->floatValue();
			m_pObjectArray[i].y			= pObject->valueForKey("y")->floatValue();

			switch ( kind )
			{
			case 0:
				m_pObjectArray[i].iToward = pObject->valueForKey("type")->uintValue();
				m_pObjectArray[i].argi1 = pObject->valueForKey("index")->intValue();
				m_pObjectArray[i].argi2 = pObject->valueForKey("add")->intValue();
				m_pObjectArray[i].argi3 = pObject->valueForKey("num")->intValue();
				m_pObjectArray[i].w		= 170;
				m_pObjectArray[i].h		= 800;
				m_pObjectArray[i].argb	= false;
				m_pObjectArray[i].argb1	= false; 
				m_pObjectArray[i].bCheck= false;
				break;
			case 1:
				m_pObjectArray[i].sPath = g_sBoxPath[pObject->valueForKey("type")->uintValue()];
				m_pObjectArray[i].arg1	= 0;
				if ( m_unLevel < 0 )
					m_pObjectArray[i].argi3 = pObject->valueForKey("item")->intValue();
				break;
			case 2:
				m_pObjectArray[i].sPath = g_sStairPath[pObject->valueForKey("type")->uintValue()-1];
				m_pObjectArray[i].argi1 = pObject->valueForKey("type")->uintValue() - 1;
				m_pObjectArray[i].arg1	= m_pObjectArray[i].x;
				m_pObjectArray[i].arg2	= pObject->valueForKey("max")->floatValue();
				m_pObjectArray[i].arg3	= 2.0;
				m_pObjectArray[i].bCheck= true;
				break;
			case 3:
				m_pObjectArray[i].sPath = g_sStairPath[pObject->valueForKey("type")->uintValue()-1];
				m_pObjectArray[i].argi1 = pObject->valueForKey("type")->uintValue() - 1;
				m_pObjectArray[i].arg1	= m_pObjectArray[i].y;
				m_pObjectArray[i].arg2	= pObject->valueForKey("max")->floatValue();
				m_pObjectArray[i].arg3	= 2.0;
				m_pObjectArray[i].bCheck= true;
				break;
			case 4:
				m_pObjectArray[i].sPath = "Tile/a3.png";
				m_pObjectArray[i].argi1 = 0;
				m_pObjectArray[i].argb	= false;
				m_pObjectArray[i].bCheck= true;
				break;
			case 5:
				m_pObjectArray[i].sPath = "Tile/a4.png";
				m_pObjectArray[i].argi1 = 0;
				break;
			case 6:
				m_pObjectArray[i].sPath = g_sStairPath[pObject->valueForKey("type")->uintValue()-1];
				m_pObjectArray[i].argi1 = pObject->valueForKey("type")->uintValue() - 1;
				m_pObjectArray[i].arg1	= m_pObjectArray[i].x;
				m_pObjectArray[i].arg2	= pObject->valueForKey("to")->floatValue();
				m_pObjectArray[i].arg3	= 2.0;
				m_pObjectArray[i].bCheck= true;
				if ( m_pObjectArray[i].arg2 == 0.0 )
					m_pObjectArray[i].iToward = 1;
				else
					m_pObjectArray[i].iToward = -1;
				break;
			case 7:
				m_pObjectArray[i].argi1	= pObject->valueForKey("type")->intValue();
				m_pObjectArray[i].argi2	= 0;
				m_pObjectArray[i].arg1	= pObject->valueForKey("max")->floatValue();
				m_pObjectArray[i].arg2	= m_pObjectArray[i].y;
				break;
			case 8:
				m_pObjectArray[i].argi2	= 0;
				m_pObjectArray[i].argb	= false;
				break;
			case 9:
				m_pObjectArray[i].argi1 = pObject->valueForKey("type")->intValue();
				m_pObjectArray[i].argi2 = 0;
				m_pObjectArray[i].arg1  = 200;
				m_pObjectArray[i].argb  = true;
				m_pObjectArray[i].w		= 100;
				m_pObjectArray[i].h		= 40;
				m_pObjectArray[i].bCheck= true;
				break;
			case 10:
				m_pObjectArray[i].argi1 = pObject->valueForKey("type")->intValue();
				m_pObjectArray[i].argi2 = 249;
				m_pObjectArray[i].argb  = true;
				m_pObjectArray[i].w		= 500;
				m_pObjectArray[i].h		= 800;
				m_pObjectArray[i].bCheck= true;
				break;
			case 11:
				m_pObjectArray[i].argi1	= pObject->valueForKey("type")->intValue();
				m_pObjectArray[i].argi2	= pObject->valueForKey("max")->intValue();
				m_pObjectArray[i].argb  = false;
				m_pObjectArray[i].bCheck= true;
				switch ( m_pObjectArray[i].argi1 )
				{
				case 0:
					m_pObjectArray[i].w		= 130;
					m_pObjectArray[i].h		= 111;
					break;
				case 1:
					m_pObjectArray[i].w		= 344;
					m_pObjectArray[i].h		= 170;
					break;
				}
				break;
			case 12:
				m_pObjectArray[i].argi3 = 0;
				break;
			case 13:
				m_pObjectArray[i].arg1	= 0.0f;
				m_pObjectArray[i].argi1 = 0;
				m_pObjectArray[i].w		= 117;
				m_pObjectArray[i].h		= 63;
				m_pObjectArray[i].bCheck= true;
				break;
			case 14:
				m_pObjectArray[i].argb	= true;
				m_pObjectArray[i].w		= 49;
				m_pObjectArray[i].h		= 80;
				break;
			case 15:
				m_pObjectArray[i].argb	= true;
				m_pObjectArray[i].argi1	= pObject->valueForKey("index")->intValue();
				m_pObjectArray[i].w		= 20;
				m_pObjectArray[i].h		= 20;
				break;
			case 16:
				m_pObjectArray[i].argb	= true;
				m_pObjectArray[i].w		= 100;
				m_pObjectArray[i].h		= 200;
				m_pObjectArray[i].bCheck= true;
				break;
			case 17:
				m_pObjectArray[i].w		= 10;
				m_pObjectArray[i].h		= 10;
				break;
			case 18:
				m_pObjectArray[i].w		= 56;
				m_pObjectArray[i].h		= 42;
				break;
			case 19:
				m_pObjectArray[i].w		= pObject->valueForKey("width")->intValue();
				m_pObjectArray[i].h		= pObject->valueForKey("height")->intValue();
				break;
			}
			if ( m_pObjectArray[i].sPath != "" )
			{
				CCSprite* pSprite = new CCSprite;
				pSprite->initWithFile(m_pObjectArray[i].sPath.c_str());
				CCSize size = pSprite->getContentSize();
				m_pObjectArray[i].w = size.width;
				m_pObjectArray[i].h = size.height - 24;
				delete pSprite;
			}
		}
	}
	if ( m_pMonsterArray )
	{
		m_pMonsterArray->release();
		VECTORCLEAN(m_vecObjectArray, MonsterObject);
		m_vecObjectArray.clear();
	}
	m_pMonsterArray = m_pTileMap->objectGroupNamed("zuobiao2")->getObjects();
	m_pMonsterArray->retain();
	if ( m_pMonsterArray->count() )
	{
		//if ( CGameControler::GetGameControler()->m_iLevelType != 2 )
		{
			for ( unsigned int i = 0; i < m_pMonsterArray->count(); i++ )
			{
				CCDictionary* pObject = (CCDictionary*)m_pMonsterArray->objectAtIndex(i);
				int id = pObject->valueForKey("id")->uintValue()%100 - 1
					+ (pObject->valueForKey("id")->uintValue()/100-1)*25;
#ifdef GameTypeC
				if ( id == 4 || id == 6 )
					continue;
				if ( id != 5 && id != 8 )
					id = id%2;
#endif
				MonsterObject* pMonsterInfo = new MonsterObject;
				pMonsterInfo->kind	= id;
				pMonsterInfo->x		= pObject->valueForKey("x")->floatValue();
				pMonsterInfo->y		= pObject->valueForKey("y")->floatValue();
				pMonsterInfo->time	= pObject->valueForKey("time")->uintValue()*50;
				pMonsterInfo->num	= pObject->valueForKey("num")->intValue();
				pMonsterInfo->index = pObject->valueForKey("z")->intValue();
				if ( pMonsterInfo->kind == 4 )
				{
					pMonsterInfo->dist = pObject->valueForKey("dist")->floatValue();
				}
				if ( pMonsterInfo->num )
				{
					pMonsterInfo->range = pObject->valueForKey("range")->intValue();
					pMonsterInfo->timemax = pObject->valueForKey("timemax")->intValue();
					pMonsterInfo->timemin = pObject->valueForKey("timmin")->intValue();
				}
				else
					pMonsterInfo->range = 0;
				m_vecObjectArray.push_back(pMonsterInfo);
			}
		}
	}
}

int CFrontground::GetMapNums(){
	return m_pTileMap->getMapSize().width*m_pTileMap->getTileSize().width/800;
}
