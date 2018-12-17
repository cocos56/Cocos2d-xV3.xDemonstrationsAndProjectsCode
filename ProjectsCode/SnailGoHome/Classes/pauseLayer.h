#pragma once
#include "cocos2d.h"
USING_NS_CC;
class pauseLayer :public LayerColor
{
public:
	pauseLayer(void);
	~pauseLayer(void);
	virtual bool init();
	CREATE_FUNC(pauseLayer);	
    void clickButton(Ref *sender);
};

