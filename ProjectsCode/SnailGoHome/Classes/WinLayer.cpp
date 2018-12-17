#include "WinLayer.h"
#include "ui/CocosGUI.h"
using namespace ui;

#include "gameScene.h"
#include "SelectChapter.h"
#include "DataParse.h"
#include "SimpleAudioEngine.h"
using namespace CocosDenshion;

int WinLayer::win_star = 0;//初始化
bool WinLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}
	size = Director::getInstance()->getWinSize();
	this->initWithColor(Color4B(100,100,100,100));

	this->setTouchEnabled(true);//设置可触摸
	this->setContentSize(Size(size.width,size.height));

	Sprite* winSp = Sprite::create("succeed.png");
	winSp->setPosition(Vec2(size.width/2,size.height/2));
	this->addChild(winSp);

	if (!UserDefault::getInstance()->getBoolForKey("onEffect"))
	{
		SimpleAudioEngine::getInstance()->playEffect("win.wav",false);
	}

	//自定义粒子效果
	auto quad = ParticleSystemQuad::create("xingxing.plist");
	quad->setPosition(Vec2(size.width/2,size.height/2+50));
	quad->setDuration(2);//播放次数
	this->addChild(quad);

	int levelNum = UserDefault::getInstance()->getIntegerForKey("level");
	if(levelNum == 6 && win_star == 3)
	{
		Label* label = Label::createWithSystemFont("You have Win, Play next chapter","",30);
		label->setColor(Color3B(100,100,100));
		label->setPosition(Vec2(size.width/2,size.height/2+100));
		this->addChild(label);
	}

	//在成功面板上添加星星数量
	for (int i = 1;i <= win_star;i++)
	{
		Sprite* starSp = Sprite::create("star2.png");
		starSp->setScale(.5);
		starSp->setPosition(Vec2(size.width/2-100+50*i,size.height/2+200));
		this->addChild(starSp);
	}

	Node* node = Node::create();
	node->setPosition(Vec2(size.width/2,size.height/2-50));
	this->addChild(node);

	Button* again = Button::create("again.png","again.png");
	again->setPosition(Vec2(-100,0));
	again->setTag(1);
	again->addClickEventListener(CC_CALLBACK_1(WinLayer::clickButton,this));
	node->addChild(again);

	Button* next = Button::create("next.png","next.png");
	next->setPosition(Vec2(0,0));
	next->setTag(2);
	next->addClickEventListener(CC_CALLBACK_1(WinLayer::clickButton,this));
	node->addChild(next);

	Button* menu = Button::create("menu.png","menu.png");
	menu->setPosition(Vec2(-100,0));
	menu->setTag(3);
	menu->addClickEventListener(CC_CALLBACK_1(WinLayer::clickButton,this));
	node->addChild(menu);

	if (levelNum == 6)
	{
		next->removeFromParent();
	}

	return true;
}

void WinLayer::clickButton(Ref* sender)
{
	Button* button = (Button*)sender;
	Scene* scene;
	//从UserDefault.xml中获取当前游戏的章节数和关卡数
	int chapternum = UserDefault::getInstance()->getIntegerForKey("chapter");
	int levelNum = UserDefault::getInstance()->getIntegerForKey("level");
	//根据当前游戏的章节数和关卡数，从json文件中获取对应的星星数给变量starNum
	int starNum = DataParse::getStar(chapternum,levelNum);
	switch (button->getTag())
	{
	case 1://点击again按钮，重新玩
		scene = gameScene::createScene();
		Director::getInstance()->replaceScene(scene);
		break;

	case 2://点击next按钮
		if (starNum ==3 && levelNum <6)//吃掉三颗星（蜗牛与三颗星都碰撞）,双等号用来判断是否等于3，但关卡数小于6，则进入该章的下一关
		{
			//把关卡数加1，再存入UserDefault.xml中
			UserDefault::getInstance()->setIntegerForKey("level",levelNum + 1);
			/*gameScene类在初始化场景时，通过执行语句int levelNum=UserDefault::getInstance()->getIntegerForKey("level");
			把上一行语句存入到UserDefault.xml中的加1之后的关卡数取出给变量levelNum，然后根据levelNum选用相应的关卡界面。
			*/
			scene = gameScene::createScene();
			Director::getInstance()->replaceScene(scene);
		}		
		else if(starNum < 3 && levelNum < 6)//吃掉星星数小于3（蜗牛碰撞的星星数小于3），且关卡数小于6，则提示“Can't go to next level!”,不能进入该章的下一关
		//else
		{
			Label* lable = Label::createWithSystemFont("Can't go to next level!","",30);
			lable->setColor(Color3B(100,100,100));
			lable->setPosition(Vec2(size.width/2,size.height/2+100));
			this->addChild(lable);
		}
		break;

	case 3://点击选择菜单按钮，从新选择章
		scene = SelectChapter::createScene();
		Director::getInstance()->replaceScene(scene);
		break;

	default:
		break;
	}
}

void WinLayer::setstarNum(int starNum)
{
	win_star = starNum;
}