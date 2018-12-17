//
//  MenuScene.cpp
//  KidsNumerals
//
//  Created by mythlab on 12/14/15.
//
//

#include "MenuScene.h"

Scene* MenuScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = MenuScene::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool MenuScene::init()
{
    // super init first
    if(!Layer::init())
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    Sprite* background = Sprite::create("bg.png");
    background->setPosition(Vec2(visibleSize.width/2,visibleSize.height/2));
    SCALE_UNIV_BKGND(background, 0.5);
    this->addChild(background);
    
    auto playButton = MenuItemImage::create(
                                       "rightArrow.png",
                                       "rightArrow.png",
                                       CC_CALLBACK_1(MenuScene::playCallback, this));
    
    playButton->setPosition(Vec2(visibleSize.width/2,visibleSize.height/2));
    playButton->setScale(0.35);
    
    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "exit.png",
                                           "exit.png",
                                           CC_CALLBACK_1(MenuScene::exitCallback, this));
    
    closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/7,
                                origin.y + closeItem->getContentSize().height/8));
    closeItem->setScale(0.25);

    
    // create menu, it's an autorelease object
    auto menu = Menu::create(playButton,closeItem,NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);
    
    
    
    return true;
}

void MenuScene::playCallback(cocos2d::Ref *pSender)
{
    // initialize director
    auto director = Director::getInstance();
    
    // create a scene. it's an autorelease object
    auto scene = HelloWorld::createScene();
    
    // run
    director->replaceScene(scene);
}

void MenuScene::exitCallback(Ref* pSender)
{
    Director::getInstance()->end();
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}





