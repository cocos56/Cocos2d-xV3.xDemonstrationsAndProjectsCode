#pragma once

#include "cocos2d.h"
USING_NS_CC;

class MainInterface : public Layer
{
public:
	static Scene* createScene();
	bool init();
	void startAction(Ref *obj);

	Size windowSize;

	CREATE_FUNC(MainInterface);
};