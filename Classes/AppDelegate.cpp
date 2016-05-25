#include "cocos2d.h"
#include "CCEGLView.h"
#include "AppDelegate.h"
#include "baseRes.h"
#include "FileCommon.h"
#include "MainScene.h"

#define ShowFrame false
#define LevelOpenNum	18

int AppDelegate::s_VoiceOpen	= 1;
int AppDelegate::m_voice = 50;
int AppDelegate::m_canVoiceResume = 0;

using namespace CocosDenshion;
USING_NS_CC;

AppDelegate::AppDelegate(){
	SimpleAudioEngine::sharedEngine()->preloadEffect("SoundEffect/zmanhua1.mp3");
}

AppDelegate::~AppDelegate(){
	SimpleAudioEngine::end();
}

bool AppDelegate::applicationDidFinishLaunching()
{
	CCEGLView* eglView = CCEGLView::sharedOpenGLView();
    CCDirector *pDirector = CCDirector::sharedDirector();
	pDirector->setOpenGLView(eglView);

    // turn on display FPS
    pDirector->setDisplayStats(ShowFrame);
    pDirector->setAnimationInterval(1.0 / 60);

	CCSize frameSize = eglView->getFrameSize();
	eglView->setDesignResolutionSize(frameSize.width, frameSize.height, kResolutionNoBorder);

    // create a scene. it's an autorelease object
	//Ö÷²Ëµ¥
	CCScene* pScene = MainScene::create();
	pDirector->runWithScene(pScene);
    return true;
}



// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    //CCDirector::sharedDirector()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
	CCDirector::sharedDirector()->stopAnimation();  
  
    CocosDenshion::SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();  
	//pScene->getOperatorLayer()->MenuChoose();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
	 CCDirector::sharedDirector()->startAnimation();  
  
    // if you use SimpleAudioEngine, it must resume here
    CocosDenshion::SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();  
}

//// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
//void AppDelegate::applicationDidEnterBackground()
//{
//	//CCTextureCache::sharedTextureCache()->removeAllTextures();
//
//	/*{
//	CCDirector::sharedDirector()->pause();
//	SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
//	SimpleAudioEngine::sharedEngine()->pauseAllEffects();
//	m_voice = SimpleAudioEngine::sharedEngine()->getEffectsVolume();
//	SimpleAudioEngine::sharedEngine()->setEffectsVolume(0);
//	PayService::getInstance()->setCheckTrue();
//	}*/
//
//	//m_canVoiceResume = 0;
//	//PayService::OnPause();
//}
//
//// this function will be called when the app is active again
//void AppDelegate::applicationWillEnterForeground()
//{
//	//CCTextureCache::sharedTextureCache()->reloadAllTextures();
//	//CCDirector::sharedDirector()->resume();
//	//if ( CGameControler::GetGameControler() )
//	//	CGameControler::GetGameControler()->PauseGame();
//	//m_canVoiceResume++;
//	//PayService::OnResume();
//	//SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
//	//SimpleAudioEngine::sharedEngine()->resumeAllEffects();
//	//SimpleAudioEngine::sharedEngine()->setEffectsVolume(m_voice);
//}

void AppDelegate::AudioBackResume(){
	m_canVoiceResume++;
	if ( m_canVoiceResume >= 2 ){
		CCTextureCache::sharedTextureCache()->reloadAllTextures();
		m_canVoiceResume = 0;
		CCDirector::sharedDirector()->startAnimation();
		SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
		SimpleAudioEngine::sharedEngine()->resumeAllEffects();
		SimpleAudioEngine::sharedEngine()->setEffectsVolume(m_voice);
	}
}

void AppDelegate::AudioBackPause(){
	CCTextureCache::sharedTextureCache()->removeAllTextures();
	SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
	SimpleAudioEngine::sharedEngine()->pauseAllEffects();
	m_voice = SimpleAudioEngine::sharedEngine()->getEffectsVolume();
	SimpleAudioEngine::sharedEngine()->setEffectsVolume(0);
	m_canVoiceResume = 0;
	CCDirector::sharedDirector()->stopAnimation();
}

void AppDelegate::AudioSwitch(){
	AppDelegate::s_VoiceOpen = 1 - AppDelegate::s_VoiceOpen;
	AudioSetVoice();
}

void AppDelegate::AudioSetVoice(){
	if ( AppDelegate::s_VoiceOpen == 0 ){
		m_voice = SimpleAudioEngine::sharedEngine()->getEffectsVolume();
		SimpleAudioEngine::sharedEngine()->setEffectsVolume(0);
	}
	else{
		SimpleAudioEngine::sharedEngine()->setEffectsVolume(m_voice);
	}
}
//½çÃæÇÐ»»
void AppDelegate::ChangeScene(cocos2d::CCScene* _pScene, eTransition _transition, float _time){
	CCDirector::sharedDirector()->getRunningScene()->stopAllActions();
	CCDirector::sharedDirector()->getRunningScene()->pauseSchedulerAndActions();
	CCScene* pScene = NULL;
	switch ( _transition ){
	case etHorizontal:
		pScene = CCTransitionProgressHorizontal::create(_time, _pScene);
		break;
	case etVertical:
		pScene = CCTransitionProgressVertical::create(_time, _pScene);
		break;
	case etOutIn:
		pScene = CCTransitionProgressInOut::create(_time, _pScene);
		break;
	case etFade:
		pScene = CCTransitionFade::create(_time, _pScene);
		break;
	default:
		break;
	}
	if ( pScene ){
		CCDirector::sharedDirector()->replaceScene(_pScene);
	}
}

void AppDelegate::ChangeScene(cocos2d::CCScene* _pScene){
	if ( _pScene ){
		CCDirector::sharedDirector()->getRunningScene()->stopAllActions();
		CCDirector::sharedDirector()->getRunningScene()->pauseSchedulerAndActions();
		CCDirector::sharedDirector()->replaceScene(_pScene);
	}
}
//ÒôÀÖ»º´æ
void AppDelegate::AudioInit1(){
	SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic("MS/Music/mainmenu/mainmenu.mp3");
	SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic("sound");
	SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic("MS/Music/level1/1.mp3");
#ifndef GameTypeC
	SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic("MS/Music/level1/2.mp3");
	SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic("MS/Music/level2/1.mp3");
	SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic("MS/Music/level2/2.mp3");
	SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic("MS/Music/mainmenu/LevelChose.mp3");	
#endif
}

void AppDelegate::AudioInit2(){
	SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic("MS/Music/level2/1.mp3");
}

void AppDelegate::AudioInit3(){}

//±³¾°ÒôÀÖ
void AppDelegate::AudioPlayBgm(const char* _path, bool _Repeat){
	if ( s_VoiceOpen ){
		SimpleAudioEngine::sharedEngine()->setEffectsVolume(100);
		SimpleAudioEngine::sharedEngine()->playBackgroundMusic(_path, _Repeat);
	}
}

void AppDelegate::AudioStopBgm(){
	SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
	SimpleAudioEngine::sharedEngine()->stopAllEffects();
	SimpleAudioEngine::sharedEngine()->setEffectsVolume(0);
}
//ÒôÀÖ²¥·Å¿ØÖÆ
void AppDelegate::AudioStopB(){
	SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
}

void AppDelegate::AudioPause(){
	SimpleAudioEngine::sharedEngine()->pauseAllEffects();
	SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
}

void AppDelegate::AudioResume(){
	if ( AppDelegate::s_VoiceOpen ){
		SimpleAudioEngine::sharedEngine()->resumeAllEffects();
		SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
	}
}

//ÒôÐ§
int AppDelegate::AudioPlayEffect(const char* _path){
	int id = -1;
	if ( s_VoiceOpen ){
		id = SimpleAudioEngine::sharedEngine()->playEffect(_path);
	}
	return id;
}

void AppDelegate::AudioStopEffect( int _id ){}
