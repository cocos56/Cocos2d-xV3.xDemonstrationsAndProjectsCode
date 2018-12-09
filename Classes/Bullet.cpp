#include "Bullet.h"
#include <cmath>

bool Bullet::init()
{
	Sprite::init();
	auto s = Sprite::create("bullet.png");
	addChild(s);
	Pi = acos(-1);
	speed = 6;
	radian = 0;
	return true;
}
void Bullet::update(float dt)
{
	float vx = speed * cos(radian);
	float vy = speed * sin(radian);
	setPosition(getPositionX() + vx, getPositionY() + vy);
}

void Bullet::fire(bool towardsLeft, bool isDown, bool isGoRight, bool isGoLeft, float x, float y)
{
	auto b = create();
	b->radian = towardsLeft ? Pi : 0;
	if (isDown)
	{
		b->setPositionX(x + (towardsLeft ? -35 :35));
		b->setPositionY(y + 16);
	}
	else
	{
		b->setPositionX(x + (towardsLeft ? -20 : 20));
		b->setPositionY(y + 36);
	}
	addChild(b);
	bullets.pushBack(b);
}
void Bullet::moveBullets(float dt)
{
	for (int i=0; i<bullets.size(); i++)
	{
		auto b = bullets.at(i);
		b->update(dt);
		if (outScreen(b))
		{
			b->removeFromParent();
			bullets.eraseObject(b);
			i--;
		}
	}
}

void Bullet::listenKeyboardEvent()
{
	auto listener = EventListenerKeyboard::create();
	listener->onKeyPressed = CC_CALLBACK_2(Bullet::onKeyPressed2, this);
	listener->onKeyReleased = CC_CALLBACK_2(Bullet::onKeyReleased2, this);
	this->_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}
void Bullet::onKeyPressed2(EventKeyboard::KeyCode code, Event *evt)
{

}
void Bullet::onKeyReleased2(EventKeyboard::KeyCode code, Event *evt)
{

}

bool Bullet::outScreen(Node* n)
{
	if (n->getPositionX() < -20 || n->getPositionX() > 600
		|| n->getPositionY() < -20 || n->getPositionY() > 500)
	{
		return true;
	}
	return false;
}