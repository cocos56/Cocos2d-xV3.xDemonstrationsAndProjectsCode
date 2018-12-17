#include "AppDelegate.h"
#include "InkmooFlash.h"

USING_NS_CC;

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
        glview = GLView::create("My Game");
        director->setOpenGLView(glview);

		glview -> setFrameSize(320,480);
    }

	glview->setDesignResolutionSize(480, 800, ResolutionPolicy::EXACT_FIT);
	
	std::vector<std::string> searchPath;
	searchPath.push_back("rese");
	CCFileUtils::getInstance()->setSearchPaths(searchPath);
//	director->setContentScaleFactor( 480.0 / 320.0 );

    /*
	// turn on display FPS
    director->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0 / 60);
	*/

    // create a scene. it's an autorelease object
	auto scene = InkmooFlash::createScene();

    // run
    director->runWithScene(scene);

	//初始化 背景音乐  
    SimpleAudioEngine::getInstance()->preloadBackgroundMusic("music_bg.mp3"); 
	SimpleAudioEngine::getInstance()->preloadBackgroundMusic("music_mainScene.mp3");
    //初始化 音效  
    SimpleAudioEngine::getInstance()->preloadEffect("music_explode.wav"); 
	SimpleAudioEngine::getInstance()->preloadEffect("music_explodeOne.wav");
	SimpleAudioEngine::getInstance()->preloadEffect("music_gameOver.mp3");
	SimpleAudioEngine::getInstance()->preloadEffect("music_fail.mp3");
	SimpleAudioEngine::getInstance()->preloadEffect("music_win.wav");

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}
