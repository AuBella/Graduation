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
	
    void addLabel();
	
	//每帧更新时调用的事件
	//virtual void update(float delta);
	//矩形碰撞检测
	bool isRectCollision (CCRect rect1, CCRect rect2);
    //添加目标通知观察者之后调用的事件  
    void ObserverFunction(CCObject * object);  
	//Monster* monster1;
	Ogre* ogre;
	Shana* shana;
	CCLabelTTF* label;
	CREATE_FUNC(GameLayer);
};