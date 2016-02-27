#include "AppDelegate.h"

USING_NS_CC;

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    CCDirector* pDirector = CCDirector::sharedDirector();
	
    CCEGLView* pEGLView = CCEGLView::sharedOpenGLView();
	CCSize frameSize = pEGLView->getFrameSize();
	CCSize winSize=CCSize(480,320);

	//将宽和高做一个比，通过这个比，来具体的调整逻辑分辨率的大小
	float widthRate = frameSize.width/winSize.width;
	float heightRate = frameSize.height/winSize.height;
    pDirector->setOpenGLView(pEGLView);
	
    // turn on display FPS
    pDirector->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    pDirector->setAnimationInterval(1.0 / 60);
	pEGLView -> setDesignResolutionSize(winSize.width*widthRate/heightRate, winSize.height,  kResolutionShowAll);
	pScene = GameScene::create();
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
	pScene->getOperatorLayer()->MenuChoose();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
	 CCDirector::sharedDirector()->startAnimation();  
  
    // if you use SimpleAudioEngine, it must resume here
    CocosDenshion::SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();  
}
