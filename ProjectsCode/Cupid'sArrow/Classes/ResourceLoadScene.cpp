#include "ResourceLoadScene.h"
#include "Mainscene.h"


Scene*ResourceLoadScene::createScence()
{
	cocos2d::Scene*scene=cocos2d::Scene::create();
	ResourceLoadScene*layer=ResourceLoadScene::create();
	scene->addChild(layer);
	return scene;
}
bool ResourceLoadScene::init()
{
	if(!Layer::init())
	{
		return false;
	}

	cocos2d::Size winSize = cocos2d::Director::getInstance()->getWinSize();
	cocos2d::Sprite* bgSprite = cocos2d::Sprite::create("bg2.png");
	bgSprite->setPosition(cocos2d::Vec2(winSize.width/2+200,winSize.height/2));
		;
	bgSprite->setScale(1.7f);
	this->addChild(bgSprite);


	cocos2d::Sprite*progressSprite=cocos2d::Sprite::create("xiaohai1.png");
	progressSprite->setScale(0.6);
	cocos2d::ProgressTimer*progress=cocos2d::ProgressTimer::create(progressSprite);
	progress->setPosition(cocos2d::Vec2(winSize.width/2,winSize.height/2));
	this->addChild(progress);
	progress->setType(cocos2d::ProgressTimer::Type::BAR);
	FadeTo* fadeto = FadeTo::create(3,0);
	cocos2d::ProgressTo* progressTo = cocos2d::ProgressTo::create(3.0, 100);
	cocos2d::Sequence* seq = cocos2d::Sequence::create(progressTo,fadeto, NULL);
	progress->setMidpoint(cocos2d::Vec2(0,0.5));
	progress->setBarChangeRate(cocos2d::Vec2(1,0));
	progress->runAction(seq);
	

	
	label=cocos2d::Label::createWithSystemFont("Loading...","ronts/Marker Felt.ttf",20);
	label->setName("label");
	label->setScale(2);
	label->setColor(cocos2d::Color3B::BLACK);
	label->setPosition(cocos2d::Vec2(winSize.width/2,winSize.height/2-200));
	this->addChild(label,2);


	schedule(CC_CALLBACK_1(ResourceLoadScene::nextScene,this),6.0f,"nextScene");
	return true;
}

void ResourceLoadScene::nextScene(float dt)
{
	Scene*scene=Mainscence::creatScence();
	Director::getInstance()->replaceScene(scene);
}
