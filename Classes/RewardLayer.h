#include"cocos2d.h"
USING_NS_CC;

class RewardLayer :public CCLayer{
public:
	RewardLayer();
	~RewardLayer();
	virtual bool init();
	void calculationStars(int Time);
	static cocos2d::CCScene* scene(CCRenderTexture* sqr, int num, int redBlood);
	CREATE_FUNC(RewardLayer);
};