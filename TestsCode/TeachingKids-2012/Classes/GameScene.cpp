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
		windowSize = getContentSize();

		Sprite *bg = Sprite::create("bg.png");
		bg->setAnchorPoint(Vec2(0, 0));
		bg->setScale(0.5);
		addChild(bg);

		Sprite *left = Sprite::create("left.png");
		left->setAnchorPoint(Vec2(1, 0));
		left->setPosition(windowSize.height/2+20, windowSize.width / 5);
		left->setScale(0.5);
		addChild(left);

		Sprite *right = Sprite::create("right.png");
		right->setAnchorPoint(Vec2(0, 0));
		right->setPosition(windowSize.height/2 + right->getContentSize().height-20, windowSize.width/5);
		right->setScale(0.5);
		addChild(right);

		Sprite *back = Sprite::create("back.png");
		back->setAnchorPoint(Vec2(0, 1));
		back->setPosition(0, windowSize.height);
		back->setScale(0.5);
		addChild(back);

		/*Sprite* normal = Sprite::create("back.png");
		Sprite* selected = Sprite::create("back_selected.png");
		MenuItemSprite* backBtn = MenuItemSprite::create(normal, selected, CC_CALLBACK_1(MainGame::backToMainInterface, this));
		Menu* list = Menu::create(backBtn, NULL);
		list->setAnchorPoint(Vec2(0, 0));
		list->setScale(1.0 / 2);
		list->setPosition(Vec2(windowSize.width - normal->getContentSize().width / 2 - 20, windowSize.height - normal->getContentSize().height / 2));
		addChild(list, 1);*/

		fruitSprite = FruitSprite::create(1);
		windowSize = getContentSize();
		fruitSprite->setScale(0.5);
		fruitSprite->setAnchorPoint(Vec2(0.5, 0.5));
		fruitSprite->setPosition(windowSize.height / 2 + fruitSprite->getContentSize().height / 4 + 50, windowSize.width / 2 - fruitSprite->getContentSize().width / 4 - 20);
		addChild(fruitSprite, 1);

		return true;
	}
	return false;
}