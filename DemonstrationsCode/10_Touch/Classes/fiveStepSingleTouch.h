#pragma once
#include "cocos2d.h"
USING_NS_CC;
class fiveStepSingleTouch :	public Layer
{
public:
	fiveStepSingleTouch(void);
	~fiveStepSingleTouch(void);
public:
	static Scene* createScene();
    virtual bool init();
    CREATE_FUNC(fiveStepSingleTouch);
    virtual bool onTouchBegan(Touch *touch, Event *unused_event);
    virtual void onTouchMoved(Touch *touch, Event *unused_event);
    virtual void onTouchEnded(Touch *touch, Event *unused_event);
    virtual void onTouchCancelled(Touch *touch, Event *unused_event);
    void onExit();
    void onEnter();

};

