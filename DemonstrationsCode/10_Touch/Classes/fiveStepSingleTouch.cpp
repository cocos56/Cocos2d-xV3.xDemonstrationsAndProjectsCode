#include "fiveStepSingleTouch.h"


fiveStepSingleTouch::fiveStepSingleTouch(void)
{
}
fiveStepSingleTouch::~fiveStepSingleTouch(void)
{
}

Scene* fiveStepSingleTouch::createScene()
{
	auto scene = Scene::create();
	auto layer = fiveStepSingleTouch::create();
	scene->addChild(layer);
	return scene;
}

bool fiveStepSingleTouch::init()
{
	if (!Layer::init())
	{
		return false;
	}

	return true;
}
void fiveStepSingleTouch::onEnter()
{
	Layer::onEnter();//当层进入舞台时调用onEnter函数，
		//设置层layer的位置触摸事件发生时，将会导致触摸点偏移，触摸事件中添加的精灵也会随着偏移
	this->setPosition(100, 100);
	log("onEnter is executed!");
	auto sp = Sprite::create("bg.jpg");
	sp->setPosition(240, 160);
	this->addChild(sp);
	// ①获取触摸事件分发器（事件管理中心）
	auto dispatcher = Director::getInstance()->getEventDispatcher();
	//② 创建单点触摸监听者（即创建一个单点触摸事件监听器），处理触摸事件逻辑
	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->setSwallowTouches(true);//吞噬触摸，若两个layer都接收到触摸事件，则上面的将吞噬掉下面的，使下面的层监听不到触摸事件。
	//③绑定响应事件函数，或设置触摸的函数回调
	touchListener->onTouchBegan = CC_CALLBACK_2(fiveStepSingleTouch::onTouchBegan, this);
	touchListener->onTouchMoved = CC_CALLBACK_2(fiveStepSingleTouch::onTouchMoved, this);
	touchListener->onTouchEnded = CC_CALLBACK_2(fiveStepSingleTouch::onTouchEnded, this);
	touchListener->onTouchCancelled = CC_CALLBACK_2(fiveStepSingleTouch::onTouchCancelled, this);
	//④将监听器添加到事件分发器dispatcher中
	dispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
}
void fiveStepSingleTouch::onExit()
{
	Layer::onExit();//当层退出舞台时调用onExit函数
	log("onExit is executed! ");
	auto dispatcher = Director::getInstance()->getEventDispatcher();
	dispatcher->removeEventListenersForTarget(this);
}
//⑤编写回调响应函数。
bool fiveStepSingleTouch::onTouchBegan(Touch *touch, Event *unused_event)
{
	log("begin");
	return true; //表示接受这次触摸事件
   // return false;//设置为false，表示不接受这次触摸事件，则无法向下传递，没法显示触摸，
}
void fiveStepSingleTouch::onTouchMoved(Touch *touch, Event *unused_event)
{
	//log("move");下面代码的含义是触摸屏幕就会添加精灵，
	Vec2 position = touch->getLocation();//得到当前的触摸点的OpenGL坐标
	//touch->getPreviousLocation()//得到前一个触摸点的坐标
	position = this->convertToNodeSpace(position);
	//为 this->setPosition(100,100); 而转换，这样触摸事件中添加精灵时就不会偏移，鼠标点击什么地方就在该地方画图
	auto sprite = Sprite::create("bird.png");
	sprite->setScale(0.5);
	sprite->setPosition(position);
	this->addChild(sprite);
}

void fiveStepSingleTouch::onTouchEnded(Touch *touch, Event *unused_event)
{
	log("end");
}
void fiveStepSingleTouch::onTouchCancelled(Touch *touch, Event *unused_event)
{
	log("cancel");
}