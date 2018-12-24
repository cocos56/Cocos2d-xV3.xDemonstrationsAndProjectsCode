#include "MainGame.h"
#include "MainInterface.h"

Scene* MainGame::createScene()
{
	Scene* scene = Scene::create();
	MainGame* layer = MainGame::create();
	scene->addChild(layer);
	return scene;
}

bool MainGame::init()
{
	if (Layer::init())
	{
		windowSize = getContentSize();
		bg = Sprite::create("bg.png");
		bg->setAnchorPoint(Vec2(0, 0));
		bg->setPosition(Vec2(0, 0));
		addChild(bg, 0);

		bg2 = Sprite::create("bg.png");
		bg2->setAnchorPoint(Vec2(0, 0));
		bg2->setPosition(Vec2(0, windowSize.height+18));
		addChild(bg2, 0);

		Sprite* normal = Sprite::create("back.png");
		Sprite* selected = Sprite::create("back_selected.png");
		MenuItemSprite* backBtn = MenuItemSprite::create(normal, selected, CC_CALLBACK_1(MainGame::backToMainInterface, this));
		Menu* list = Menu::create(backBtn, NULL);
		list->setAnchorPoint(Vec2(0, 0));
		list->setScale(1.0/2);
		list->setPosition(Vec2(windowSize.width-normal->getContentSize().width/2-20, windowSize.height- normal->getContentSize().height/2));
		addChild(list, 1);

		Sprite* normal_p = Sprite::create("pause.png");
		Sprite* selected_p = Sprite::create("pause_selected.png");
		MenuItemSprite* pauseBtn = MenuItemSprite::create(normal_p, selected_p, CC_CALLBACK_1(MainGame::pauseGame, this));
		Menu* list_p = Menu::create(pauseBtn, NULL);
		list_p->setAnchorPoint(Vec2(0, 0));
		list_p->setScale(1.0 / 2);
		list_p->setPosition(windowSize.width - normal_p->getContentSize().width / 2,
									normal_p->getContentSize().height/2);
		addChild(list_p);

		auto gameState = Sprite::create("top.png");
		gameState->setScale(0.5);
		gameState->setAnchorPoint(Vec2(0, 1));
		gameState->setPosition(Vec2(0, windowSize.height));
		addChild(gameState, 0);

		schedule(schedule_selector(MainGame::updateBgPosition), 1/60);
		return true;
	}
	return false;
}

void MainGame::updateBgPosition(float dt)
{
	changeBgPosition(bg);
	changeBgPosition(bg2);
}

void MainGame::changeBgPosition(Sprite *bg)
{
	int p = bg->getPositionY();
	if (p <= -1536)
	{
		bg->setPositionY(windowSize.height);
	}
	else
	{
		p -= 5;
		bg->setPositionY(p);
	}
}

void MainGame::backToMainInterface(Ref *obj)
{
	TransitionRotoZoom* ani = TransitionRotoZoom::create(1, MainInterface::createScene());
	Director::getInstance()->replaceScene(ani);
}

void MainGame::pauseGame(Ref *obj)
{
	pause();

	Sprite* resume = Sprite::create("resume.png");
	Sprite* select = Sprite::create("resume.png");
	
	MenuItemSprite *btn = MenuItemSprite::create(resume, select, CC_CALLBACK_1(MainGame::resumeGame, this));
	resume_list = Menu::create(btn, NULL);
	resume_list->setAnchorPoint(Vec2(0.5, 0.5));
	resume_list->setPosition(Vec2(windowSize.width/2, windowSize.height/2));
	addChild(resume_list);
	ScaleTo *max = ScaleTo::create(0.35, 1.5);
	ScaleTo *min = ScaleTo::create(0.35, 0.5);
	RepeatForever* list = RepeatForever::create(Sequence::create(max, min, NULL));
	btn->runAction(list);
}

void MainGame::resumeGame(Ref *obj)
{
	removeChild(resume_list);
	resume();
}