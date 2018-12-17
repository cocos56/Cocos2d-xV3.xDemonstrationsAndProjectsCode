#pragma once
#include "cocos2d.h"
USING_NS_CC;
#include "ui/CocosGUI.h"
using namespace ui;

class selectLevel :	public Layer
{
public:
	static Scene * createScene();
	virtual bool  init();
	CREATE_FUNC(selectLevel);
	void flip();
	void createLevelItem();
	void  back();
	void goto_level(Ref *sender);
private:
	Sprite *wo1;
	Size   size;
	ScrollView *scrollView;
};

