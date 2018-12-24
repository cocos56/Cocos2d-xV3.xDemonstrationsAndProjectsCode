//
//  GameMain.hpp
//  testGame
//
//  Created by 姚龙 on 15/12/21.
//
//

#ifndef GameMain_hpp
#define GameMain_hpp

#include <stdio.h>
#include "cocos2d.h"

using namespace cocos2d;
using namespace std;

class GameMain: public cocos2d::Layer {
    
    
public:
    ///窗口的大小
    Size windowSize;
    ///时间变量
    int time_m;
    ///成绩变量
    int score_m;
    
    bool init();
    
    ///统一实现我们的游戏变凉初始化
    void initAllParamter();
    
    static cocos2d::Scene* MainScene();
    
    ///背景图片下
    Sprite* bgImg;
    ///背景图片上
    Sprite* bgTop;
    
    ///游戏状态栏的背景图片
    Sprite* gameState;
    
    ///显示时间
    Label* time_show;
    ///显示成绩
    Label* score_show;
    
    void updateBgImagePostion(float time);
    ///主要是负责我们成绩和时间的计算
    void countTimeAndScore(float time);
    
    void changeBgImagePostion(Sprite* bgImage_m);
    
    ///返回到开始界面
    void backToStartLayer(Ref* object);
    ///游戏的暂停操作
    void pauseGame(Ref* object);
    
    
    CREATE_FUNC(GameMain);
};

#endif /* GameMain_hpp */
