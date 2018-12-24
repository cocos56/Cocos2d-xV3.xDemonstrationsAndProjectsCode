#include "MySprite.h"

MySprite::MySprite(){}
MySprite::~MySprite()
{
    Director::getInstance()->getEventDispatcher()->removeEventListener(listener);
}

char _spriteFileName[20] = {0} ;
char _spriteAudioName[20] = {0} ;

MySprite* MySprite::create(int i)
{
    std::vector<Sprite*> _sprites;
    std::vector<std::string> _spriteNames = {"zero","one","two","three","four","five","six","seven","eight","nine","ten"};
    
	//i = RandomHelper::random_int(1, 9);
    sprintf(_spriteFileName,"%s.png",_spriteNames.at(i).c_str());
    sprintf(_spriteAudioName,"%s.wav",_spriteNames.at(i).c_str());
   
    
     MySprite* pSprite = new MySprite();
      
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

void MySprite::initOptions()
{
    
}

void MySprite::addEvents()
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
    
    listener->onTouchEnded = [=] (Touch* touch, Event* event)
    {
        Vec2 p = touch->getLocation();
        MySprite::touchEvent(touch,p);
    };
    
    Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(listener, 30);
}

void MySprite::touchEvent(Touch* touch, cocos2d::Vec2 _p)
{
    SimpleAudioEngine::getInstance()->playEffect(_spriteAudioName);
    touchEffect();
}

void MySprite::touchEffect()
{
    auto scaleUP = ScaleBy::create(0.0625f, 1.25f);
    auto scaleDown = ScaleTo::create(0.0625f,1.0f);
    auto rotLeft = RotateBy::create(0.0625f, -40.0f);
    auto rotRight = RotateBy::create(0.0625f, 40.0f);
    auto rotFix = RotateTo::create(0.001, 0.0f);
    
    auto seq = Sequence::create(scaleUP,rotLeft,scaleDown,rotRight,scaleUP,rotRight,scaleDown,rotLeft,rotFix,NULL);
    this->runAction(seq);

}

void MySprite::removeMySprite()
{
    Director::getInstance()->getEventDispatcher()->removeEventListener(listener);
    listener->release();
    removeFromParentAndCleanup(true);
}