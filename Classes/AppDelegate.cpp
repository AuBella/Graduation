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
	//pEGLView->setFrameSize(1280, 768);
    pDirector->setOpenGLView(pEGLView);
	
    // turn on display FPS
    pDirector->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    pDirector->setAnimationInterval(1.0 / 60);
	//CCEGLView::sharedOpenGLView()-&gt;setDesignResolutionSize(720, 480, kResolutionShowAll);
	pEGLView -> setDesignResolutionSize(winSize.width*widthRate/heightRate, winSize.height,  kResolutionShowAll);
	//pEGLView->setDesignResolutionSize(winSize.width*widthRate/heightRate, winSize.height,kResolutionNoBorder);
    // create a scene. it's an autorelease object
	pScene = GameScene::create();

    // run
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
   /* Global* sh = Global::toIns();  
    CCRenderTexture* renderTexture;  
    switch(sh->targetScene){  
    case TargetSceneFirstScene:  
        break;  
    case TargetSceneSecondScene:  
        renderTexture = CCRenderTexture::create(800,600);  
        renderTexture->begin();  
        sh->battleLayer->visit();  
        renderTexture->end();  
  
        CCDirector::sharedDirector()->pushScene(PauseLayer::scene(renderTexture,false));  
        break;  
    case TargetSceneInvalid:  
        break;  
    default:  
        break;  
    }  */
	//CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	//CCRenderTexture *renderTexture = CCRenderTexture::create(visibleSize.width,visibleSize.height);

	////遍历当前类的所有子节点信息，画入renderTexture中。
	////这里类似截图。
	//renderTexture->begin(); 
	////this->getParent()->visit();
	////this->visit();
	//renderTexture->end();

	////将游戏界面暂停，压入场景堆栈。并切换到GamePause界面
	//CCDirector::sharedDirector()->pushScene(Gamepause::scene(renderTexture));
	pScene->getOperatorLayer()->MenuChoose();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
   /* CCDirector::sharedDirector()->startAnimation();*/
	 CCDirector::sharedDirector()->startAnimation();  
  
    CocosDenshion::SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();  
    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
}
