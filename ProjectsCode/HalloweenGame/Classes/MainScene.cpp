
#include "MainScene.h"
#include "GameScene.h"
#include "Developer.h"
#include "GameOverScene.h"

using namespace CocosDenshion;

Scene* MainScene::createScene( )
{
	auto scene = Scene::create();
	auto layer = MainScene::create();
	scene -> addChild( layer );
	return scene;
}

bool MainScene::init( )
{
	if( !Layer::init() ){
		return false;
	}

	// 添加背景图片
    auto sprite = Sprite::create("scene_sta.png");
	sprite->setPosition(Point(GAME_SCREEN_WIDTH/2,GAME_SCREEN_HEIGHT/2));
    this->addChild(sprite);

	// 添加开始按钮
	auto startItem = MenuItemImage::create(
                                           "btn_start01.png",
                                           "btn_start02.png",
										   CC_CALLBACK_1(MainScene::menuStartCallback, this));
    
	startItem->setPosition(Vec2(GAME_SCREEN_WIDTH/2,GAME_SCREEN_HEIGHT/6));

	// 添加设置按钮
	auto setItem = MenuItemImage::create(
											"btn_setting01.png",
											"btn_setting02.png",
											CC_CALLBACK_1(MainScene::menuSetCallback,this));
	setItem->setPosition(Vec2( setItem->getContentSize().width , GAME_SCREEN_HEIGHT/6 ));

	// 添加退出按钮
	auto exitItem = MenuItemImage::create(
											"btn_exit01.png",
											"btn_exit02.png",
											CC_CALLBACK_1(MainScene::menuExitCallback,this));
	exitItem->setPosition(Vec2( GAME_SCREEN_WIDTH-exitItem->getContentSize().width ,GAME_SCREEN_HEIGHT/6 ));

    auto menu = Menu::create(startItem,setItem,exitItem, NULL);
    menu->setPosition(Vec2::ZERO);
	this -> addChild( menu );

	return true;
}

void MainScene::menuStartCallback( Ref* pSender )
{
	auto scene = GameScene::createScene();
	CCDirector::sharedDirector()->replaceScene(scene);
}

void MainScene::menuSetCallback(Ref *pSender)
{
	auto scene = Developer::createScene();
	CCTransitionScene* reScene = CCTransitionPageTurn::create(1.0f, scene, false);
	CCDirector::sharedDirector()->replaceScene(reScene);
}

void MainScene::menuExitCallback(Ref *pSender)
{
	Director::getInstance()->end();
}

void MainScene::onEnter()
{
	Layer::onEnter();
}

void MainScene::onEnterTransitionDidFinish()
{
	Layer::onEnterTransitionDidFinish();  
	if (UserDefault::getInstance()->getBoolForKey(MUSIC_KEY)) {                      
        SimpleAudioEngine::getInstance()->playBackgroundMusic("music_mainScene.mp3", true);  
    } 
}

void MainScene::onExit()
{
	Layer::onExit();
}

void MainScene::onExitTransitionDidStart()
{
	Layer::onExitTransitionDidStart();
}

void MainScene::cleanup()
{
	Layer::cleanup();
	SimpleAudioEngine::getInstance()->stopBackgroundMusic("music_mainScene.mp3");
}