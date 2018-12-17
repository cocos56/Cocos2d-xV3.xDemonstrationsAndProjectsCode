#include "fixedPriority.h"
#include "spriteTouch.h"
USING_NS_CC;

fixedPriority::fixedPriority(void)
{
}


fixedPriority::~fixedPriority(void)
{
}


Scene* fixedPriority::createScene()
{
    // 创建一个场景对象，该对象将会由自动释放池管理内存的释放
    auto scene = Scene::create();
    
    // 创建层对象，该对象将会由自动释放池管理内存的释放
    auto layer = fixedPriority::create();
    
    // 将HelloWorld层作为子节点添加到场景
    scene->addChild(layer);
    
    // 返回场景对象
    return scene;
}

// on "init" you need to initialize your instance
bool fixedPriority::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    // 获得设备支持的可见OpenGL视图大小（即窗口大小）。
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    // 关闭菜单
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(fixedPriority::menuCloseCallback, this));
    
	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));

    // 创建菜单
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    // 标题标签
    auto title = Label::createWithSystemFont("touch oneByeone fixed Priority Test", "",25);
    title->setPosition(visibleSize.width/2, visibleSize.height*0.9);
    this->addChild(title);
    
    // 提示标签
    auto subtitle = Label::createWithSystemFont("Please click block!", "", 18);
    subtitle->setPosition(visibleSize.width/2, visibleSize.height*0.75);
    this->addChild(subtitle);
    
    // 使用之前设计的TouchableSpriteWithFixedPriority类创建精灵对象
    auto sprite1 = spriteTouch::create();
    // 设置纹理图片
	//sprite1->initWithFile("CyanSquare.png");
	sprite1->setTexture("CyanSquare.png");
    // 设置优先级别和名称
    sprite1->setPriority(2,"CyanSquare");

    sprite1->setPosition(Vec2(visibleSize.width/2, visibleSize.height/2) + Vec2(-80, 40));
    this->addChild(sprite1,3);
    
    // 使用之前设计的TouchableSpriteWithFixedPriority类创建精灵对象
    auto sprite2 = spriteTouch::create();
    sprite2->setTexture("MagentaSquare.png");
    sprite2->setPriority(3,"MagentaSquare");
    sprite2->setPosition(Vec2(visibleSize.width/2, visibleSize.height/2));
    this->addChild(sprite2, 2);
    
    // 使用之前设计的TouchableSpriteWithFixedPriority类创建精灵对象
    auto sprite3 = spriteTouch::create();
    sprite3->setTexture("YellowSquare.png");
    sprite3->setPriority(1,"YellowSquare");
    sprite3->setPosition(Vec2::ZERO);
    sprite2->addChild(sprite3, 1);    
    return true;
}


void fixedPriority::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif

    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

