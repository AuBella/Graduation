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
	
	//ÿ֡����ʱ���õ��¼�
	//virtual void update(float delta);
	//������ײ���
	bool isRectCollision (CCRect rect1, CCRect rect2);
    //���Ŀ��֪ͨ�۲���֮����õ��¼�  
    void ObserverFunction(CCObject * object);  
	//Monster* monster1;
	Ogre* ogre;
	Shana* shana;
	CCLabelTTF* label;
	CREATE_FUNC(GameLayer);
};