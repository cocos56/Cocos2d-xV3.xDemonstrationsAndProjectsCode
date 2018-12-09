#include "GameScene.h"
#include "MainScene.h"
#include "SimpleAudioEngine.h"
#include "Bullet.h"

using namespace CocosDenshion;
USING_NS_CC;//using namespace cocos2d

Scene* GameScene::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = GameScene::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool GameScene::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto bg = Sprite::create("bg.jpg");
	//bg->setPosition(bg->getContentSize().width/2, bg->getContentSize().height/2);
	bg->setAnchorPoint(Vec2(0, 0));
	this->addChild(bg);

	label = LabelTTF::create("GameScene", "Arial", 24);
	label->setAnchorPoint(Vec2(0, 0));
	label->setPosition(10, 450);
	this->addChild(label);
	c = 0;

	listenKeyboardEvent();

	hero = Hero::create();
	hero->setPosition(121, 200);
	this->addChild(hero);

	bullet = Bullet::create();
	this->addChild(bullet);
	this->schedule(schedule_selector(GameScene::update), 1.0 / 45);

	//scheduleUpdate();
	return true;
}

void GameScene::onEnter()
{
	Layer::onEnter();
	SimpleAudioEngine::getInstance()->playBackgroundMusic("sound/backgroundMusic.mp3", true);
}

void GameScene::onEnterTransitionDidFinish()
{
	Layer::onEnterTransitionDidFinish();
}

void GameScene::listenKeyboardEvent()
{
	this->_eventDispatcher->removeAllEventListeners();

	auto listener = EventListenerKeyboard::create();
	listener->onKeyPressed = CC_CALLBACK_2(GameScene::onKeyPressed2, this);
	listener->onKeyReleased = CC_CALLBACK_2(GameScene::onKeyReleased2, this);

	this->_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}

void GameScene::onKeyPressed2(EventKeyboard::KeyCode code, Event *evt)
{
	char txt[50] = {};
	sprintf_s(txt, "Key %d is pressed.", code);
	label->setString(txt);

	if (code == EventKeyboard::KeyCode::KEY_ESCAPE)
	{
		//Director::getInstance()->replaceScene(MainScene::createScene());
		Director::getInstance()->replaceScene(TransitionMoveInL::create(0.3, MainScene::createScene()));
	}
	else if (code == EventKeyboard::KeyCode::KEY_F)
	{
		hero->isFiring = true;
	}
}
void GameScene::onKeyReleased2(EventKeyboard::KeyCode code, Event *evt)
{
	char txt[50] = {};
	sprintf_s(txt, "Key %d is released.", code);
	label->setString(txt);
	if (code == EventKeyboard::KeyCode::KEY_F)
	{
		hero->isFiring = false;
	}
}

void GameScene::update(float dt)
{
	//CCLOG("dt %f ", dt);
	hero->update(dt);
	c++;
	if (hero->isFiring && !(c%15))
	{
		bullet->fire(hero->towardsLeft, hero->isDown, hero->isGoRight, hero->isGoRight, hero->getPositionX(), hero->getPositionY());
	}
	bullet->moveBullets(dt);
}