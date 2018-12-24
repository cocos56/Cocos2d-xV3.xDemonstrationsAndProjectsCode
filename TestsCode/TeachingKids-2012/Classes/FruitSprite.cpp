#include "FruitSprite.h"

//初始化静态变量（静态变量属于类，所有对象共享，而不属于某个对象）
char FruitSprite::_spriteFileName[20] = { 0 };
char FruitSprite::_spriteAudioName[20] = { 0 };
FruitSprite* FruitSprite::pSprite = nullptr;
Size FruitSprite::windowSize;


FruitSprite::FruitSprite() {}
FruitSprite::~FruitSprite()
{
	Director::getInstance()->getEventDispatcher()->removeEventListener(listener);
}

FruitSprite* FruitSprite::create(int i)
{
	//std::vector<Sprite*> _sprites;
	//std::vector<std::string> _spriteNames = { "zero","one","two","three","four","five","six","seven","eight","nine","ten" };

	//i = RandomHelper::random_int(1, 9);
	//sprintf(_spriteFileName, "%s.png", _spriteNames.at(i).c_str());
	//sprintf(_spriteAudioName, "%s.wav", _spriteNames.at(i).c_str());

	sprintf(_spriteFileName, "apple.png");
	sprintf(_spriteAudioName, "apple.mp3");

	pSprite = new FruitSprite();

	if (pSprite->initWithFile(_spriteFileName))
	{
		pSprite->autorelease();
		pSprite->initOptions();
		pSprite->addEvents();

		return pSprite;
	}

	CC_SAFE_DELETE(pSprite);
	return NULL;
}

void FruitSprite::initOptions()
{
	LabelTTF *label = LabelTTF::create("apple", "Marker Felt.ttf", 64);
	label->setAnchorPoint(Vec2(0.5, 0.5));
	label->setPosition(pSprite->getContentSize().width/2, -25);
	label->setColor(Color3B(247, 181, 33));
	this->addChild(label);
}

void FruitSprite::addEvents()
{
	listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);

	listener->onTouchBegan = [&](Touch* touch, Event* event)->bool
	{
		Vec2 p = touch->getLocation();
		Rect rect = this->getBoundingBox();

		if (rect.containsPoint(p))
		{
			return true;
		}

		return false;
	};

	listener->onTouchEnded = [=](Touch* touch, Event* event)
	{
		Vec2 p = touch->getLocation();
		FruitSprite::touchEvent(touch, p);
	};

	Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(listener, 30);
}

void FruitSprite::touchEvent(Touch* touch, cocos2d::Vec2 _p)
{
	SimpleAudioEngine::getInstance()->playEffect(_spriteAudioName);
	touchEffect();
}

void FruitSprite::touchEffect()
{
	auto scaleUP = ScaleBy::create(0.0625f, 1.25/2);
	auto scaleDown = ScaleTo::create(0.0625f, 1.0/2);
	auto rotLeft = RotateBy::create(0.0625f, -40.0f);
	auto rotRight = RotateBy::create(0.0625f, 40.0f);
	auto rotFix = RotateTo::create(0.001, 0.0f);

	auto seq = Sequence::create(scaleUP, rotLeft, scaleDown, rotRight, scaleUP, rotRight, scaleDown, rotLeft, rotFix, NULL);
	this->runAction(seq);

}

void FruitSprite::removeMySprite()
{
	Director::getInstance()->getEventDispatcher()->removeEventListener(listener);
	listener->release();
	removeFromParentAndCleanup(true);
}