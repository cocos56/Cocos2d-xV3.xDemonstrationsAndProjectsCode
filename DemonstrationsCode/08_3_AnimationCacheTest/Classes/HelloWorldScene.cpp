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
    // ①获取精灵帧缓存的单例对象，并读取grossini.plist文件将精灵帧纹理添加到精灵帧缓存当中
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("grossini.plist");
    // 创建精灵对象（舞蹈者）
    auto dance = Sprite::create("grossini_dance_01.png");
	// 设置精灵对象（舞蹈者）位置为屏幕正中
	dance->setPosition(Vec2(visibleSize.width/2,visibleSize.height/2));
	// 把精灵对象（舞蹈者）添加为HelloWorldLayer层的子节点。
	this->addChild(dance);
    // ②创建动画帧缓冲并向缓冲区中添加动画文件
    AnimationCache::getInstance()->addAnimationsWithFile("animations.plist");
    // ③从缓冲区中获取文件中设定的名称为“dance_1”的动画对象。
    auto animation = AnimationCache::getInstance()->getAnimation("dance_1");
    // ④根据动画对象创建动画动作
    auto animate = Animate::create(animation);
    // ⑤精灵对象（舞蹈者）执行动画动作
    dance->runAction(animate);
    
    return true;
}


