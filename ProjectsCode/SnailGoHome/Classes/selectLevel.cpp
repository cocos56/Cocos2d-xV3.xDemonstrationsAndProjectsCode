#include "selectLevel.h"
#include "selectChapter.h"

#include "DataParse.h"
#include "gameScene.h"

Scene *  selectLevel::createScene()
{
	Scene * scene =Scene::create();
	Layer *layer=selectLevel::create();
	scene->addChild(layer);
	return scene;
}
bool selectLevel::init()
{
	if(!Layer::init())
	{
		return false;
	}
   	size=Director::getInstance()->getWinSize();
	//
	Sprite *bg=Sprite::create("bg2.png");
	//auto scalex=size.width/bg->getContentSize().width/2;
	//auto scaley=size.width/bg->getContentSize().height/2;
	//bg->setScale(scalex,scaley);
	bg->setPosition(Vec2(size.width/2,size.height/2));
	this->addChild(bg);
	wo1=Sprite::create("wowo1.png");
	wo1->setPosition(100,size.height-100);
	this->addChild(wo1);
	JumpTo *jumptoRight=JumpTo::create(5,Vec2(size.height-100,size.height-100),20,10);
	JumpTo *jumptoLeft=JumpTo::create(5,Vec2(100,size.height-100),20,10);
	auto  backCall=CallFunc::create(this,callfunc_selector(selectLevel::flip));
	Sequence *seq=Sequence::create(jumptoRight,backCall,jumptoLeft,backCall,NULL);
	wo1->runAction(seq);
	Button * backButton=Button::create("backarrow.png","backarrow.png");
	backButton->setPosition(Vec2(50,size.height-50));
	backButton->addClickEventListener(CC_CALLBACK_0(selectLevel::back,this));
	this->addChild(backButton);
	
	//用ScrollView来实现滑动选取关卡的效果
	scrollView=ScrollView::create();
	Size size2(size.width,size.height/4*3);
	scrollView->setContentSize(size2);
	//设置内容大小为2屏
	scrollView->setInnerContainerSize(Size(size.width*2,size.height/4*3));
	scrollView->setPosition(Vec2(0,0));
	scrollView->setAnchorPoint(Vec2(0,0));
	scrollView->setDirection(ScrollView::Direction::HORIZONTAL);
	this->addChild(scrollView);
	//向scrollview中添加小房子（）
	createLevelItem();
	return true;
}
void selectLevel::createLevelItem()
{
	//点击button的tag值
	int chapter=UserDefault::getInstance()->getIntegerForKey("chapter");
	//根据章chapter，通过DataParse::getChapter(chapter)获取其中的star和lock的值，并存放到字典中，返回一个字典
	__Dictionary * chapterData=DataParse::getChapter(chapter); 
   //根据关卡数拼接出上锁和非上锁图片的名字
	char levelLock[20];
	sprintf(levelLock,"house_lock%d.png",chapter);
	char levelUnlock[20];
	sprintf(levelUnlock,"house%d.png",chapter);
	
	//根据锁的状态值，循环添加6个关卡对应的房子，并根据starNum对应的值，在房子的位置显示星星的图片0getstar.png
	for (int i = 1; i <=6; i++)
	{
		Button *levelBg;//房子
		char lockKey[20];
		sprintf(lockKey,"level_%d_lock",i);
		Integer *lock=(Integer* )chapterData->objectForKey(lockKey);
		int lockValue=lock->getValue();//锁的状态
		switch (lockValue)
		{
		case 0://不上锁图片
			levelBg=Button::create(levelUnlock,levelUnlock);
			levelBg->addClickEventListener(CC_CALLBACK_1(selectLevel::goto_level,this));
			break;
		case 1:
			levelBg=Button::create(levelLock,levelLock);
		default:
			break;
		}
		levelBg->setAnchorPoint(Vec2(0,0));
		//房子的间隔
		float f=(size.width*2-levelBg->getContentSize().width)/5;
		levelBg->setPosition(Vec2((i-1)*f,0));
		levelBg->setTag(i);
		auto starImage=Sprite::create();
		starImage->setPosition(levelBg->getContentSize().width/2,50);
		char starKey[20];
		sprintf(starKey,"level_%d_star",i);
		Integer * star=(Integer *)chapterData->objectForKey(starKey);
		int starValue=star->getValue();
		switch (starValue)
		{
		case 0:
			starImage->setTexture("0getstar.png");
			break;
		case 1:
			starImage->setTexture("1getstar.png");
			break;
		case 2:
			starImage->setTexture("2getstar.png");
			break;
		case 3:
			starImage->setTexture("3getstar.png");
			break;
		default:
			break;
		}
		levelBg->addChild(starImage);
		scrollView->addChild(levelBg);
	}

}
 void selectLevel::goto_level(Ref *sender)
{
	Button *button=(Button *)sender;
	int levelNum=button->getTag();
	UserDefault::getInstance()->setIntegerForKey("level",levelNum);
	//根据	levelNum的值选择该关卡对应的游戏场景布局效果图
	Scene *scene=gameScene::createScene();
	Director::getInstance()->replaceScene(scene);

}
void  selectLevel::flip()
{
	if(wo1->isFlipX())
	{
		//恢复原来的状态
		wo1->setFlipX(false);
		//wo1->setFlipX(-1);
	}
	else
	{
		//翻转
		wo1->setFlipX(true);
	}
}
void selectLevel::back( )
{
	Scene *scene=SelectChapter::createScene();
	Director::getInstance()->replaceScene(scene);
}