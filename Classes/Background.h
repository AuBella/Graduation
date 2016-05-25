#include "cocos2d.h"

class CBackground : public cocos2d::CCLayer
{
public:
	CBackground();
	~CBackground();
	static CBackground* Create(int _unLevel);
	virtual bool init();
	cocos2d::CCTMXTiledMap* GetTileMap();

protected:
	int					m_unLevel;
	cocos2d::CCTMXTiledMap* m_pTileMap;
};
