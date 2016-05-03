#include"cocos2d.h"
#include"Ogre.h"
#include "Shana.h"
#include "GlobalCtrl.h"

USING_NS_CC;
class GameLayer:public CCLayer{
private:
	CCTMXTiledMap* tilemap;
	void addShana();
	void addOgre();
public:
	GameLayer(void);
	~GameLayer(void);
	void initTileMap();
	virtual bool init();
    void ObserverFunction(CCObject * object);
	Ogre* ogre;
	Shana* shana;
	CCArray* ogreArray;
	void output();
	CREATE_FUNC(GameLayer);
};