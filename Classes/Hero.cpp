#include "Hero.h"
#include "GameScene.h"
#include "Bullet.h"

bool Hero::init()
{
	Sprite::init();
	isJumping = isGoRight = isGoLeft = isDown = towardsLeft = isFiring = false;
	idle();
	listenKeyboardEvent();
	return true;
}

void Hero::idle()
{
	this->removeAllChildren();
	auto s = Sprite::create("hero/idle.png");
	s->setAnchorPoint(Vec2(0.5, 0));
	s->setScaleX(towardsLeft ? 1:-1);
	this->addChild(s);
	sp = s;
}
void Hero::goLeft(float d)
{
	float d1 = getPositionX();
	float d2 = d1 - 4;
	setPositionX(d2);

}
void Hero::goRight(float d)
{
	float d1 = getPositionX();
	float d2 = d1 + 4;
	setPositionX(d2);
}

void Hero::goAnimation()
{
	Vector<SpriteFrame*> allFrames;
	char txt[50] = {};
	for(int i=1; i<4; i++)
	{
		sprintf_s(txt, "hero/goLeft%d.png",i);
		SpriteFrame* sf = SpriteFrame::create(txt, Rect(0, 0,  46, 46));
		allFrames.pushBack(sf);
	}
	Animation* ani = Animation::createWithSpriteFrames(allFrames, 0.1);
	sp->setScaleX(towardsLeft ? 1:-1);
	act = sp->runAction(RepeatForever::create(Animate::create(ani)));
}

void Hero::down()
{
	auto s = Sprite::create("hero/down.png");
	s->setAnchorPoint(Vec2(0.5, 0));
	s->setScaleX(towardsLeft ? 1:-1);
	this->addChild(s);
	sp = s;
}
void Hero::jump()
{
	Vector<SpriteFrame*>allFrames;
	char txt[50] = {};
	for (int i=1; i<4; i++)
	{
		sprintf_s(txt, "hero/jump%d.png", i);
		SpriteFrame *sf = SpriteFrame::create(txt, Rect(0, 0, 46, 46));
		allFrames.pushBack(sf);
	}
	Animation* ani = Animation::createWithSpriteFrames(allFrames, 0.1);
	act = sp->runAction(RepeatForever::create(Animate::create(ani)));
}

void Hero::listenKeyboardEvent()
{
	auto listener = EventListenerKeyboard::create();
	listener->onKeyPressed = CC_CALLBACK_2(Hero::onKeyPressed2, this);
	listener->onKeyReleased = CC_CALLBACK_2(Hero::onKeyReleased2, this);

	this->_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}

void Hero::onKeyPressed2(EventKeyboard::KeyCode code, Event *evt)
{
	if(code == EventKeyboard::KeyCode::KEY_LEFT_ARROW)
	{
		isGoLeft=true;
		towardsLeft = true;
		if (!isJumping)
		{
			goAnimation();

		}
	}
	else if(code == EventKeyboard::KeyCode::KEY_RIGHT_ARROW)
	{
		isGoRight=true;
		towardsLeft = false;
		if (!isJumping)
		{
			goAnimation();
		}
	}
	else if(code == EventKeyboard::KeyCode::KEY_DOWN_ARROW)
	{
		if (!isJumping)
		{
			this->removeAllChildren();
			down();
			isDown = true;
		}
	}
	else if(code == EventKeyboard::KeyCode::KEY_J)
	{
		if((isGoLeft||isGoRight)&&!isJumping)
		{
			sp->stopAction(act);
		}
		if (!isJumping)
		{
			isJumping=true;
			oy =  getPositionY();
			jump();
			vy = 6;
			g = -0.25;
		}
	}
}
void Hero::onKeyReleased2(EventKeyboard::KeyCode code, Event *evt)
{
	if(code == EventKeyboard::KeyCode::KEY_LEFT_ARROW)
	{
		isGoLeft=false;
		if (!isJumping)
		{
			sp->stopAction(act);
			idle();
		}
	}
	else if(code == EventKeyboard::KeyCode::KEY_RIGHT_ARROW)
	{
		isGoRight=false;
		if (!isJumping)
		{
			sp->stopAction(act);
			idle();
		}
	}
	else if(code == EventKeyboard::KeyCode::KEY_DOWN_ARROW)
	{
		idle();
		isDown = false;
	}
	else if(code == EventKeyboard::KeyCode::KEY_J)
	{
	}
}

void Hero::update(float dt)
{
	if(isGoRight)
	{
		goRight(dt);
	}
	if(isGoLeft)
	{
		goLeft(dt);
	}
	if(isJumping)
	{
		setPositionY(getPositionY()+vy);
		vy+=g;
		if(getPositionY()<=oy)
		{
			setPositionY(oy);
			isJumping=false;
			sp->stopAction(act);
			idle();
		}
	}
}