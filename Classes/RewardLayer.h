#include"cocos2d.h"
USING_NS_CC;
#define d_fStarLocateX		500.0f
#define d_fStarLocateY		340.0f
#define d_fStarLocateX1		852.0f
#define d_fStarLocateY1		192.0f
#define d_fStarLocateX2		923.0f
#define d_fStarLocateY2		230.0f
#define d_fStarLocateX3		994.0f
#define d_fStarLocateY3		199.0f
class RewardLayer :public CCLayer{
public:
	RewardLayer();
	~RewardLayer();
	void CallBackRemoveSelf(cocos2d::CCNode* _pNode, void* data);
	void CallBackRemoveSelf2(cocos2d::CCNode* _pNode);
	void CallBackRemoveSelf(cocos2d::CCNode* _pNode);
	virtual bool init();
	static cocos2d::CCScene* scene(CCRenderTexture* sqr, int num, int redBlood);
	void ShowStar();
	void ShowStarMovie1(float _dt);
	void ShowStarMovie2(float _dt);
	void ShowStarMovie3(float _dt);
	void ShowStarBoss(float _dt);
	void ShowStarBoss1();
	void setRewardLayerInfo(bool visible, bool condition1, bool condition2, bool condition3, int killnum, int attackcombomnum, int Getmoney,int rewardmoney);
private:
	float fStarLocateX;
	float fStarLocateY;
	float fStarLocateX1;
	float fStarLocateY1;
	float fStarLocateX2;
	float fStarLocateY2;
	float fStarLocateX3;
	float fStarLocateY3;
	void AddOver();
	void SetPositionStart(float x, float y); 
	
	void StartDigit(float _t);
	void Timer(float _t);
	int		m_iNowKill;
	int		m_iNowTime;
	int		m_iNowScore;
	int otherScore;
	bool	m_bOverAddCombo;
	bool	m_bStartAddCombo;
	bool	m_bNowKill;
	bool	m_bNowMedal;
	bool	m_bNowGold;
	bool	m_bComboMoney;
	//CCSprite* pSprite1;
	CCSprite *xingxingBack;
	CCSprite *back_small_spr;
	bool Visible;//ÐÇÐÇ±³¾°
	int testnum;
	void StartRewardLayer();
	int levelScore;
	CCArray* overachieveArray;
	bool overachieve[5];
	int m_iAllStar;
	int LevelNum;
	void ShowOverBtn( float _dt );
	void OnContinueLevel(CCObject* pSender);
	void OnGoToMainLevel(CCObject* pSender);
	CREATE_FUNC(RewardLayer);
};