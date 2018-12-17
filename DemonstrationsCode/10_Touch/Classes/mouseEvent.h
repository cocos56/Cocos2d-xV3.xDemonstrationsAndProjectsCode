#pragma once
#include "cocos2d.h"
USING_NS_CC;
class mouseEvent :public Layer
{
public:
	mouseEvent(void);
	~mouseEvent(void);
public:
	static Scene* createScene();
    virtual bool init();
    CREATE_FUNC(mouseEvent);
		
	void onMouseDownss(Event *ev);
    void onMouseMoved(Event *ev);
    void onMouseUpss(Event *ev);
    void onMouseScrollss(Event *ev);
};

