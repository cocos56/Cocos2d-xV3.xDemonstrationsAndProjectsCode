//
//  StartLayer.cpp
//  testGame
//
//  Created by 姚龙 on 15/12/23.
//
//

#include "StartLayer.h"
#include "GameMain.h"

bool StartLayer::init() {

    if (Layer::init()) {
        
        this->windowSize = this->getContentSize();
        
        Sprite* nornal = Sprite::create("start.png");
        Sprite* selected = Sprite::create("start_selected.png");
        
        MenuItemSprite* startBtn = MenuItemSprite::create(nornal, selected, CC_CALLBACK_1(StartLayer::startAction, this));
        Menu* list = Menu::create(startBtn, NULL);
        
        list->setPosition(Vec2(this->windowSize.width/2, this->windowSize.height/2));
        
        this->addChild(list);
        
        
        
        
        return true;
    }

    return false;
}

Scene* StartLayer::createGameStartScent() {

    Scene* start = Scene::create();
    
    StartLayer* start_m = StartLayer::create();

    start->addChild(start_m);
    
    return start;
}


void StartLayer::startAction(Ref *object) {

    Director* dic = Director::getInstance();
    
    TransitionRotoZoom* roto = TransitionRotoZoom::create(1, GameMain::MainScene());
    
    dic->replaceScene(roto);

}

