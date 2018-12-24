//
//  GameMain.cpp
//  testGame
//
//  Created by 姚龙 on 15/12/21.
//
//

#include "GameMain.h"
#include "StartLayer.h"


cocos2d::Scene* GameMain::MainScene() {

    Scene* scene_m = Scene::create();
    
    GameMain* layer_m = GameMain::create();
    
    scene_m->addChild(layer_m);
    
    return scene_m;
}

void GameMain::initAllParamter() {

    this->time_m = 0;
    this->score_m = 0;

}

bool GameMain::init() {

    if (cocos2d::Layer::init()) {
        
        this->windowSize = this->getContentSize();
        
        this->initAllParamter();
        
        this->bgImg = Sprite::create("bg.png");
        this->bgImg->setAnchorPoint(Vec2(0, 1));
        this->bgImg->setPosition(Vec2(0, this->windowSize.height));
        this->addChild(this->bgImg);
        
        this->bgTop = Sprite::create("bg.png");
        this->bgTop->setAnchorPoint(Vec2(0, 1));
        this->bgTop->setPosition(Vec2(0, this->windowSize.height*2));
        this->addChild(this->bgTop);
        
        
        this->schedule(schedule_selector(GameMain::updateBgImagePostion), 0.005);
        this->schedule(schedule_selector(GameMain::countTimeAndScore), 1);
        
        
        ///返回按钮
        Sprite* nornal = Sprite::create("back.png");
        Sprite* selected = Sprite::create("back_selected.png");
        
        MenuItemSprite* startBtn = MenuItemSprite::create(nornal, selected, CC_CALLBACK_1(GameMain::backToStartLayer, this));
        Menu* list = Menu::create(startBtn, NULL);
        list->setAnchorPoint(Vec2(0, 1));
        list->setPosition(Vec2(this->windowSize.width-nornal->getContentSize().width-20, this->windowSize.height-nornal->getContentSize().height));
        
        this->addChild(list, 2);
        
        ///返回按钮
        Sprite* nornal_p = Sprite::create("pause.png");
        Sprite* selected_p = Sprite::create("pause_selected.png");
        
        MenuItemSprite* pBtn = MenuItemSprite::create(nornal_p, selected_p, CC_CALLBACK_1(GameMain::pauseGame, this));
        Menu* plist = Menu::create(pBtn, NULL);
        plist->setAnchorPoint(Vec2(0, 1));
        plist->setPosition(this->windowSize.width-nornal_p->getContentSize().width-20,
                                nornal_p->getContentSize().height);
        
        this->addChild(plist);

        ///创建状态栏的背景图片
        this->gameState = Sprite::create("top.png");
        this->gameState->setAnchorPoint(Vec2(0, 1));
        this->gameState->setPosition(Vec2(0, this->windowSize.height));
        
        this->addChild(this->gameState);
        
        ///创建时间标签
        this->time_show = Label::create();
        this->time_show->setContentSize(Size(200, this->gameState->getContentSize().height));
        this->time_show->setAnchorPoint(Vec2(0.5, 0.5));
        this->time_show->setPosition(Vec2(100, this->gameState->getContentSize().height/2));
        this->time_show->setColor(Color3B::YELLOW);
        this->time_show->setString("12:00");
        
        this->gameState->addChild(this->time_show);
        
        ///创建成绩标签
        this->score_show = Label::create();
        this->score_show->setContentSize(Size(200, this->gameState->getContentSize().height));
        this->score_show->setAnchorPoint(Vec2(0.5, 0.5));
        this->score_show->setPosition(Vec2(300, this->gameState->getContentSize().height/2));
        this->score_show->setColor(Color3B::RED);
        this->score_show->setString("1000分");
        
        this->gameState->addChild(this->score_show);
        
        return true;
    }
    return false;
}

void GameMain::changeBgImagePostion(cocos2d::Sprite *bgImage_m) {
    
    if (bgImage_m->getPosition().y <= 0) {
        bgImage_m->setPosition(Vec2(0, this->windowSize.height*2));
    } else {
        float yy = bgImage_m->getPosition().y;
        yy -= 1;
        bgImage_m->setPosition(Vec2(0, yy));
    }

}

void GameMain::updateBgImagePostion(float time) {

    this->changeBgImagePostion(this->bgImg);
    
    this->changeBgImagePostion(this->bgTop);
    

}

void GameMain::countTimeAndScore(float time) {

    this->time_m ++;
    this->score_m ++;
    
    char timeFormat[20];
    char scoreFormat[20];
    
    sprintf(timeFormat, "%.2d:%.2d",this->time_m/60,this->time_m%60);
    sprintf(scoreFormat, "%.3d分",this->score_m);
    
    this->time_show->setString(timeFormat);
    this->score_show->setString(scoreFormat);
    
    ScaleTo * max = ScaleTo::create(0.25, 1.5);
    ScaleTo * min = ScaleTo::create(0.25, 0.5);
    ScaleTo * start = ScaleTo::create(0.25, 1);
    Sequence* list = Sequence::create(max,min,start, NULL);
    
    this->score_show->runAction(list);
    
}

void GameMain::backToStartLayer(cocos2d::Ref *object) {

    TransitionRotoZoom* anmation = TransitionRotoZoom::create(1, StartLayer::createGameStartScent());
    Director::getInstance()->replaceScene(anmation);
    

}

void GameMain::pauseGame(cocos2d::Ref *object) {

    

}


