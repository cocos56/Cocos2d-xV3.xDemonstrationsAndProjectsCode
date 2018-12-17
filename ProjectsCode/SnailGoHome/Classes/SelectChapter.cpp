#include "SelectChapter.h"
#include "ui/cocosGUI.h"
using namespace ui;
#include  "StartScene.h"
#include "SimpleAudioEngine.h"
using namespace CocosDenshion;
#include "selectLevel.h"

Scene *  SelectChapter::createScene()
{
	Scene * scene =Scene::create();
	Layer *layer=SelectChapter::create();
	scene->addChild(layer);
	return scene;
}
bool SelectChapter::init()
{
	if(!Layer::init())
	{
		return false;
	}
	auto size=Director::getInstance()->getWinSize();
	Sprite *bg=Sprite::create("bg2.png");
	bg->setPosition(Vec2(size.width/2,size.height/2));
	this->addChild(bg);
	Button *backButton=Button::create("backarrow.png","backarrow.png");
	backButton->setPosition(Vec2(50,size.height - 50));
	backButton->addClickEventListener(CC_CALLBACK_0(SelectChapter::back,this));
	addChild(backButton);

	/*添加3个图片按钮，并把按钮添加到node节点中，再把node节点加到当前层中，并让节点执行跳跃动作，
	设置tag的目的是为了在执行回调时通过获取tag值，并把它保存到UserDefault.xml文件中，
	在调用Director::getInstance()->replaceScene(selectLevel::createScene());生成选关场景时，
	从UserDefault.xml文件中取出来，用来选择某一关的场景。
	*/
	auto node=Node::create();
	node->setPosition(Vec2(size.width/2,size.height/2));
	Button *chaper1=Button::create("scene11.png","scene11.png");
	chaper1->setTag(1);
	chaper1->setPosition(Vec2(-250,0));
	chaper1->addClickEventListener(CC_CALLBACK_1(SelectChapter::goto_chapter,this));
	Button *chaper2=Button::create("scene22.png","scene22.png");
	chaper2->setTag(2);
	chaper2->setPosition(Vec2(0,0));
	chaper2->addClickEventListener(CC_CALLBACK_1(SelectChapter::goto_chapter,this));
	Button *chaper3=Button::create("scene33.png","scene33.png");
	chaper3->setTag(3);
	chaper3->setPosition(Vec2(250,0));
	chaper3->addClickEventListener(CC_CALLBACK_1(SelectChapter::goto_chapter,this));
	node->addChild(chaper1);
	node->addChild(chaper2);
	node->addChild(chaper3);
	this->addChild(node);
	//时间，位置，高度，次数，产生跳跃的动作
	JumpTo *jumpTo=JumpTo::create(1,Vec2(size.width/2,size.height/2-20),50,2);
	node->runAction(jumpTo);
	return true;
}
void SelectChapter::back()
{
	Scene * scene=StartScene::createScene();
	Director::getInstance()->replaceScene(scene);
}

void SelectChapter::goto_chapter(Ref *sender)
{
	Button *button=(Button *)sender;
	int tag=button->getTag();
	//章节信息用的也比较少，所以放到userdefault.xml中,而且数据不需要修改
	UserDefault::getInstance()->setIntegerForKey("chapter",tag);
	Director::getInstance()->replaceScene(selectLevel::createScene());
}
