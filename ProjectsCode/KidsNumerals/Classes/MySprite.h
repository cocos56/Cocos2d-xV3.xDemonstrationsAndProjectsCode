//
//  MySprite.h
//  KidsNumerals
//
//  Created by mythlab on 12/9/15.
//
//

#ifndef __KidsNumerals__MySprite__
#define __KidsNumerals__MySprite__

#include "cocos2d.h"
#include "SimpleAudioEngine.h"


USING_NS_CC;
using namespace CocosDenshion;

class MySprite : public Sprite
{
public:
    MySprite();
    ~MySprite();
    static MySprite* create(int i);
 
    
    void initOptions();
    void addEvents();
    
    void touchEvent(Touch* touch,Vec2 _p);
    void removeMySprite();
    EventListenerTouchOneByOne* listener;
    void touchEffect();

};

#endif /* defined(__KidsNumerals__MySprite__) */
