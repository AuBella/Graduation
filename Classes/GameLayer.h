#include"cocos2d.h"
#include "Monster.h"
#include"Ogre.h"
#include "Shana.h"
//#include "Ogre.h"
#include "GlobalCtrl.h"

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
	//virtual void update(float delta);
	//������ײ���
	bool isRectCollision (CCRect rect1, CCRect rect2);
    //���Ŀ��֪ͨ�۲���֮����õ��¼�  
    void ObserverFunction(CCObject * object);  
	Monster* monster1;
	Ogre* monster2;
	CREATE_FUNC(GameLayer);
};