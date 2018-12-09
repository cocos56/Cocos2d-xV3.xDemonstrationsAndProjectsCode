#pragma once

#include "cocos2d.h"

using namespace cocos2d;

class Hero : public Sprite
{
public:
	CREATE_FUNC(Hero);
	virtual bool init();

	bool towardsLeft, isGoLeft, isGoRight, isDown, isJumping, isFiring;

	Sprite *sp;
	Action *act;

	float g, vy, oy;

	void idle();
	void goLeft(float d);
	void goRight(float d);
	void goAnimation();
	void down();
	void jump();

	void listenKeyboardEvent();
	void onKeyPressed2(EventKeyboard::KeyCode code, Event *evt);
	void onKeyReleased2(EventKeyboard::KeyCode code, Event *evt);

	void update(float dt);
};