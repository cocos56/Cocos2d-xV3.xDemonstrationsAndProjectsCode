#pragma once
#include "cocos2d.h"
USING_NS_CC;
#include "ui/CocosGUI.h"
using namespace ui;
class gameScene :public Layer
{

public:
	static Scene * createScene();
	virtual bool init();
	CREATE_FUNC(gameScene);
    virtual bool onTouchBegan(Touch *touch, Event *unused_event); 
    virtual void onTouchMoved(Touch *touch, Event *unused_event); 
    virtual void onTouchEnded(Touch *touch, Event *unused_event); 
	//设置物理世界
	void setPhysicsWorld(PhysicsWorld *_world);
	void createPhysicsBody(Node *sprite);
	bool onContactBegin(PhysicsContact &contact);
	void update(float f);//定时器必须带一个float类型的参数
	void pauseBack(Ref * sender);//定义方法时，注意不要和引擎封装好的方法重名，这里就不能直接定义为pause（）；因为引擎已经封装好了这个方法
private:
	Size size;
	__Array *body_array;
	Node *snail;
	__Array *star_array;
	int star_Num;
	Sprite *star;
	Widget *house;
};

