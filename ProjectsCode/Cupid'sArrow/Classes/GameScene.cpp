#include "GameScene.h"
#include "Mainscene.h"
//#include "MycontactListener.h"


#include "SimpleAudioEngine.h"
using namespace CocosDenshion;
USING_NS_CC;
Scene* GameScene::createScene()
{
	auto scene = Scene::create();
	auto layer = GameScene::create();
	scene->addChild(layer);
	return scene;
}

bool GameScene::init()
{
	if ( !Layer::init() )
	{
		return false;
	}
	//关卡控制
	_score=0;
	_gameOver=false;
	_sucessScore = 15 + (_level*5 - 5);
	_totalxin = 20 + (_level*10 - 10);
	_timeBarInterval = 100/_totalxin;
	a = 0.5 - (_level*0.05 - 0.05);

	Size visibleSize = Director::getInstance()->getVisibleSize();
	_screenWidth = visibleSize.width;
	_screenHeight = visibleSize.height;
	_gameOver=false;
	// 创建背景图片
	auto bg = Sprite::create("bg4.png");
	bg->setScale(1.95f);
	bg->setPosition(_screenWidth/2, _screenHeight/2+150);
	this->addChild(bg, -2);

	// 创建计时器进度条
	_timeBar = LoadingBar::create("bar.png");
	_timeBar->setScale(0.4f);
	_timeBar->setDirection(LoadingBar::Direction::LEFT);
	_timeBar->setPercent(100);
	_timeBar->setAnchorPoint(Vec2(0,1));
	_timeBar->setPosition(Vec2(_screenWidth*0.11, _screenHeight*0.1));
	this->addChild(_timeBar,2);
	//时间调度
	this->scheduleUpdate();
	this->schedule(schedule_selector(GameScene::addxin), 2-_level*0.3);
	this->schedule(schedule_selector(GameScene::gameOver), 1);
	// 关卡数
	_levelSprite=Sprite::create("level-1.png");
	_levelSprite->setPosition(visibleSize.width*0.15-50, visibleSize.height-30);
	_levelSprite->setScale(0.7);
	this->addChild(_levelSprite, 3);

	char temp[50];
	sprintf(temp,"%d",_level);
	_levelLabel = Label::createWithSystemFont(temp,"DPCarved",36);
	_levelLabel->setPosition(visibleSize.width*0.15, visibleSize.height-30);
	this->addChild(_levelLabel, 3);

	// 关卡得分
	_scoreSprite=Sprite::create("score-1.png");
	_scoreSprite->setPosition(visibleSize.width*0.4-65, visibleSize.height-40);
	_scoreSprite->setScale(0.7);
	this->addChild(_scoreSprite, 3);

	sprintf(temp,"%d",_score);
	_scoreLabel = Label::createWithSystemFont(temp,"DPCarved",36);
	_scoreLabel->setPosition(visibleSize.width*0.4, visibleSize.height-30);
	this->addChild(_scoreLabel, 3);	
	_scoreLabel->setTag(30);
	// 关卡过关分数
	_passSprite=Sprite::create("target score-1.png");
	_passSprite->setPosition(visibleSize.width*0.95-150, visibleSize.height-25);
	_passSprite->setScale(0.7);
	this->addChild(_passSprite, 3);

	sprintf(temp,"%d",_sucessScore);
	_passLabel = Label::createWithSystemFont(temp,"DPCarved",36);
	_passLabel->setPosition(visibleSize.width*0.95, visibleSize.height-30);
	this->addChild(_passLabel, 3);


	

	child =Sprite::create("child.png");
	child->setScale(2.0f);
	child->setPosition(visibleSize.width/2+100, visibleSize.height/2+100);
	this->addChild(child,2);
	child1 =Sprite::create("child.png");
	child1->setScale(2.0f);
	act1= FlipX::create(true);
	child1->runAction(act1);
	child1->setPosition(visibleSize.width/2-100, visibleSize.height/2+100);
	child1->setVisible(false);
	this->addChild(child1,2);

	

	 auto gameListener = EventListenerTouchOneByOne::create();
	
	 gameListener->onTouchBegan=[=](Touch* touch, Event* event){  
		 Vec2 touchlocation = touch->getLocation();
		 if (touchlocation.y<600&& _gameOver ==false&&_i>0)
		 {
			 SimpleAudioEngine::getInstance()->playEffect("3774.mp3");
			  return true;
		 }
		 else
			 return false;
		 
		};
	 gameListener->onTouchMoved = [=](Touch* touch, Event* event){};
	 gameListener->onTouchEnded = [=](Touch* touch, Event* event){

		 Vec2 touchlocation = touch->getLocation();
		 Vec2 nodelocation =this->convertToNodeSpace(touchlocation);
		 auto jian =Sprite::create("jian.png");
		 jian->setScale(0.7f);
		 this->addChild(jian,2);
		 auto moveto= MoveTo::create(0.8f,Point(nodelocation));
		 jian->runAction(Sequence::create(moveto,CallFuncN::create(CC_CALLBACK_1(GameScene::unHit, this)),NULL));
		 jian->setTag(2);
		 _jianVector.pushBack(jian);
		
		  if (nodelocation.x<_screenWidth/2)
		  
		 {
			 child1->setVisible(false);
			 child->setVisible(true);
			 jian->setPosition(Vec2(child->getPosition().x+120,child->getPosition().y+100));
			 auto rotateTo=RotateTo::create(0.1,45);
			 jian->runAction(rotateTo);
			 auto ll = Animate::create(AnimationCache::getInstance()->getAnimation("fei"));
			 child->runAction(ll);
			 if(jian->isFlippedX())
			 {jian->setFlippedX(false);
			 }
		   //  _i1=1;
		 }
		  else if (nodelocation.x>_screenWidth/2)
		 {
			 child->setVisible(false);
			 child1->setVisible(true);
			 jian->setPosition(Vec2(child1->getPosition().x-120,child1->getPosition().y+100));
			 
			  auto rotateTo=RotateTo::create(0.1,-45);
			 jian->runAction(rotateTo);
			 auto ll = Animate::create(AnimationCache::getInstance()->getAnimation("fei"));
			  child1->runAction(ll);
			  if(!jian->isFlippedX())
			 {jian->setFlippedX(true);
			  }
			 
     	    // _i1=0;
		 }
		 
	 };
	
	 Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(gameListener, this);
	
	return true;
}


//添加心
void GameScene::addxin(float delta)
{
	// _gameOver标记为true，游戏结束
	if (_gameOver) return;
	
	// 设置分数
	char t[50];
	sprintf(t,"%d",_score);
	_scoreLabel->setString(t);
	// 获取一个随机数
	int x =CCRANDOM_0_1()*2;
	int y =CCRANDOM_0_1()*340;
	int z =CCRANDOM_0_1()*340;
	int b;
	y =y+300;
    auto xin = Sprite::create("xin1.png");
	if (x==1)
	{
		xin->setPosition(1050,z);
	}else
	{
		
		xin->setPosition(-70,z);
	}
	this->addChild(xin, 0);
	xin->setTag(1);
	_xinVector.pushBack(xin);

	if (_totalxin <= 0) 
	{_gameOver=true;return;}
	_totalxin--;

	if (x==1)
	{
		b =-70;	
	}else
	{
		b =1050;
		auto act = FlipX::create(true);

		xin->runAction(act);
	}
	auto Moveto =MoveTo::create(6.0f, Point(b,y));
	auto WW = Animate::create(AnimationCache::getInstance()->getAnimation("xin"));
	auto action1 = Spawn::create(Moveto,WW,CallFuncN::create(CC_CALLBACK_1(GameScene::setHit, this)),NULL);
	xin->runAction(action1);
	float percentage = _timeBarInterval*_totalxin;
	_timeBar->setPercent(percentage);
	
	
}


void GameScene::setHit(Ref* pSender){
	xin = (Sprite*)pSender;
	xin->setTag(1);

	

}
void GameScene::update(float delta)
	

{
	for (auto it2 =_xinVector.begin();it2!=_xinVector.end();it2++)
	{  
		xin=*it2;
		if (xin->getTag() == 0 ) continue;
		for (auto it=_jianVector.begin();it!=_jianVector.end();it++)
		{
			jian=*it;
			if (jian->getTag() == 0 ) continue;		

			//碰撞检测
			if (jian->getBoundingBox().intersectsRect(xin->getBoundingBox()))
			{
				SimpleAudioEngine::getInstance()->playEffect("xinsui.wav");
				this->removeChild(jian);
				xin->stopAllActions();
				auto ll = Animate::create(AnimationCache::getInstance()->getAnimation("xinluo"));
				xin->setScale(1.2f);
				xin->runAction(ll);
                auto actionluo1 = Spawn::create(ll,NULL);
				xin->runAction(Sequence::create(actionluo1,CallFuncN::create(CC_CALLBACK_1(GameScene::unHit, this)),NULL));
				xin->setTag(0);
				jian->setTag(0);

				char temp[50];
				auto s = (Label *)getChildByTag(30);
				sprintf(temp,"%d",++_score);
				_scoreLabel->setString(temp);
			

			}

		}


	}

}



void GameScene::unHit(Ref* pSender)
{
	xin = (Sprite*)pSender;
	xin->setTag(0);
	this->removeChild(xin);
}

void GameScene::gameOver(float delta)
{
      if (_totalxin <= 0){
		bool flag = true;
		for (auto it=_xinVector.begin();it!=_xinVector.end();it++)
		{   xin=*it;
		if(xin->getNumberOfRunningActions() != 0){
			flag = false;
			break;
		}
		}

		if (flag) {
			_gameOver = true;
			MenuItemImage* goItem = NULL;
			if (_score < _sucessScore) {
				goItem = MenuItemImage::create("chongwan.png", "chongwan.png",CC_CALLBACK_0(GameScene::continueGame,this));
				auto snow=ParticleSnow::create();
				snow->setSpeed(100);
	            snow->setDuration(2);//播放次数
	            this->addChild(snow);
				 UserDefault::getInstance()->getBoolForKey("onEffect");
				SimpleAudioEngine::getInstance()->playEffect("lose.wav",false);
			}
			else
			{
				goItem = MenuItemImage::create("xiayiguan.png", "xiayiguan.png",CC_CALLBACK_0(GameScene::goNext,this));
				auto quad = ParticleSystemQuad::create("liuxing.plist");
				quad->setPosition(100,_screenHeight);
         auto quad1 = ParticleSystemQuad::create("liuxing.plist");
	      quad1->setPosition(350,_screenHeight);
		 auto quad2 = ParticleSystemQuad::create("liuxing.plist");
	            quad2->setPosition(600,_screenHeight);
	            quad->setDuration(2);//播放次数
	            this->addChild(quad);
				 this->addChild(quad1);
				  this->addChild(quad2);
				 UserDefault::getInstance()->getBoolForKey("onEffect");
				SimpleAudioEngine::getInstance()->playEffect("win.wav",false);
               
			}
			goItem->setPosition(Vec2(_screenWidth / 2, _screenHeight / 2+100));
			auto againItem = MenuItemImage::create("congtouzailai.png","congtouzailai.png",CC_CALLBACK_0(GameScene::againGame,this));
			againItem->setPosition(Vec2(_screenWidth / 2, _screenHeight / 2-100));
			auto menu = Menu::create(goItem,againItem, NULL);
			menu->setPosition(Vec2::ZERO);
			this->addChild(menu, 1);
		}
	}
}
void GameScene::againGame(){
	_level=1;
	Director::getInstance()->replaceScene(Mainscence::creatScence());
} 
void GameScene::goNext(){
	_level = _level + 1;
	Director::getInstance()->replaceScene(GameScene::createScene());

}
void GameScene::continueGame(){
	Director::getInstance()->replaceScene(GameScene::createScene());
}


