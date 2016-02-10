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

	
	//ÿ֡����ʱ���õ��¼�
	virtual void update(float delta);
	//������ײ���
	bool isRectCollision (CCRect rect1, CCRect rect2);
	Monster* monster1;
	CREATE_FUNC(GameLayer);
};