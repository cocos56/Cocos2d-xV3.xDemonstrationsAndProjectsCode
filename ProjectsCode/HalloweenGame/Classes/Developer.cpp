
#include "Developer.h"
#include "MainScene.h"

using namespace CocosDenshion;

Scene* Developer::createScene()
{
	auto scene = Scene::create();
	auto layer = Developer::create();
	scene->addChild(layer);
	return scene;
}

bool Developer::init()
{
	if( !Layer::init() ){
		return false;
	}

	UserDefault *defaults  = UserDefault::getInstance();
	
	// 添加背景图片
    auto sprite = Sprite::create("scene_abo.png");
	sprite->setPosition(Point(GAME_SCREEN_WIDTH/2,GAME_SCREEN_HEIGHT/2));
    this->addChild(sprite);

	// 添加返回主菜单按钮
	auto backItem = MenuItemImage::create(
                                           "btn_ret.png",
                                           "btn_ret.png",
										   CC_CALLBACK_1(Developer::menuBackCallback, this));
    
	backItem->setPosition(Vec2(backItem->getContentSize().width/2,GAME_SCREEN_HEIGHT-backItem->getContentSize().height/2));
    
	
    MenuItemImage *_turnOn,*_turnOff;  
    _turnOn = MenuItemImage::create(  
        "btn_musOn.png",  
        "btn_musOn.png");  
    _turnOff = MenuItemImage::create(  
        "btn_musOff.png",  
        "btn_musOff.png");  

	MenuItemImage *_trnOn,*_trnOff;
	_trnOn = MenuItemImage::create(  
        "btn_musOn.png",  
        "btn_musOn.png");  
    _trnOff = MenuItemImage::create(  
        "btn_musOff.png",  
        "btn_musOff.png");

	// 音乐开关
    MenuItemToggle *musicItem = MenuItemToggle::createWithCallback(CC_CALLBACK_1(Developer::menuMusicCallback, this), _turnOn,_turnOff, NULL);       
	musicItem->setPosition(Point(GAME_SCREEN_WIDTH/1.4,GAME_SCREEN_HEIGHT/1.8));  
	
	// 音效开关
    MenuItemToggle *soundItem = MenuItemToggle::createWithCallback(CC_CALLBACK_1(Developer::menuSoundCallback, this), _trnOn,_trnOff, NULL);       
	soundItem->setPosition(Point(GAME_SCREEN_WIDTH/1.4,GAME_SCREEN_HEIGHT/1.4));  

	auto menu = Menu::create(backItem,musicItem,soundItem, NULL);
    menu->setPosition(Vec2::ZERO);
	this -> addChild( menu );

	TTFConfig config("Marker Felt.ttf",28);
	// 关于
	auto labelAbout = Label::createWithTTF(config, "About Us: blog.csdn.net/lttree ");
	labelAbout -> setPosition(Point( GAME_SCREEN_WIDTH/2 , GAME_SCREEN_HEIGHT/1.2));
	labelAbout->setColor(Color3B(35,35,35));
	this->addChild(labelAbout);

	if (defaults->getBoolForKey(MUSIC_KEY)) {                                      
        musicItem->setSelectedIndex(0);                                  
    } 
	else {  
        musicItem->setSelectedIndex(1);                                  
    }

	if (defaults->getBoolForKey(SOUND_KEY)) {                                      
        soundItem->setSelectedIndex(0);                                  
    } 
	else {  
        soundItem->setSelectedIndex(1);                                  
    }
	return true;
}

void Developer::menuBackCallback( Ref *pSender )
{
	auto scene = MainScene::createScene();
	CCTransitionScene* reScene = CCTransitionPageTurn::create(1.0f, scene, true);
	CCDirector::sharedDirector()->replaceScene(reScene);
}

void Developer::menuMusicCallback( Ref *pSender )
{
	auto musicToggleMenuItem = (MenuItemToggle*)pSender;   
  
    UserDefault *defaults  = UserDefault::getInstance();  
    if (defaults->getBoolForKey(MUSIC_KEY)) {                                      
        defaults->setBoolForKey(MUSIC_KEY, false);  
        SimpleAudioEngine::getInstance()->stopBackgroundMusic();  
    } 
	else {  
        defaults->setBoolForKey(MUSIC_KEY, true);  
        SimpleAudioEngine::getInstance()->playBackgroundMusic("music_mainScene.wav");  
    }                                          
}

void Developer::menuSoundCallback( Ref *pSender )
{
	auto soundToggleMenuItem = (MenuItemToggle*)pSender;   
  
    UserDefault *defaults  = UserDefault::getInstance();  
	if (defaults->getBoolForKey(SOUND_KEY)) {                                      
        defaults->setBoolForKey(SOUND_KEY, false);  
    } 
	else {  
        defaults->setBoolForKey(SOUND_KEY, true);   
    }
}

void Developer::onEnter()
{
	Layer::onEnter();
}

void Developer::onEnterTransitionDidFinish()
{
	Layer::onEnterTransitionDidFinish();  
	if (UserDefault::getInstance()->getBoolForKey(MUSIC_KEY)) {                      
        SimpleAudioEngine::getInstance()->playBackgroundMusic("music_mainScene.wav", true);  
    } 
}

void Developer::onExit()
{
	Layer::onExit();
}

void Developer::onExitTransitionDidStart()
{
	Layer::onExitTransitionDidStart();
}

void Developer::cleanup()
{
	Layer::cleanup();
	SimpleAudioEngine::getInstance()->stopBackgroundMusic("music_mainScene.wav");
}