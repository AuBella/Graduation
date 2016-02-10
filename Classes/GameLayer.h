#include"cocos2d.h"
#include "Monster.h"

USING_NS_CC;
//class GameLayer : public cocos2d::CCLayer{
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

	
	//每帧更新时调用的事件
	virtual void update(float delta);
	//矩形碰撞检测
	bool isRectCollision (CCRect rect1, CCRect rect2);
	Monster* monster1;
	CREATE_FUNC(GameLayer);
};