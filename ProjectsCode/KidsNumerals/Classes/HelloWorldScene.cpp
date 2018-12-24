#include "HelloWorldScene.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }

    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    Sprite* background = Sprite::create("bg.png");
    background->setPosition(Vec2(visibleSize.width/2,visibleSize.height/2));
    SCALE_UNIV_BKGND(background, 0.5);
    this->addChild(background);
    

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "exit.png",
                                           "exit.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
    
	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/7,
                                origin.y + closeItem->getContentSize().height/8));
    closeItem->setScale(0.25);
    
    
    // add a "prevNUM" icon to get to previous number
    prevNumItem = MenuItemImage::create(
                                           "leftArrow.png",
                                           "leftArrow.png",
                                           CC_CALLBACK_1(HelloWorld::prevNumberCallback, this));
    
    prevNumItem->setPosition(Vec2(origin.x + prevNumItem->getContentSize().width/4 ,
                                visibleSize.height/2 ));
    prevNumItem->setScale(0.35);
    
    // add a "nextNUM" icon to get to previous number
    nextNumItem = MenuItemImage::create(
                                             "rightArrow.png",
                                             "rightArrow.png",
                                             CC_CALLBACK_1(HelloWorld::nextNumberCallback, this));
    
    nextNumItem->setPosition(Vec2(origin.x + visibleSize.width - nextNumItem->getContentSize().width/4 ,
                                  visibleSize.height/2));
    nextNumItem->setScale(0.35);

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem,prevNumItem,nextNumItem,NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
    
    //auto label = Label::createWithTTF("Chandra Shekar", "fonts/Marker Felt.ttf", 24);
    
    // position the label on the center of the screen
   // label->setPosition(Vec2(origin.x + visibleSize.width/2,
                           // origin.y + visibleSize.height - label->getContentSize().height));

    // add the label as a child to this layer
    //this->addChild(label, 1);
    
    this->createNewNumber(currentNumber);
    
    return true;
}

void HelloWorld::createNewNumber(int i)
{
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    
    
    if (currentNumber==1)
    {
        prevNumItem->setVisible(false);
    }
    else if(currentNumber==9)
    {
        nextNumItem->setVisible(false);
    }
    else
    {
        prevNumItem->setVisible(true);
        nextNumItem->setVisible(true);
    }

    _mySprite = MySprite::create(i);
    // position the sprite on the center of the screen
    _mySprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    addChild(_mySprite,1);
    SCALE_UNIV_SPRTE(_mySprite, 0.75);

}

void HelloWorld::prevNumberCallback(Ref* pSender)
{
    if (currentNumber>1)
    {
        currentNumber = currentNumber - 1;
    }
    else
    {
        currentNumber = 1;
        prevNumItem->setVisible(false);
    }
    if (_mySprite!=nullptr)
    {
        removeChild(_mySprite);
    }
    this->createNewNumber(currentNumber);
}

void HelloWorld::nextNumberCallback(Ref* pSender)
{
    
    if (_mySprite!=nullptr)
    {
        removeChild(_mySprite);
    }
    
    if (currentNumber<9)
    {
        currentNumber = currentNumber + 1;
    }
    else
    {
        currentNumber = 9;
    }
    
    this->createNewNumber(currentNumber);
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->replaceScene(MenuScene::createScene());
}
