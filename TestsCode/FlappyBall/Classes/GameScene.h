#pragma once

#include "cocos2d.h"
USING_NS_CC;

class GameScene : public Scene
{
public:
    static Scene* createScene();

    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(Ref* pSender);
	void updateBallPosition(float dt);
	void listenKeyboardEvent();
	void onKeyPressed2(EventKeyboard::KeyCode code, Event *evt);
	void onKeyReleased2(EventKeyboard::KeyCode code, Event *evt);
    
    // implement the "static create()" method manually
    CREATE_FUNC(GameScene);

	Sprite *bg, *ball, *obstacle, *bh;
	float g, vy, oy;
};