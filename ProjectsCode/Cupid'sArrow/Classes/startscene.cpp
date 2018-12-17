#include "startscene.h"
#include "ResourceLoadScene.h"
#include "cocos2d.h"
Scene*startscene::createScene()
{
	auto scene=Scene::create();
	auto layer=startscene::create();
	scene->addChild(layer);
	return scene;
}
bool startscene::init()
{
	if(!Layer::init())
	{
		return false;
	}
	auto winSize=Director::getInstance()->getWinSize();
	auto sprite=Sprite::create("bg1.png");
	sprite->setScale(2.7f);
	FadeTo*fadeto=FadeTo::create(3,20);
	sprite->setPosition(Point(winSize.width/2,winSize.height/2));
	sprite->runAction(fadeto);
	this->addChild(sprite);
	
	schedule(CC_CALLBACK_1(startscene::nextScence,this),3.0f,"nextScene");
	return true;
}
void startscene::nextScence(float dt)
{
	Scene* scence = ResourceLoadScene::createScence();
	Director::getInstance()->replaceScene(scence);
}




