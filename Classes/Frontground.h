#ifndef _GAME_FRONTGROUND_H_
#define _GAME_FRONTGROUND_H_

#include "cocos2d.h"
#include "CSArmature.h"

struct MapObject
{
	int					unKind;
	float				x;
	float				y;
	float				w;
	float				h;
	float				arg1;
	float				arg2;
	float				arg3;
	float				arg4;
	int					argi1;
	int					argi2;
	int					argi3;
	int					iToward;
	bool				bActive;
	bool				argb;
	bool				argb1;
	bool				argb2;
	bool				argb3;
	std::string			sPath;
	cocos2d::CCSprite*	pSprite;
	cocos2d::CCSprite*	pSprite1;
	cs::Armature*		pArmature;
	bool				bCheck;

	MapObject()
	{
		iToward = 1;
		argi3	= -1;
		bActive = false;
		argb	= false;
		argb1	= false;
		argb2	= false;
		pSprite = NULL;
		pArmature = NULL;
		pSprite1= NULL;
		sPath	= "";
		bCheck	= false;
	}

	~MapObject()
	{
		//if ( pSprite )
		//	if ( pSprite->getParent() )
		//		pSprite->removeFromParent();
		//if ( pSprite1 )
		//	if ( pSprite1->getParent() )
		//		pSprite1->removeFromParent();
	}
};
struct MonsterObject
{
	float			x;
	float			y;
	float			dist;
	int				kind;
	int				time;
	int				num;
	int				range;
	int				timemax;
	int				timemin;
	int				index;
};

class CFrontground : public cocos2d::CCLayer
{
public:
	CFrontground();
	~CFrontground();
	static CFrontground* Create(int _unLevel);
	virtual bool init();
	void ChangeMap(const char* _path);
	int GetMapNums();

	cocos2d::CCArray* GetCrashRectArray();
	cocos2d::CCArray* GetCrashTriaArray();
	cocos2d::CCTMXTiledMap* GetTileMap();
	MapObject* GetMapObjects();
	int GetObjectNum();

	std::vector<MonsterObject*>	m_vecObjectArray;
	cocos2d::CCArray*		m_pMonsterArray;
	MapObject*				m_pObjectArray;
	int						m_unObjectArrayNum;
protected:
	cocos2d::CCSize			m_cSize;
	int						m_unLevel;
	cocos2d::CCTMXTiledMap* m_pTileMap;
	//common::CTiledLayer*	m_pTileMap;
	cocos2d::CCArray*		m_pCrashRectArray;
	cocos2d::CCArray*		m_pCrashTriaArray;
private:
	void GetMapInfo();
};

#endif
