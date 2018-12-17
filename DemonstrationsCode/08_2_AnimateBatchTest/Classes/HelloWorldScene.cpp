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
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    // ①获取精灵帧缓存的单例对象，并读取animation.plist文件将精灵帧纹理添加到精灵帧缓存当中
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("animation.plist");
    // ②使用精灵帧缓存中的精灵创建一个动画，并设置属性
    auto animation = Animation::create();
    // 循环从精灵帧缓存中获取与图片名称相对应的精灵帧组成动画
    for(int i = 1;i<=8;i++){
        std::string szName = StringUtils::format("z_00_0%d.png", i);
        // 将单张图片添加为精灵帧（即动画帧）
        animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(szName));
    }
    // 设置动画播放的属性，3秒/15帧
	animation->setDelayPerUnit(3.0f/15.0f);
	// 让精灵对象在动画执行完后恢复到最初状态
	animation->setRestoreOriginalFrame(true);
    // ③用动画帧缓冲AnimationCache缓存所有动画和动画帧
    AnimationCache::getInstance()->addAnimation(animation, "walk");
    
    // ④创建背景精灵添加到当前层
    auto bgSprite = Sprite::createWithSpriteFrameName("gamebg.png");
    bgSprite->setPosition(Vec2(visibleSize.width/2,visibleSize.height/2));
    this->addChild(bgSprite);
    // ⑤创建僵尸精灵，设置坐标位置在屏幕之外，并添加到当前层
    auto zSprite = Sprite::createWithSpriteFrameName("z_00_01.png");
    zSprite->setPosition(Vec2(visibleSize.width+zSprite->getContentSize().width/2,visibleSize.height/2));
    this->addChild(zSprite);
    // ⑥从动画帧缓冲AnimationCache中获取之前缓存的动画
    auto walk = AnimationCache::getInstance()->getAnimation("walk");
    // ⑦创建动画动作
	auto animate = Animate::create(walk);
	// 创建一个重复动作，重复执行Animate动画动作
	auto repeatanimate = RepeatForever::create(animate);
	// 定义一个移动动作，让精灵对象从屏幕右边移动到屏幕左边
	auto moveTo = MoveTo::create(10.f, Vec2(-zSprite->getContentSize().width/2, visibleSize.height/2));
	// ⑧僵尸精灵执行重复动作（包含动画动作）和移动动作，执行效果是僵尸从屏幕的右边走到屏幕的左边
	zSprite->runAction(repeatanimate);
	zSprite->runAction(moveTo);
    
    return true;
}


