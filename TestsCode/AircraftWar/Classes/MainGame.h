#pragma once

#include "cocos2d.h"
USING_NS_CC;

class MainGame : public Layer
{
public:
	static Scene* createScene();
	bool init();
	void updateBgPosition(float dt);
	void changeBgPosition(Sprite *bg);
	void backToMainInterface(Ref *obj);
	void pauseGame(Ref *obj);
	void resumeGame(Ref *obj);

	Sprite *bg, *bg2;
	Size windowSize;
	Label *time, *score;
	Menu *resume_list;

	CREATE_FUNC(MainGame);
};