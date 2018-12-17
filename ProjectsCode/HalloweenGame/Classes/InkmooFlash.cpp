
#include "InkmooFlash.h"
#include "GameDefine.h"
#include "MainScene.h"

USING_NS_CC;

bool InkmooFlash::init( )
{
	if( !LayerColor::initWithColor(Color4B(255,255,255,255) ) )
	{
		return false;
	}

	CCSpriteFrameCache * cache = CCSpriteFrameCache::sharedSpriteFrameCache();  
	cache -> addSpriteFramesWithFile("inkmoo_flash.plist");

	CCSprite *sp = CCSprite::createWithSpriteFrameName("inkmoo_001.png");
	sp -> setScale( 1.5f );
	sp -> setPosition(Point(GAME_SCREEN_WIDTH/2,GAME_SCREEN_HEIGHT/2));
	this -> addChild( sp );

	Vector< SpriteFrame* > sfme = Vector< SpriteFrame* >::Vector(78);
	char str[20] = {0};
	for( int i = 1 ; i < 79 ; ++i )
	{
		sprintf(str,"inkmoo_%03d.png",i);
		SpriteFrame *fname = cache -> spriteFrameByName( str );
		sfme.pushBack( fname );
	}
          
	CCAnimation *animation = CCAnimation::createWithSpriteFrames( sfme , 0.05f );
	sp -> runAction ( CCAnimate::create(animation ));

	this->scheduleOnce(schedule_selector(InkmooFlash::jumpToMain), 4);
	return true;
}

Scene* InkmooFlash::createScene( )
{
	auto scene = Scene::create();
	auto layer = InkmooFlash::create();

	scene -> addChild( layer );

	return scene;
}

void InkmooFlash::jumpToMain( float t )
{
	auto scene=MainScene::createScene();
    Director::getInstance()->replaceScene(CCTransitionProgressInOut ::create(1.2, scene));
}