#include"cocos2d.h"
#include"GameScene.h"
//#include"IconvString.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

class MainScene: public CCScene{
public:
	MainScene(void);
	~MainScene(void);
	virtual bool init();
	void MenuSettingCallback(CCObject* pSender);
	void MenuSettingCallback1(CCObject* pSender);
	CREATE_FUNC(MainScene);
};