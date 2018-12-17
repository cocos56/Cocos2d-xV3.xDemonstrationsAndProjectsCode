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
    // 创建精灵对象（英雄）
    auto hero = Sprite::create("10001.png");
    // 设置精灵对象（英雄）位置为屏幕正中
    hero->setPosition(Vec2(visibleSize.width/2,visibleSize.height/2));
    // 把精灵对象（英雄）添加为HelloWorldLayer层的子节点。
    this->addChild(hero);
    // ①创建动画对象，它是将动画帧元素的集合对象，决定了动画帧的播放顺序以及时间间隔
    auto animation = Animation::create();
    // ②循环使用单张图片来创建动画帧
    for( int i=46;i<=55;i++)
    {
        // 将单张图片添加为精灵帧（即动画帧）
        animation->addSpriteFrameWithFile(StringUtils::format("100%d.png",i));
    }
    // 设置动画播放的属性，3秒/15帧
    animation->setDelayPerUnit(3.0f/3.0f);
    // 让精灵对象在动画执行完后恢复到最初状态
    animation->setRestoreOriginalFrame(true);
    // ③创建动画动作
    auto animate = Animate::create(animation);
    // ④精灵对象（英雄）执行动画动作
    hero->runAction(animate);
    
    return true;
}



