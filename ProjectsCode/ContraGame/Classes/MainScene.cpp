#include "MainScene.h"
#include "GameScene.h"
#include "SimpleAudioEngine.h"

using namespace CocosDenshion;
USING_NS_CC;//using namespace cocos2d

Scene* MainScene::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = MainScene::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool MainScene::init()
{
	//////////////////////////////
	// 1. super init first
	if ( !Layer::init() )
	{
		return false;
	}
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto bg = Sprite::create("MainBG.jpg");
	bg->setAnchorPoint(Vec2(0, 0));
	this->addChild(bg);
	//bg->setPosition(bg->getContentSize().width/2, bg->getContentSize().height/2);

	label = LabelTTF::create("MainScene", "Arial", 24);
	label->setAnchorPoint(Vec2(0, 0));
	label->setPosition(10, 450);
	this->addChild(label);
	listenKeyboardEvent();
	return true;
}

void MainScene::onEnter()
{
	Layer::onEnter();
}

void MainScene::onEnterTransitionDidFinish()
{
	Layer::onEnterTransitionDidFinish();
	SimpleAudioEngine::sharedEngine()->playBackgroundMusic("sound/title.mp3");
}

void MainScene::listenKeyboardEvent()
{
	this->_eventDispatcher->removeAllEventListeners();

	auto listener = EventListenerKeyboard::create();
	listener->onKeyPressed = CC_CALLBACK_2(MainScene::onKeyPressed2, this);
	listener->onKeyReleased = CC_CALLBACK_2(MainScene::onKeyReleased2, this);
	this->_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);


}

void MainScene::onKeyPressed2(EventKeyboard::KeyCode code, Event *evt)
{
	char txt[50] = {};
	sprintf_s(txt, "Key %d is pressed.", code);
	label->setString(txt);

	if(code == EventKeyboard::KeyCode::KEY_KP_ENTER || code == EventKeyboard::KeyCode::KEY_ENTER)
	{
		//Director::getInstance()->replaceScene(GameScene::createScene());
		Director::getInstance()->replaceScene(TransitionMoveInR::create(0.3, GameScene::createScene()));
	}
}

void MainScene::onKeyReleased2(EventKeyboard::KeyCode code, Event *evt)
{
	char txt[50] = {};
	sprintf_s(txt, "Key %d is released.", code);
	label->setString(txt);
}
