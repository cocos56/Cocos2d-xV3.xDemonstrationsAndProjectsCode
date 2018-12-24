#include "GameScene.h"

#include "SimpleAudioEngine.h"
using namespace CocosDenshion;

Scene* GameScene::createScene()
{
	Scene *scene = Scene::create();
	GameScene *layer = GameScene::create();
	scene->addChild(layer);
	return scene;
}

bool GameScene::init()
{
	if (Layer::init())
	{
		//获取分辨率（窗口大小）
		windowSize = getContentSize();

		//添加背景
		Sprite *bg = Sprite::create("bg.png");
		bg->setAnchorPoint(Vec2(0, 0));
		bg->setScale(0.5);
		addChild(bg);

		//添加左键
		Sprite *left = Sprite::create("left.png");
		left->setAnchorPoint(Vec2(1, 0));
		left->setPosition(windowSize.height / 2 + 20, windowSize.width / 5);
		left->setScale(0.5);
		addChild(left);

		//添加右键
		Sprite *right = Sprite::create("right.png");
		right->setAnchorPoint(Vec2(0, 0));
		right->setPosition(windowSize.height / 2 + right->getContentSize().height - 20, windowSize.width / 5);
		right->setScale(0.5);
		addChild(right);

		//添加返回键
		Sprite *back_normal = Sprite::create("back.png");
		back_normal->setScale(0.5);
		Sprite *back_pressed = Sprite::create("back_pressed.png");
		back_pressed->setScale(0.5);
		MenuItemSprite *backBtn = MenuItemSprite::create(back_normal, back_pressed, CC_CALLBACK_0(GameScene::backAction, this));
		Menu *list = Menu::create(backBtn, NULL);
		list->setAnchorPoint(Vec2(0, 1));
		list->setPosition(0, windowSize.height);
		addChild(list);

		/*MenuItemSprite *startBtn = MenuItemSprite::create(back_normal, back_pressed, CC_CALLBACK_1(MainInterface::startAction, this));
		Menu* list = Menu::create(startBtn, NULL);
		list->setPosition(Vec2(windowSize.width / 2, windowSize.height / 2));
		addChild(list);*/

		/*back->setAnchorPoint(Vec2(0, 1));
		back->setPosition(0, windowSize.height);
		back->setScale(0.5);
		addChild(back);*/

		/*Sprite *normal = Sprite::create("start.png");
		Sprite *selected = Sprite::create("start_selected.png");
		MenuItemSprite *startBtn = MenuItemSprite::create(normal, selected, CC_CALLBACK_1(MainInterface::startAction, this));
		Menu* list = Menu::create(startBtn, NULL);
		list->setPosition(Vec2(windowSize.width / 2, windowSize.height / 2));
		addChild(list);*/

		//添加水果精灵
		fruitSprite = GameSprite::createFruitSprite(fruitNum);
		windowSize = getContentSize();
		fruitSprite->setScale(0.5);
		fruitSprite->setAnchorPoint(Vec2(0.5, 0.5));
		fruitSprite->setPosition(windowSize.height / 2 + fruitSprite->getContentSize().height / 4 + 50, windowSize.width / 2 - fruitSprite->getContentSize().width / 4 - 20);
		addChild(fruitSprite, 1);

		return true;
	}
	return false;
}

void GameScene::backAction()
{

}