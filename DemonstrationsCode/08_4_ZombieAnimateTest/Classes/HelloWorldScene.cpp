#include "HelloWorldScene.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    // 创建一个场景对象，该对象将会由自动释放池管理内存的释放
    auto scene = Scene::create();
    
    // 创建层对象，该对象将会由自动释放池管理内存的释放
    auto layer = HelloWorld::create();
    
    // 将HelloWorld层作为子节点添加到场景
    scene->addChild(layer);
    
    // 返回场景对象
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    // 调用父类的init函数
    if ( !Layer::init() )
    {
        return false;
    }
    
    // 获得OpenGL ES视图的大小
    Size visibleSize = Director::getInstance()->getVisibleSize();
    // 使用背景图片bg.png创建一个精灵，初始位置偏移是(0,0)。
    auto bgSprite = Sprite::create("bg.png");
    // 设置背景图片位置为屏幕正中
    bgSprite->setPosition(Vec2(visibleSize.width/2,visibleSize.height/2));
    // 把背景图片精灵添加为HelloWorldLayer层的子节点。
    this->addChild(bgSprite);
    // 创建精灵对象（僵尸）
    auto zSprite = Sprite::create("z_00_01.png");
    // 设置坐标位置在屏幕之外
    zSprite->setPosition(Vec2(visibleSize.width+zSprite->getContentSize().width/2,visibleSize.height/2));
    // 把精灵对象（僵尸）添加为HelloWorldLayer层的子节点。
    this->addChild(zSprite);
    // ①创建动画对象，它是将动画帧元素的集合对象，决定了动画帧的播放顺序以及时间间隔
    auto animation = Animation::create();
    // ②循环使用单张图片来创建动画帧
    for( int i=1;i<8;i++)
    {
        // 将单张图片添加为精灵帧（即动画帧）
        animation->addSpriteFrameWithFile(StringUtils::format("z_00_0%d.png",i));
    }
    // 设置动画播放的属性，3秒/15帧
    animation->setDelayPerUnit(3.0f/15.0f);
    // 让精灵对象在动画执行完后恢复到最初状态
    animation->setRestoreOriginalFrame(true);
    // ③创建动画动作
    auto animate = Animate::create(animation);
    // 创建一个重复动作，重复执行Animate动画动作
    auto repeatanimate = RepeatForever::create(animate);
    // 定义一个移动动作，让精灵对象从屏幕右边移动到屏幕左边
    auto moveTo = MoveTo::create(10.f, Vec2(-zSprite->getContentSize().width/2, visibleSize.height/2));
    // ④僵尸精灵执行重复动作（包含动画动作）和移动动作，执行效果是僵尸从屏幕的右边走到屏幕的左边
    zSprite->runAction(repeatanimate);
    zSprite->runAction(moveTo);
    
    return true;
}



