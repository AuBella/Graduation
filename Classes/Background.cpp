#include "Background.h"
#include "baseRes.h"

using namespace cocos2d;

CBackground::CBackground()
{
	
}

CBackground::~CBackground()
{

}

CBackground* CBackground::Create(int _unLevel)
{
	CBackground* pBackgroud = new CBackground;
	pBackgroud->m_unLevel = _unLevel;
	pBackgroud->init();
	pBackgroud->autorelease();

	return pBackgroud;
}

bool CBackground::init()
{
	if ( m_unLevel < 0 )
		m_pTileMap = CCTMXTiledMap::create("Tile/b1levmg.tmx");
	else
		m_pTileMap = CCTMXTiledMap::create(g_sMGPath[m_unLevel].c_str());
	//SetScale(m_pTileMap);
	addChild(m_pTileMap);
	return true;
}

cocos2d::CCTMXTiledMap* CBackground::GetTileMap()
{
	return m_pTileMap;
}
