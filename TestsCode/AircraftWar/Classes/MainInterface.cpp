#include "MainInterface.h"
#include "MainGame.h"

Scene* MainInterface::createScene()
{
	Scene *scene = Scene::create();
	MainInterface *layer = MainInterface::create();
	scene->addChild(layer);
	return scene;
}

bool MainInterface::init()
{
	if (Layer::init())
	{
		windowSize = getContentSize();

		Sprite *normal = Sprite::create("start.png");
		Sprite *selected = Sprite::create("start_selected.png");

		MenuItemSprite *startBtn = MenuItemSprite::create(normal, selected, CC_CALLBACK_1(MainInterface::startAction, this));
		Menu* list = Menu::create(startBtn, NULL);
		list->setPosition(Vec2(windowSize.width / 2, windowSize.height / 2));
		addChild(list);
		return true;
	}
	return false;
}

void MainInterface::startAction(Ref *obj)
{
	Director *dic = Director::getInstance();
	TransitionRotoZoom *roto = TransitionRotoZoom::create(1, MainGame::createScene());
	dic->replaceScene(roto);
}
