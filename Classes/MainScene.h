#ifndef __MAIN_SCENE_H__
#define __MAIN_SCENE_H__

#include "cocos2d.h"
USING_NS_CC;

class MainScene : public Layer
{
public:
	// there's no 'id' in cpp, so we recommend returning the class instance pointer
	static Scene* createScene();

	LabelTTF* label;

	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();

	// implement the "static create()" method manually
	CREATE_FUNC(MainScene);

	void onEnter();
	void onEnterTransitionDidFinish();

	void listenKeyboardEvent();

	void onKeyPressed2(EventKeyboard::KeyCode code, Event *evt);
	void onKeyReleased2(EventKeyboard::KeyCode code, Event *evt);
};

#endif // __MAIN_SCENE_H__