#include "touchesTest.h"


touchesTest::touchesTest(void)
{
}
touchesTest::~touchesTest(void)
{
}

Scene * touchesTest::createScene()
{
	auto scene = Scene::create();
	auto layer = Layer::create();
	scene->addChild(layer);
	return scene;
}
bool touchesTest::init()
{
	if (!Layer::init())
	{
		return false;
	}

	auto sp = Sprite::create("bg.jpg");
	sp->setPosition(240, 160);
	this->addChild(sp);
	// 1:获取触摸事件分发器（事件管理中心）
	auto dispatcher = Director::getInstance()->getEventDispatcher();

	//2:创建多点触摸监听者,按alter键并单击鼠标就可在模拟器上出现两个点
	auto  touchesListener = EventListenerTouchAllAtOnce::create();
	/*吞噬触摸，若两个layer都接收到触摸事件，则上面的将吞噬掉下面的，
	使下面的层监听不到触摸事件。多点触摸不能用*/
	// touchListener->setSwallowTouches(true);
	//3:设置触摸开始时的函数回调
	touchesListener->onTouchesBegan = CC_CALLBACK_2(touchesTest::onTouchesBegan, this);
	touchesListener->onTouchesMoved = CC_CALLBACK_2(touchesTest::onTouchesMoved, this);
	touchesListener->onTouchesEnded = CC_CALLBACK_2(touchesTest::onTouchesEnded, this);
	touchesListener->onTouchesCancelled = CC_CALLBACK_2(touchesTest::onTouchesCancelled, this);
	//4：添加事件监听者到事件分发中心
	dispatcher->addEventListenerWithSceneGraphPriority(touchesListener, this);

	true;
}
void touchesTest::onTouchesBegan(const std::vector<Touch*>& touches, Event *unused_event)
{
	/*1:迭代器（iterator）是一种对象，它能够用来遍历标准模板库容器中的部分或全部元素，
	 每个迭代器对象代表容器中的确定的地址。迭代器修改了常规指针的接口，
	 所谓迭代器是一种概念上的抽象：那些行为上像迭代器的东西都可以叫做迭代器。
	 然而迭代器有很多不同的能力，它可以把抽象容器和通用算法有机的统一起来。
	 迭代器提供对一个容器中的对象的访问方法，并且定义了容器中对象的范围。
	 迭代器就如同一个指针。事实上，C++的指针也是一种迭代器。
	 但是，迭代器不仅仅是指针，因此你不能认为他们一定具有地址值。
	 2:begin和end操作
	 每种容器都定义了一队命名为begin和end的函数，用于返回迭代器。
	 如果容器中有元素的话，由begin返回的元素指向第一个元素。
	 vector<int>::iterator iter=v.begin();若v不为空，iter指向v[0]。
	 由end返回的迭代器指向最后一个元素的下一个，不存在.
	 若v为空，begin和end返回的相同。*iter=0;iter++即将迭代器向前移动一个位置,
	 即将v[0]赋值为0,由end返回的不允许进行解操作。
	 ==和!=操作符来比较两个迭代器，若两个迭代器指向同一个元素，则它们相等，否则不相等。
*/
//有几个手指触摸屏幕将会在屏幕上触摸的位置绘制几个bird精灵。
	log("%d", (int)touches.size());
	auto itor = touches.begin();//C++第七章，模板库的迭代器
	for (; itor != touches.end(); itor++)
	{
		auto touch = (Touch*)(*itor);
		Vec2 pos = touch->getLocation();
		log("(%f,%f)", pos.x, pos.y);
		auto birdSprite = Sprite::create("bird.png");
		birdSprite->setPosition(pos);
		this->addChild(birdSprite);
	}
}
void touchesTest::onTouchesMoved(const std::vector<Touch*>& touches, Event *unused_event)
{
	log("onTouchesMoved");
}
void touchesTest::onTouchesEnded(const std::vector<Touch*>& touches, Event *unused_event)
{
	log("onTouchesEnded");
}
void touchesTest::onTouchesCancelled(const std::vector<Touch*>&touches, Event *unused_event)
{
	log("onTouchesCancelled");
}