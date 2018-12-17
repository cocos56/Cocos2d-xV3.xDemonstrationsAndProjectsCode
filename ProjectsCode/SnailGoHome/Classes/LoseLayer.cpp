#include "LoseLayer.h"
#include "SimpleAudioEngine.h"
#include "ui/CocosGUI.h"
#include "GameScene.h"
#include "SelectChapter.h"

using namespace ui;
using namespace CocosDenshion;

bool LoseLayer::init()
{
	if (!LayerColor::init())
	{
		return false;
	}
	size = Director::getInstance()->getWinSize();
	this->initWithColor(Color4B(100,100,100,100));

	this->setTouchEnabled(true);//设置可触摸
	this->setContentSize(Size(size.width,size.height));

	Sprite* loseBg = Sprite::create("succeed.png");
	loseBg->setPosition(Vec2(size.width/2,size.height/2));
	this->addChild(loseBg);

	//从UserDefault.xml中获取游戏音效设置的状态，若开启音效则播放失败音效。
	if (!UserDefault::getInstance()->getBoolForKey("onEffect"))
	{
		SimpleAudioEngine::getInstance()->playEffect("lose.wav",false);
	}
	
	Label* label = Label::createWithSystemFont("Regret,you lose!","",30);
	label->setColor(Color3B(100,100,100));
	label->setPosition(Vec2(size.width/2,size.height/2+100));
	this->addChild(label);

	Node* node = Node::create();
	node->setPosition(Vec2(size.width/2,size.height/2-50));
	this->addChild(node);

	Button* button1 = Button::create("again.png","again.png");
	button1->setPosition(Vec2(-50,0));
	button1->setTag(1);
	button1->addClickEventListener(CC_CALLBACK_1(LoseLayer::clickButton,this));
	node->addChild(button1);

	Button* button2 = Button::create("menu.png","menu.png");
	button2->setPosition(Vec2(50,0));
	button2->setTag(2);
	button2->addClickEventListener(CC_CALLBACK_1(LoseLayer::clickButton,this));
	node->addChild(button2);

	return true;
}
void LoseLayer::clickButton(Ref* sender)
{
	Button* button = (Button*)sender;
	Scene* scene;
	switch (button->getTag())
	{
	case 1:
		scene = gameScene::createScene();
		Director::getInstance()->replaceScene(scene);
		break;

	case 2:
		scene = SelectChapter::createScene();
		Director::getInstance()->replaceScene(scene);
		break;

	default:
		break;
	}

}