#include "HelloWorldScene.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    auto scene = Scene::create();
    
    auto layer = HelloWorld::create();

    scene->addChild(layer);

    return scene;
}

bool HelloWorld::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    
   visibleSize = Director::getInstance()->getVisibleSize();
   origin = Director::getInstance()->getVisibleOrigin();

    //游戏背景
   auto layerClour = LayerColor::create(Color4B(255,255,255,255));  
   this->addChild(layerClour);  

   //添加标题
   auto title = LabelTTF::create("Tic-Tac-Toe","Arial",30);
   title->setColor(Color3B(139,69,19));
   title->setPosition(Point(visibleSize.width/2,visibleSize.height-50));
   addChild(title);

   //添加卡片
   addCard();

   //初始化点击次数和图案标记
   count = 1;
   initPatternNum = 10;

   auto listener = EventListenerTouchOneByOne::create();
   listener->onTouchBegan = [this](Touch *t,Event *e){

   c = Card::getCard();
   Card *it;


       for (auto iterator = c->begin() ; iterator != c->end(); iterator++)  
       {  
            it = *iterator;//迭代器，容量资源，用于调用图片。
			if((it->getFlag() == 0) && (it->getBoundingBox().containsPoint(t->getLocation())) && (count==1 || count ==3 || count == 5 || count==7 || count == 9))
			{	
				it->setFlag(1);
				it->setPattern(0);
				it->showO();
				count++;
			}
			if((it->getFlag() == 0) && (it->getBoundingBox().containsPoint(t->getLocation())) && (count==2 || count ==4 || count == 6 || count==8))
			{
				it->setFlag(1);
				it->setPattern(1);
				it->showX();
				count++;
			}
	   }
	   this->isGameOver();
	   return false;
   };
   Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener,this); 

    return true;
}


void HelloWorld::menuCloseCallback(Ref* pSender)
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


void HelloWorld::addCard()
{
	Card *card;
	for (int i = 0; i < 3; i++)
	{
		for(int j = 0; j < 3; j++)
		{
			card = Card::createCards(Color3B::GRAY,Size(visibleSize.width/3-3,visibleSize.height/4-3));
			card->setPosition(Point(i*visibleSize.width/3,j*visibleSize.height/4));
			card->setPattern(initPatternNum++);
			cardArr[i][j] = card;
			addChild(card);
		}
	}
}

void HelloWorld::isGameOver()
{
	if(count == 10)
	{
		reStart();
	}

	for (int x = 0; x < 3; x++)
	{
		if(cardArr[x][0]->getPattern() == cardArr[x][1]->getPattern() && cardArr[x][1]->getPattern() == cardArr[x][2]->getPattern())//判断同一行是否相同
		{
			reStart();
		}
	}

	for (int y = 0; y < 3; y++)
	{
		if(cardArr[0][y]->getPattern() == cardArr[1][y]->getPattern() && cardArr[1][y]->getPattern() == cardArr[2][y]->getPattern())//判断同一列
		{
			reStart();
		}
	}

	if (cardArr[0][0]->getPattern() == cardArr[1][1]->getPattern() && cardArr[1][1]->getPattern() == cardArr[2][2]->getPattern())//主对角线
	{
		reStart();
	}	

	if (cardArr[0][2]->getPattern() == cardArr[1][1]->getPattern() && cardArr[1][1]->getPattern() == cardArr[2][0]->getPattern())//副对角线
	{
		reStart();
	}	
}

void HelloWorld::reStart()
{
	c->clear();
	Director::getInstance()->replaceScene(TransitionFade::create(1,HelloWorld::createScene()));
}