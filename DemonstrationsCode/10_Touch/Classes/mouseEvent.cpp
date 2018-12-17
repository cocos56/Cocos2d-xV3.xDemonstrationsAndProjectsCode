#include "mouseEvent.h"


mouseEvent::mouseEvent(void)
{
}
mouseEvent::~mouseEvent(void)
{
}
Scene* mouseEvent::createScene()
{
    auto scene = Scene::create();
    auto layer = mouseEvent::create();
    scene->addChild(layer);
    return scene;
}
bool mouseEvent::init()
{
     if ( !Layer::init() )
    {
        return false;
    }
    auto bgsprite=Sprite::create("bg.jpg");
	bgsprite->setPosition(Vec2(240,160));
	addChild(bgsprite,0);
    
	this->_eventDispatcher->removeAllEventListeners();
    auto listener=EventListenerMouse::create();
    listener->onMouseDown = CC_CALLBACK_1(mouseEvent::onMouseDownss, this);
    listener->onMouseMove = CC_CALLBACK_1(mouseEvent::onMouseMoved, this);
    listener->onMouseScroll = CC_CALLBACK_1(mouseEvent::onMouseScrollss, this);
    listener->onMouseUp =CC_CALLBACK_1(mouseEvent::onMouseUpss, this);
    this->_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    return true;
}

void mouseEvent::onMouseDownss(Event *ev)
{
    log("onMouseDownss!");
}
void mouseEvent::onMouseMoved(Event *ev)
{
    log("onMouseMoved");
}
void mouseEvent::onMouseUpss(Event *ev)
{
    log("onMouseUpss");
}
void mouseEvent::onMouseScrollss(Event *ev)
{
    log("onMouseScrollss");
}