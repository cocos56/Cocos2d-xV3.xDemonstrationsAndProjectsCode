#pragma once
#include "cocos2d.h"
USING_NS_CC;

class SelectChapter :	public Layer
{
public:
	static Scene * createScene();
	virtual bool  init();
	CREATE_FUNC(SelectChapter);
	void back();
	void goto_chapter(Ref *sender);
};

