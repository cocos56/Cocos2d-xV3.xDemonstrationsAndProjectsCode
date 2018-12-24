#pragma once

#include "cocos2d.h"
USING_NS_CC;

#include "GameScene.h"
#include "GameSprite.h"

class GameScene : public Layer
{
public:
	static Scene* createScene();
	bool init();
	void backAction();

	EventListenerTouchOneByOne* listener;
	GameSprite* fruitSprite;
	Size windowSize;
	int fruitNum = 0;

	CREATE_FUNC(GameScene);
};