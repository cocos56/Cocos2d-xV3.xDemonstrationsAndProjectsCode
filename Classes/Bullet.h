#pragma once
#include "cocos2d.h"
using namespace cocos2d;

class Bullet :public Sprite
{
public:
	CREATE_FUNC(Bullet);
	bool init();
	void update(float dt);
	float speed;
	float radian;
	float Pi;

	bool isFiring;
	Vector<Bullet*>bullets;

	void fire(bool towardsLeft, bool isDown, bool isGoRight, bool isGoLeft, float x, float y);
	void moveBullets(float dt);

	void listenKeyboardEvent();
	void onKeyPressed2(EventKeyboard::KeyCode code, Event *evt);
	void onKeyReleased2(EventKeyboard::KeyCode code, Event *evt);

	bool outScreen(Node* n);
};