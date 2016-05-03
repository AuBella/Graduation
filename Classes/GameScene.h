#include"cocos2d.h"
#include"GameLayer.h"
#include "OperatorLayer.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

class GameScene: public CCScene{
public:
	GameScene(void);
	~GameScene(void);

	virtual bool init();
	void update(float delta);
	// ±÷”µπº∆ ±
	void setupInitTime(int num);
	void setupHeroIcon(char* name);
	CC_SYNTHESIZE(GameLayer*, gameLayer, GameLayer);
	CC_SYNTHESIZE(OperatorLayer*, operatorLayer, OperatorLayer);
	CREATE_FUNC(GameScene);
private:
	CCLabelTTF* pLabel;
	int TimeNum;
};