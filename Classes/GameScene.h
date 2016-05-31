#include"cocos2d.h"
#include"GameLayer.h"
#include "OperatorLayer.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;
//�޶�ʱ��
static int StayTime[] ={
	105, 105, 120,
};
class GameScene: public CCScene{
public:
	GameScene(void);
	~GameScene(void);

	virtual bool init();
	void update(float delta);
	//ʱ�ӵ���ʱ
	void setupInitTime(int num);
	//void setupHeroIcon(char* name);
	CC_SYNTHESIZE(GameLayer*, gameLayer, GameLayer);
	//void showRewardResult();
	CC_SYNTHESIZE(OperatorLayer*, operatorLayer, OperatorLayer);
	void StartGame(int _level, int _difficult);
	CREATE_FUNC(GameScene);
private:
	bool LimitInit();//��ʱ������ʼ��
	int TimeNum;//ʱ����Ŀ
	int	m_iGameMinute;//��
	int	m_iGameSecond;//��
	int currentLevel;//��ǰ�ؿ�
	int m_iMapNum;//��ͼnum
	float	m_fHeroLocateX;//heroposx
	float	m_fHeroLocateY;
	CCSprite* m_pLimitBoard;//��������
	CCSprite* m_pgameBoard;//��������
	int m_iLimitTimeNeed;//�����ؿ�ʱ��
	int gameTime;
	bool GameStart;//��Ϸ��ʼ
	int userbloodnum;
	void rewardresult(float delta);
	void showTime(float delta);
};