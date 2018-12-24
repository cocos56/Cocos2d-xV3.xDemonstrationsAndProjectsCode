#pragma once

#include "cocos2d.h"
USING_NS_CC;

#include "GameScene.h"
#include "FruitSprite.h"

class GameScene : public Layer
{
public:
	static Scene* createScene();
	bool init();

	EventListenerTouchOneByOne* listener;
	FruitSprite* fruitSprite;
	Size windowSize;

	CREATE_FUNC(GameScene);
};