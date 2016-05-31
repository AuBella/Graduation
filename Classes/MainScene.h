#include"cocos2d.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

class MainScene: public CCScene{
public:
	MainScene(void);
	~MainScene(void);
	virtual bool init();
	void MenuSettingCallback(CCObject* pSender);
	void MenuSettingCallback1(CCObject* pSender);
	void MenuSettingCallback2(CCObject* pSender);
	void MenuSettingCallback3(CCObject* pSender);
	CREATE_FUNC(MainScene);
};