//
//  MenuScene.h
//  KidsNumerals
//
//  Created by mythlab on 12/14/15.
//
//

#ifndef __KidsNumerals__MenuScene__
#define __KidsNumerals__MenuScene__

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

#endif /* defined(__KidsNumerals__MenuScene__) */
