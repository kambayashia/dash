#include "AppDelegate.h"
#include "Scene/StageScene.h"
#include "HelloWorldScene.h"
#include "TitleScene.h"

USING_NS_CC;

typedef struct tagResource
{
    cocos2d::CCSize size;
    char directory[100];
}Resource;
/*
static Resource smallResource  =  { cocos2d::CCSizeMake(480, 320),   "iphone" };
static Resource mediumResource =  { cocos2d::CCSizeMake(1024, 768),  "ipad"   };
static Resource largeResource  =  { cocos2d::CCSizeMake(2048, 1536), "ipadhd" };
 */
static Resource smallResource  =  { cocos2d::CCSizeMake(480, 320),   "hdpi" };
static Resource mediumResource =  { cocos2d::CCSizeMake(1024, 768),  "hdpi"   };
static Resource largeResource  =  { cocos2d::CCSizeMake(2048, 1536), "hdpi" };
static cocos2d::CCSize designResolutionSize = cocos2d::CCSizeMake(480, 320);

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    auto director = Director::getInstance();
    auto eglView = EGLView::getInstance();

    director->setOpenGLView(eglView);
	
    eglView->setDesignResolutionSize(designResolutionSize.width, designResolutionSize.height, kResolutionNoBorder);
    CCSize frameSize = eglView->getFrameSize();
    std::vector<std::string> searchPath;
    
    if (frameSize.height > mediumResource.size.height)
    {
        searchPath.push_back(largeResource.directory);
        director->setContentScaleFactor(largeResource.size.height/designResolutionSize.height);
    }
    else if (frameSize.height > smallResource.size.height)
    {
        searchPath.push_back(mediumResource.directory);
        director->setContentScaleFactor(mediumResource.size.height/designResolutionSize.height);
    }
    else
    {
        searchPath.push_back(smallResource.directory);
        director->setContentScaleFactor(smallResource.size.height/designResolutionSize.height);
    }
    CCFileUtils::sharedFileUtils()->setSearchPaths(searchPath);
    
    // turn on display FPS
    director->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0 / 60);

    // create a scene. it's an autorelease object
    auto scene = Title::createScene();

    // run
    director->runWithScene(scene);

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
}
