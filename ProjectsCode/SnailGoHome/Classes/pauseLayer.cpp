#include "pauseLayer.h"
#include "ui\CocosGUI.h"
using namespace ui;
#include "gameScene.h"
#include "SelectChapter.h"
pauseLayer::pauseLayer(void)
{
}
pauseLayer::~pauseLayer(void)
{
}
bool pauseLayer::init()
{
	if(!Layer::init())
  {
	  return false; //这里必须为false，后面必须为true，否则出现pauseLayer场景创建错误，可以把它改为true，该方法结束的地方改为false，查看错误
  }
	Size  size=Director::getInstance()->getWinSize();
	this->initWithColor(Color4B(180,180,180,70));
	this->setTouchEnabled(true);
	this->setContentSize(Size(size.width,size.height));
	Sprite *bg=Sprite::create("green.jpg");
	bg->setAnchorPoint(Vec2(0,0));
	bg->setPosition(Vec2(size.width- bg->getContentSize().width,size.height-bg->getContentSize().height));
	this->addChild(bg);
	Node *node=Node::create();
	node->setPosition(bg->getContentSize().width/2,bg->getContentSize().height/2);
	//切忌，不能把一个节点添加到自身节点上，如果添加到自身则出现死循环，界面不变化
	bg->addChild(node);

	Button *again=Button::create("again.png","again.png");
	again->setPosition(Vec2(0,100));//把该按钮放置在节点的位置向上偏移100的位置上，这里充分体现了setpositon（）方法中的值为与父节点的相对偏移量，即采用的是节点坐标系
	again->setTag(1);
	again->addClickEventListener(CC_CALLBACK_1(pauseLayer::clickButton,this));
	node->addChild(again);

	Button *continue_Button=Button::create("continue.png","continue.png");
	continue_Button->setPosition(Vec2(0,0));//表示该按钮与父节点node的相对位置偏移量为0，即把该按钮放置在节点的位置上
	continue_Button->setTag(2);
	continue_Button->addClickEventListener(CC_CALLBACK_1(pauseLayer::clickButton,this));
	node->addChild(continue_Button);

	Button *menu_Button=Button::create("menu.png","menu.png");
	menu_Button->setPosition(Vec2(0,-100));//把该按钮放置在节点的位置向下偏移100的位置上
	menu_Button->setTag(3);
	menu_Button->addClickEventListener(CC_CALLBACK_1(pauseLayer::clickButton,this));
	node->addChild(menu_Button);
  return true;
}
	
void pauseLayer::clickButton(Ref *sender)
{
	Button *button=(Button*)sender;
	Scene *scene=Scene::create();
	int chapter=UserDefault::getInstance()->getIntegerForKey("chapter");
	int level=UserDefault::getInstance()->getIntegerForKey("level");
	switch (button->getTag())
	{
	case 1:
		Director::getInstance()->resume();//恢复暂停，重玩游戏，
		scene=gameScene::createScene();
		Director::getInstance()->replaceScene(scene);
		break;
	case 2:
		Director::getInstance()->resume();
		Director::getInstance()->getEventDispatcher()->resumeEventListenersForTarget(this->getParent());
		this->removeFromParent();
		break;
	case 3:
		Director::getInstance()->resume();
		scene=SelectChapter::createScene();
		Director::getInstance()->replaceScene(scene);
		break;
	default:
		break;
	}
}