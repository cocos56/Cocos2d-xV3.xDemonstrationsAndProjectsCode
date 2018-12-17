#include "gameScene.h"
//cocosStudio界面布局的msb或exportJson文件
//#include "editor-support/cocostudio/ActionTimeline/CSLoader.h"
#include "editor-support\cocostudio\ActionTimeline\CSLoader.h"
#include "cocostudio/CocoStudio.h"
using namespace cocostudio;

#include "DataParse.h"

#include "ui/CocosGUI.h"
using namespace ui;

#include "selectLevel.h"

#include "SimpleAudioEngine.h"
using namespace CocosDenshion;

#include"WinLayer.h"
#include"LoseLayer.h"
#include "pauseLayer.h"


Scene * gameScene::createScene()
{
	//创建一个世界 
	auto scene=Scene::createWithPhysics();
	auto layer=gameScene::create();
	// 巧妙使用auto，自动追踪类型，也可以直接使用注明具体类型（gameScene *）
	//gameScene *layer=gameScene::create();
	//得到一个物理世界并且设置物理世界的属性
	layer->setPhysicsWorld(scene->getPhysicsWorld());
	scene->addChild(layer);
	return scene;
}
//设置物理世界
 void gameScene::setPhysicsWorld(PhysicsWorld *_world)
{
	PhysicsWorld *world=_world;
	world->setGravity(Vec2(0,-2000));//设置物理世界的重力（参数：x方向，y方向）
	
	//创建一个刚体（刚体的大小）
	auto bootom=PhysicsBody::createEdgeBox(Size(size.width,30));
	bootom->getShape(0)->setFriction(0.9);//设置摩擦力
	bootom->getShape(0)->setRestitution(0.5);//设置恢复力
	bootom->setMass(0);//设置质量

	//草丛精灵,也是刚体
	Sprite *bootomSp=Sprite::create("caocong.png");
	auto scaleX=size.width/bootomSp->getContentSize().width;
	bootomSp->setScaleX(scaleX);
	this->addChild(bootomSp);
	bootomSp->setPosition(Vec2(size.width/2,15));
	bootomSp->setPhysicsBody(bootom);//精灵绑定刚体
	//刚体调试（物理世界所有物体调试）
	//world->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
}

bool gameScene::init()
{ 
	if(!Layer::init())
	{
		return false;	
	}
	 size=Director::getInstance()->getWinSize();
	int chapter=UserDefault::getInstance()->getIntegerForKey("chapter");
	char gameBg[20];
	sprintf(gameBg,"background%d.png",chapter);
	Sprite *bg=Sprite::create(gameBg);
	auto scaleX=size.width/bg->getContentSize().width;
	auto ScaleY=size.height/bg->getContentSize().height;
	bg->setScale(scaleX,ScaleY);
	bg->setPosition(Vec2(size.width/2,size.height/2));
	this->addChild(bg);
	this->setTouchEnabled(true);
	//this->setTouchMode(Touch::DispatchMode::ONE_BY_ONE);
	auto touchListener=EventListenerTouchOneByOne::create();//点击触摸
	touchListener->onTouchBegan=CC_CALLBACK_2(gameScene::onTouchBegan,this);
	touchListener->onTouchMoved=CC_CALLBACK_2(gameScene::onTouchMoved,this);
	touchListener->onTouchEnded=CC_CALLBACK_2(gameScene::onTouchEnded,this);
	auto dispatcher=Director::getInstance()->getEventDispatcher();//分发中心
	dispatcher->addEventListenerWithSceneGraphPriority(touchListener,this);//向分发中心注册
	//物理世界监听（两个刚体碰撞调用方法）
	auto contactListener=EventListenerPhysicsContact::create();
	contactListener->onContactBegin=CC_CALLBACK_1(gameScene::onContactBegin,this);
	dispatcher->addEventListenerWithSceneGraphPriority(contactListener,this);

	//创建游戏布局界面，用cocosStudio完成物品摆放，游戏界面的布局可以导出为msb文件，也可以导出为ExportJson文件，只是用不同的方法加载而已
	//房子Button的tag值
	int levelNum=UserDefault::getInstance()->getIntegerForKey("level");
	char uiLayerName[40];
	sprintf(uiLayerName,"ui/Level_%d_%d.ExportJson",chapter,levelNum);
	log("===%s",uiLayerName);//输出语句
	
	Node *uiLayer;
	//这里选择部分关卡用msb，其余用ExportJson文件
	if(chapter==1&& levelNum==1)
	{
		uiLayer=CSLoader::createNode("Layer1_1.csb");
	}
	else
	{
		uiLayer=GUIReader::getInstance()->widgetFromJsonFile(uiLayerName);
		dynamic_cast<Widget *> (uiLayer)->setSwallowTouches(false);
	}
    //  auto uiLayer=GUIReader::getInstance()->widgetFromJsonFile(uiLayerName);	
	////吞噬触摸，true吞噬，不允许向下传递；false不吞噬，允许向下传递
	//uiLayer->setSwallowTouches(false);
	//uiLayer=GUIReader::getInstance()->widgetFromJsonFile(uiLayerName);
	//dynamic_cast<Widget *> (uiLayer)->setSwallowTouches(false);
	this->addChild(uiLayer);
    
	body_array =__Array::create();//盛放可点击消除的刚体
	body_array->retain();//建立数组，一帧不释放
	//星系，房子发光的效果
	house=(Widget *)uiLayer->getChildByName("house");	
	auto light=ParticleGalaxy::create();
	light->setPosition(house->getPosition());
	this->addChild(light);
	
	//关卡信息
	char labelText[20];
	sprintf(labelText,"%d--%d",chapter,levelNum);
	auto label=Label::createWithSystemFont(labelText,"",40);
	label->setColor(Color3B(100,100,100));
	label->setPosition(Vec2(size.width-100,size.height-80));
	this->addChild(label);

	//添加返回按钮
	 Button* pause= Button::create("pause.png","pause.png");
	 pause->setPosition(Vec2(50,size.height-50));
	 this->addChild(pause);
	 //使用lambda 表达式写暂停的回调函数，back->addClickEventListener(CC_CALLBACK_1(gameScene::back,this));
	 pause->addClickEventListener(CC_CALLBACK_1(gameScene::pauseBack,this)); 

	//从json文件解析出该关对应的刚体数，把它赋给变量num，根据num获得关卡的刚体数量，uiLayer对应的界面中的刚体数与json文件中的num数一致（相等）。
	int num=DataParse::getNum(chapter,levelNum);
	for(int i= 1;i<=num;i++)
	{
		char spriteName[20];
		sprintf(spriteName,"Image_%d",i);
		//从场景中取出精灵
		auto sprite=(Widget *)uiLayer->getChildByName(spriteName);
		//创建刚体并把精灵与刚体绑定
		this->createPhysicsBody(sprite);
	}
	//开始时星星的数量为1
	star_Num=0;
	//用来装界面出现的三颗星星
	star_array=__Array::create();
	star_array->retain();
	//通过uiLayer循环从界面上获取三颗星星item，并把它装入数组star_array，为了后来进行蜗牛和星星的碰撞检测
	for(int i =1;i <=3;i++)
	{
		char starNum[20];
		sprintf(starNum,"star%d",i);
		auto item=uiLayer->getChildByName(starNum);
		star_array->addObject(item);
	}
	//右上角的星星数量
	star=Sprite::create("0getstar.png");
	star->setPosition(Vec2(size.width - star->getContentSize().width/2,size.height- star->getContentSize().height/2));
	this->addChild(star);
	this->scheduleUpdate();

	return true;
}

void gameScene::pauseBack(Ref *sender)
{ 
	Director::getInstance()->pause();	 
	Director::getInstance()->getEventDispatcher()->pauseEventListenersForTarget(this); 	 
	Layer* layer=pauseLayer::create();	 
	layer->setPosition(Vec2(0,0));
	this->addChild(layer,8);
}

 //创建物理世界的刚体
 void  gameScene::createPhysicsBody(Node *sprite)
 {
	 PhysicsBody  *body;
	 Point point1,point2,point3;
	 Point points[3];
	 //设置精灵的bodyshape
	 switch (sprite->getTag())
	 {
	 case 601://蜗牛
		 //创建一个圆形动态刚体
		 snail=sprite;
		 body=PhysicsBody::createCircle(sprite->getContentSize().width/2);
		 body->getShape(0)->setRestitution(1);
		 body->setMass(20);
		 break;
	 case 106://石头，圆形动态刚体
		 body=PhysicsBody::createCircle(sprite->getContentSize().width/2-5);
		 body->getShape(0)->setRestitution(0.5);
		 break;
	 case 108://椰子,动态刚体
		 body=PhysicsBody::createBox(sprite->getContentSize());
		 body->getShape(0)->setRestitution(0.5);
		 body->setMass(100);
		 break;
	 case 107://弹力蘑菇，静态刚体
		 body= PhysicsBody::createEdgeBox(sprite->getContentSize());
		 body->getShape(0)->setRestitution(2);
		 body->setMass(0);
		 break;
	 case 109://三角砖，静态刚体
		 sprite->setAnchorPoint(Vec2(0,0));
		 point1=Point(-sprite->getContentSize().width/2,-sprite->getContentSize().height/2);
		 point2=Point(-sprite->getContentSize().width/2,sprite->getContentSize().height);
		 point3=Point(sprite->getContentSize().width/2,-sprite->getContentSize().height);
		 points[0]=point1;
		 points[1]=point2;
		 points[2]=point3;
		 body=PhysicsBody::createEdgePolygon(points,3);
		 body->getShape(0)->setRestitution(0.5);
		 body->setMass(0);
		 break;
	 case 401://刺，静态刚体
		 body=PhysicsBody::createEdgeBox(sprite->getContentSize());
		 body->getShape(0)->setRestitution(0.5);
	 case 201://点击不可消除
		 body=PhysicsBody::createEdgeBox(sprite->getContentSize());
		 body->getShape(0)->setRestitution(0.5);
		 break;
	 case 301://点击可消除
		 if (Widget *item=dynamic_cast<Widget *>(sprite))
		 {
			 item->setSwallowTouches(false);
		 }
		 //sprite->setSwallowTouches(false);
		 body=PhysicsBody::createEdgeBox(sprite->getContentSize());
		 body->getShape(0)->setRestitution(0.5);
		 body_array->addObject(body);
		 break;
	 default:
		 break;
	 }
	 
	 body->getShape(0)->setFriction(0.2);//设置摩擦力
	 //开启后，物体方可检测碰撞（必须设置三个参数）
	 body->setCategoryBitmask(1);//设置类别
	 body->setCollisionBitmask(1);//设置掩码
	 body->setContactTestBitmask(1);//设置触摸组

	 //精灵与刚体绑定
	 sprite->setPhysicsBody(body);
 }

 bool gameScene::onTouchBegan(Touch *touch, Event *unused_event)
 {
	 log("ontouchBegin");
	 return true;//true 接受触摸，并向下传递，false接受触摸的，但不传递
 }
 void gameScene::onTouchMoved(Touch *touch, Event *unused_event)
 {
	  log("onTouchMoved");
 }
 bool gameScene::onContactBegin(PhysicsContact &contact)
 {
	 auto nodeA=(Widget *)contact.getShapeA()->getBody()->getNode();
	 auto nodeB=(Widget *)contact.getShapeB()->getBody()->getNode();
	 int Atag=nodeA->getTag();
	 int Btag=nodeB->getTag();
	 //利用tag值进行判断
	 if( (Atag==401 && Btag==601) ||(Atag==601 && Btag==401))
	 {
		
		 log("AABBB");
		 this->unscheduleUpdate();//停止定时器
		 this->setTouchEnabled(false);//停止当前layer的点击事件
		 Director::getInstance()->getEventDispatcher()->removeAllEventListeners();//移除所有的监听事件
		 auto loseLayer = LoseLayer::create();
		 loseLayer->setPosition(Vec2(0,200));
		 auto moveTo = MoveTo::create(0.7,Vec2(0,0));
		 this->addChild(loseLayer);
		 loseLayer->runAction(moveTo);
	 }
	 return true;
 }

 //根据用户的点击操作，更新游戏的界面显示结果
 void gameScene::update(float f)
 {
	 auto rect=snail->getBoundingBox();
	 //判断蜗牛和星星是否碰撞
	 for(int i =0; i< star_array->count();i++)
	 {
		 auto item=(Widget*)star_array->objectAtIndex(i);
		 if(rect.intersectsRect(item->getBoundingBox()))
		 {
			 //控制音效
			 if(!UserDefault::getInstance()->getBoolForKey("Effect"))
			 {
				 SimpleAudioEngine::getInstance()->playEffect("yinxiao.wav",false);				 
			 }
			 item->removeFromParent();
			 star_array->removeObject(item);
			 star_Num=star_Num + 1;
			 char starImage[20];
			 sprintf(starImage,"%dgetstar.png",star_Num);
			 //改变精灵的纹理
			 star->setTexture(starImage);
		 }
	 }
	 //判断蜗牛与房子相碰撞
	 if(rect.intersectsRect(house->getBoundingBox()))
	 {
		 snail->setPosition(house->getPosition());
		 this->unscheduleUpdate();
		 int chapter=UserDefault::getInstance()->getIntegerForKey("chapter");
		 int levelNum=UserDefault::getInstance()->getIntegerForKey("level");
		 DataParse::setStar(chapter,levelNum,star_Num);
		 this->setTouchEnabled(false);
		 Director::getInstance()->getEventDispatcher()->removeAllEventListeners();
		 WinLayer::setstarNum(star_Num);
		 auto winlayer=WinLayer::create();
		 winlayer->setPosition(Vec2(0,200));
		 auto moveto=MoveTo::create(0.7,Vec2(0,0));
		 this->addChild(winlayer);
		 winlayer->runAction(moveto);		
	 }
	 //是否出界，即蜗牛和刚体世界没有碰撞，则游戏失败
	 auto worldRect=Rect(0,0,size.width,size.height);
	 if(!rect.intersectsRect(worldRect))
	 {
		 this->unscheduleUpdate();
		 this->setTouchEnabled(false);
		 Director::getInstance()->getEventDispatcher()->removeAllEventListeners();
		 auto loseLayer=LoseLayer::create();
		 loseLayer->setPosition(Vec2(0,200));
		 auto moveTo=MoveTo::create(0.7,Vec2(0,0));
		 this->addChild(loseLayer);
		 loseLayer->runAction(moveTo);
	 }
 }
 void gameScene::onTouchEnded(Touch *touch, Event *unused_event)
 {
	  log("onTouchEnded");
	  auto point =touch->getLocation();//获得当前点击的点的坐标
	  for(int i=0;i<body_array->count();i++)
	  {
		  
		   auto body=(PhysicsBody *)body_array->getObjectAtIndex(i);//获得点击可消除的刚体
		  // 通过语句 body->getNode()获得刚体所属的精灵，body本身不是一个节点，只是添加到精灵节点的属性
		  auto rect=body->getNode()->getBoundingBox();//获得刚体的精灵的范围
		  //判断点击的点是否在点击的范围之内，判断是否是点击可消除的刚体
		  if(rect.containsPoint(point) && body->getNode()->getTag()==301)
		  {
			  body->removeFromWorld();//从物理世界中移除刚体
			  body->getNode()->removeFromParent();//从父视图中移除精灵
			  body_array->removeObject(body);//从数组中移除刚体
		  }

	  }
 }
