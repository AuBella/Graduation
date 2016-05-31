#include"cocos2d.h"
#include"GameLayer.h"
#include "OperatorLayer.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;
//限定时间
static int StayTime[] ={
	105, 105, 120,
};
class GameScene: public CCScene{
public:
	GameScene(void);
	~GameScene(void);

	virtual bool init();
	void update(float delta);
	//时钟倒计时
	void setupInitTime(int num);
	//void setupHeroIcon(char* name);
	CC_SYNTHESIZE(GameLayer*, gameLayer, GameLayer);
	//void showRewardResult();
	CC_SYNTHESIZE(OperatorLayer*, operatorLayer, OperatorLayer);
	void StartGame(int _level, int _difficult);
	CREATE_FUNC(GameScene);
private:
	bool LimitInit();//计时计数初始化
	int TimeNum;//时间数目
	int	m_iGameMinute;//分
	int	m_iGameSecond;//秒
	int currentLevel;//当前关卡
	int m_iMapNum;//地图num
	float	m_fHeroLocateX;//heroposx
	float	m_fHeroLocateY;
	CCSprite* m_pLimitBoard;//计数背景
	CCSprite* m_pgameBoard;//计数背景
	int m_iLimitTimeNeed;//单个关卡时间
	int gameTime;
	bool GameStart;//游戏开始
	int userbloodnum;
	void rewardresult(float delta);
	void showTime(float delta);
};