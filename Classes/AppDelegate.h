#ifndef __APP_DELEGATE_H__
#define __APP_DELEGATE_H__

#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "baseRes.h"

#ifdef GameTypeC
	#define d_iLevelNum		2
#else
	#define d_iLevelNum		5
#endif

enum eTransition{
	etHorizontal,
	etVertical,
	etInOut,
	etOutIn,
	etFade,
};

class  AppDelegate : private cocos2d::CCApplication{
public:
    AppDelegate();
    virtual ~AppDelegate();

    virtual bool applicationDidFinishLaunching();

    virtual void applicationDidEnterBackground();
	virtual void applicationWillEnterForeground();
	static void AudioBackResume();
	static void AudioBackPause();

	static void ChangeScene(cocos2d::CCScene* _pScene, eTransition _transition, float _time);
	static void ChangeScene(cocos2d::CCScene* _pScene);

	static void AudioInit1();
	static void AudioInit2();
	static void AudioInit3();
	static void AudioPlayBgm(const char* _path, bool _Repeat = true);
	static void AudioStopBgm();
	static void AudioPause();
	static void AudioResume();
	static int AudioPlayEffect(const char* _path);
	static void AudioStopEffect(int _id);
	static void AudioSetVoice();

	static int WeaponIndex(int _num);
	static int WeaponSpeed(int _num);
	static int WeaponDamage(int _num);

	static void DataInit();
	static void DataInit2();

	static void AudioSwitch();
	static void AudioStopB();
	static int s_VoiceOpen;
	static int m_voice;
	static int m_canVoiceResume;
};

#endif  // __APP_DELEGATE_H__

