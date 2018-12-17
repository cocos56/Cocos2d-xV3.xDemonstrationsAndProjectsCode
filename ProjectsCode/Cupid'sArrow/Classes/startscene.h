#pragma once
#include "cocos2d.h"
using namespace cocos2d;
class startscene:public Layer
{
public:
	static cocos2d::Scene * createScene();
	virtual bool init();  
	CREATE_FUNC(startscene);
	void nextScence(float dt);
};
