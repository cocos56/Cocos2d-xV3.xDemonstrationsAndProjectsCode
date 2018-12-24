#pragma once

#include "cocos2d.h"
#include "SimpleAudioEngine.h"


USING_NS_CC;
using namespace CocosDenshion;

class FruitSprite : public Sprite
{
public:
	FruitSprite();
	~FruitSprite();
	static FruitSprite* create(int i);


	void initOptions();
	void addEvents();

	void touchEvent(Touch* touch, Vec2 _p);
	void removeMySprite();
	EventListenerTouchOneByOne* listener;
	void touchEffect();

	static char _spriteFileName[20];
	static char _spriteAudioName[20];
	static FruitSprite *pSprite;
	static Size windowSize;
};