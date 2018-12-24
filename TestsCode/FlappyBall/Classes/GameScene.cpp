#include "GameScene.h"
#include "SimpleAudioEngine.h"

Scene* GameScene::createScene()
{
    return GameScene::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool GameScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
	Size windowSize = getContentSize();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(GameScene::menuCloseCallback, this));

    if (closeItem == nullptr ||
        closeItem->getContentSize().width <= 0 ||
        closeItem->getContentSize().height <= 0)
    {
        problemLoading("'CloseNormal.png' and 'CloseSelected.png'");
    }
    else
    {
        float x = origin.x + visibleSize.width - closeItem->getContentSize().width/2;
        float y = origin.y + closeItem->getContentSize().height/2;
        closeItem->setPosition(Vec2(x,y));
    }

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label

    auto label = Label::createWithTTF("Bappy Ball", "fonts/Marker Felt.ttf", 24);
    if (label == nullptr)
    {
        problemLoading("'fonts/Marker Felt.ttf'");
    }
    else
    {
        // position the label on the center of the screen
        label->setPosition(Vec2(origin.x + visibleSize.width/2,
                                origin.y + visibleSize.height - label->getContentSize().height));

        // add the label as a child to this layer
        this->addChild(label, 1);
    }

    // add background
    bg = Sprite::create("bg.png");
	//bg->setScale(0.5);
    if (bg == nullptr)
    {
        problemLoading("'bg.png'");
    }
    else
    {
        // position the sprite on the center of the screen
        bg->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

        // add the sprite as a child to this layer
        this->addChild(bg, 0);
    }

	ball = Sprite::create("ball.png");
	ball->setScale(0.5);
	if (ball == nullptr)
	{
		problemLoading("'ball.png'");
	}
	else
	{
		// position the sprite on the center of the screen
		ball->setPosition(Vec2(visibleSize.width / 2 + origin.x, windowSize.height/2));
		ball->setAnchorPoint(Vec2(0, 0));

		// add the sprite as a child to this layer
		this->addChild(ball, 1);
	}

	obstacle = Sprite::create("obstacle.png");
	obstacle->setScale(0.5);
	if (obstacle == nullptr)
	{
		problemLoading("'obstacle.png'");
	}
	else
	{
		// position the sprite on the center of the screen
		obstacle->setAnchorPoint(Vec2(1, 0));
		obstacle->setPosition(Vec2(visibleSize.width / 3 + origin.x, visibleSize.height / 2 + origin.y));

		// add the sprite as a child to this layer
		this->addChild(obstacle, 1);
	}

	auto obstacle2 = Sprite::create("obstacle.png");
	obstacle2->setAnchorPoint(Vec2(1, 1));
	obstacle2->setScale(0.5);
	obstacle2->setFlippedY(true);
	if (obstacle2 == nullptr)
	{
		problemLoading("'obstacle.png'");
	}
	else
	{
		// position the sprite on the center of the screen
		obstacle2->setPosition(Vec2(visibleSize.width / 3 + origin.x+100, visibleSize.height / 2 + origin.y));

		// add the sprite as a child to this layer
		this->addChild(obstacle2, 1);
	}

	bh = Sprite::create("bh.png");
	bh->setScale(0.5);
	if (bh == nullptr)
	{
		problemLoading("'bh.png'");
	}
	else
	{
		// position the sprite on the center of the screen
		bh->setAnchorPoint(Vec2(0.5, 0.5));
		bh->setPosition(Vec2(visibleSize.width + origin.x-200, visibleSize.height / 2 + origin.y));

		// add the sprite as a child to this layer
		this->addChild(bh, 0);
	}
	listenKeyboardEvent();
	vy = 6;
	g = -0.25;
	schedule(schedule_selector(GameScene::updateBallPosition, 1));
    return true;
}


void GameScene::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    #if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif

    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() and exit(0) as given above,instead trigger a custom event created in RootViewController.mm as below*/

    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);


}

void GameScene::listenKeyboardEvent()
{
	auto listener = EventListenerKeyboard::create();
	listener->onKeyPressed = CC_CALLBACK_2(GameScene::onKeyPressed2, this);
	listener->onKeyReleased = CC_CALLBACK_2(GameScene::onKeyReleased2, this);

	this->_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}

void GameScene::onKeyPressed2(EventKeyboard::KeyCode code, Event *evt)
{
	if (code == EventKeyboard::KeyCode::KEY_J)
	{
		vy = 6;
		g = -0.25;
	}
}
void GameScene::onKeyReleased2(EventKeyboard::KeyCode code, Event *evt)
{
	if (code == EventKeyboard::KeyCode::KEY_J)
	{
	}
}

void GameScene::updateBallPosition(float dt)
{
	if (ball->getPositionY() <= 0)
	{
		vy = 12;
		g = -0.25;
	}
	ball->setPositionY(ball->getPositionY() + vy);
	vy += g;
	ball->setPositionX(ball->getPositionX() + 1);
}