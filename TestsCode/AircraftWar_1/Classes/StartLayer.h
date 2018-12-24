//
//  StartLayer.hpp
//  testGame
//
//  Created by 姚龙 on 15/12/23.
//
//

#ifndef StartLayer_hpp
#define StartLayer_hpp

#include <stdio.h>
#include "cocos2d.h"

using namespace cocos2d;
using namespace std;

class StartLayer: public Layer {
    
    
public:
    
    static Scene* createGameStartScent();
    
    bool init();
    
    Size windowSize;
    
    void startAction(Ref* object);
    
    CREATE_FUNC(StartLayer);
};

#endif /* StartLayer_hpp */
