#pragma once

#include "cocos2d.h"
#include "HelloWorldScene.h"

USING_NS_CC;

class MenuScene : public Layer
{
public:
    static Scene* createScene();
    virtual bool init();
    
    CREATE_FUNC(MenuScene);
    
    void playCallback(Ref* pSender);
    void exitCallback(Ref* pSender);
    
    
};
