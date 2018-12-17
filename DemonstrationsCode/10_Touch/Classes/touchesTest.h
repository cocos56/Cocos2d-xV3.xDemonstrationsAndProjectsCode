#pragma once
#include "cocos2d.h"
USING_NS_CC;
class touchesTest :	public Layer
{
public:
	touchesTest(void);
	~touchesTest(void);
public:
	static Scene * createScene();
	virtual bool init( );
	CREATE_FUNC(touchesTest);
	virtual void onTouchesBegan(const std::vector<Touch*>& touches, Event *unused_event);
    virtual void onTouchesMoved(const std::vector<Touch*>& touches, Event *unused_event);
    virtual void onTouchesEnded(const std::vector<Touch*>& touches, Event *unused_event);
    virtual void onTouchesCancelled(const std::vector<Touch*>&touches, Event *unused_event);
};

