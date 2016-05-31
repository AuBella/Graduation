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
	void showRewardResult();
	CC_SYNTHESIZE(OperatorLayer*, operatorLayer, OperatorLayer);
	void StartGame(int _level, int _difficult);
	CREATE_FUNC(GameScene);
private:
	CCLabelTTF* pLabel;
	int TimeNum;
	CCSprite* heroIcon;
	int currentLevel;
	void rewardresult(float delta);
};