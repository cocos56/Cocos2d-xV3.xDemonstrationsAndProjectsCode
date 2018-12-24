#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "MySprite.h"
#include "MenuScene.h"

USING_NS_CC;
using namespace CocosDenshion;


// SOME USEFUL MACROS FOR SCALING SPRITES
// 3. SCREEN SIZES
#define GET_SCREEN_SIZE Director::getInstance()->getWinSize()
#define GET_VISIBLE_SIZE Director::getInstance()->getVisibleSize()
#define GET_VISIBLE_ORIGIN Director::getInstance()->getVisibleOrigin();


// USE MIN for sprites and MAX for backgrounds)
// LANDSCAPE
//factor = MIN(targetWidth / DesignWidth, targetHeight / DesignHeight)

// PORTRAIT
// factor = MIN(targetHeight / DesignHeight,targetWidth / DesignWidth)


// 4. UNIVERSAL SCALE BACKGROUND
#define SCALE_UNIV_BKGND(_object,factor) \
MAX(GET_SCREEN_SIZE.width/_object->getContentSize().width,GET_SCREEN_SIZE.height/_object->getContentSize().height) * factor


// 5. UNIVERSAL SCALE SPRITES
#define SCALE_UNIV_SPRTE(_object,factor) \
MIN(GET_SCREEN_SIZE.width/_object->getContentSize().width,GET_SCREEN_SIZE.height/_object->getContentSize().height) * factor






class HelloWorld : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    void prevNumberCallback(Ref* pSender);
    void nextNumberCallback(Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);
    
    void createNewNumber(int i);
    MySprite* _mySprite;
    int currentNumber;
    
    MenuItemImage* prevNumItem;
    MenuItemImage* nextNumItem;
};

#endif // __HELLOWORLD_SCENE_H__
