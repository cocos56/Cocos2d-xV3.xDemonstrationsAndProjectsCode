#include "sceneGraphPriority.h"
sceneGraphPriority::sceneGraphPriority(void)
{
}


sceneGraphPriority::~sceneGraphPriority(void)
{
}

Scene* sceneGraphPriority::createScene()
{
    // 创建一个场景对象，该对象将会由自动释放池管理内存的释放
    auto scene = Scene::create();
    
    // 创建层对象，该对象将会由自动释放池管理内存的释放
    auto layer = sceneGraphPriority::create();
    
    // 将HelloWorld层作为子节点添加到场景
    scene->addChild(layer);
    
    // 返回场景对象
    return scene;
}

// on "init" you need to initialize your instance
bool sceneGraphPriority::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    // 获得设备支持的可见OpenGL视图大小（即窗口大小）。
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    // 关闭菜单
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(sceneGraphPriority::menuCloseCallback, this));
    
	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));

   
    // ①创建单点触摸监听者（即创建一个单点触摸事件监听器），处理触摸事件逻辑
    auto listener1 = EventListenerTouchOneByOne::create();
    // 设置是否向下传递触摸,当为true时，下面的将被吞噬掉，不能接收到触摸事件，即不会向下传递，当为false时，不吞噬，即会向下传递。
    listener1->setSwallowTouches(true);

	// 删除触摸监听器 removeEventListenersForType，_eventDispatcher作为Node类的全局变量，可直接使用。
    auto removeAllTouchItem = MenuItemFont::create("Delete all the TouchListeners",[=](Ref* sender){auto senderItem = static_cast<MenuItemFont*>(sender);
	 senderItem->setString("TouchListenerDeletedSucceedd");
	 senderItem->setFontSize(15);
	 _eventDispatcher->removeEventListener(listener1); //删除指定的监听器listener1，仅仅删除了对颜青色layer的监听
	 //删除所有的单点触摸事件监听器，将连同菜单的关闭按钮的单击事件也被删除
	 //_eventDispatcher->removeEventListenersForType(EventListener::Type::TOUCH_ONE_BY_ONE);
      });
    removeAllTouchItem->setPosition(visibleSize.width/2, visibleSize.height*0.2);
    // 创建菜单
    auto menu = Menu::create(removeAllTouchItem,closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu);
    // 标题标签
    auto title = Label::createWithSystemFont("SingleClicked touchTest--SceneGraphPriority", "", 20);
    title->setPosition(visibleSize.width/2, visibleSize.height*0.9);
    this->addChild(title);
    
    // 提示标签 
    auto subtitle = Label::createWithSystemFont("Please click or drag Slider", "", 12);
    subtitle->setPosition(visibleSize.width/2, visibleSize.height*0.8);
    this->addChild(subtitle);
    
    // 创建三个精灵对象 
    auto sprite1 = Sprite::create("CyanSquare.png");
    sprite1->setPosition(Vec2(visibleSize.width/2, visibleSize.height/2) + Vec2(-80, 80));
    addChild(sprite1, 2);
    
    auto sprite2 = Sprite::create("MagentaSquare.png");
    sprite2->setPosition(Vec2(visibleSize.width/2, visibleSize.height/2));
    addChild(sprite2, 3);
    
    auto sprite3 = Sprite::create("YellowSquare.png");
    sprite3->setPosition(Vec2(0, 0));
    sprite2->addChild(sprite3, 1);
   
    //② 通过 lambda 表达式直接实现并绑定触摸事件的响应函数
    listener1->onTouchBegan = [](Touch* touch, Event* event){
        // 获得当前事件触摸的目标对象
        auto target = static_cast<Sprite*>(event->getCurrentTarget());
        // 获得当前的触摸点
        Point locationInNode = target->convertToNodeSpace(touch->getLocation());
        // 获得触摸对象的ContentSize
        Size s = target->getContentSize();
        // 获得位置矩形
        Rect rect = Rect(0, 0, s.width, s.height);
        // 如果位置矩形包含触摸点
        if (rect.containsPoint(locationInNode))
        {
            log("onTouchBegan... x = %f, y = %f", locationInNode.x, locationInNode.y);
            // 设置透明度
            target->setOpacity(180);
            // 表明用户触摸事件已经被处理，后续的onTouchMoved、onTouchEnded和onTouchCancelled会接着响应，其他事件监听器则不会再去进行监听本次触摸事件。
            return true;
        }
        return false;
    };
    
    listener1->onTouchMoved = [](Touch* touch, Event* event){
        auto target = static_cast<Sprite*>(event->getCurrentTarget());
        // 移动触摸的精灵
        target->setPosition(target->getPosition() + touch->getDelta());
		
		//无法隐式捕获“this”，因为尚未指定默认捕获模式
		/*auto position=touch->getLocation();
		auto position1=this->convertToNodeSpace(position);
		target->setPosition (position1);
		*/
    };
    
    listener1->onTouchEnded = [=](Touch* touch, Event* event){
        auto target = static_cast<Sprite*>(event->getCurrentTarget());
        // 设置透明度
        target->setOpacity(255);
        std::string name;
        if (target == sprite2) //sprite2为洋红色
        {
            name = "MagentaSquare.png";
            sprite1->setZOrder(100);//修改颜青色的z轴顺序为100，放到最上层
           //修改列表框的文本内容
			subtitle->setString("MagentaSquare responses event,CyanSquare's ZOrderis modified to 100");
		}
        else if(target == sprite1)//sprite1为颜青色
        {
            name = "CyanSquare.png";
            sprite1->setZOrder(0);   //修改颜青色的z轴顺序为0，放到最层
             //修改列表框的文本内容
			subtitle->setString("CyanSquare responses event,CyanSquare's ZOrderis modified to 100");
        }else{
            name = "YellowSquare.png";
        }
        log("onTouchEnded.. What you touched is %s",name.c_str());
    };
    
    /*③将监听器添加到事件分发器dispatcher中——添加场景优先事件监听器。
	直接使用Node类自带的全局属性_eventDispatcher。当设置listener1->setSwallowTouches(false)时；
	才能看到SceneGraphPriority的效果。
	*/
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener1, sprite1);
	/*注意：在使用addEventListenerWithSceneGraphPriority或者addEventListenerWithFixedPriority函数时，
	          会对当前使用的事件监听器添加一个已注册的标记，这使得它不能够被添加多次。
			  所以当我们再次使用listener1的时候，需要使用clone()函数创建一个新的克隆。*/
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener1->clone(), sprite2);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener1->clone(), sprite3);
    
  return true;
}

void sceneGraphPriority::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif

    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}