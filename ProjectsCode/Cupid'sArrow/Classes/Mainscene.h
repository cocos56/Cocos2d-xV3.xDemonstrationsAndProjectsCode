
#pragma once
#include<stdio.h>
#include"cocos2d.h"
using namespace cocos2d;
#define RESOURCESPLIST "resources.plist"
class Mainscence:public cocos2d::Layer
{
public:
	virtual bool init();
	static cocos2d::Scene* creatScence();
	CREATE_FUNC(Mainscence);
	//void helpbook();
	void end();
	//void nextgame();
	void helpgame();
	void finish();
	void gameStart();
    Animation * getAnimationByName(std::string animName,float delay,int animNum);
	

};
