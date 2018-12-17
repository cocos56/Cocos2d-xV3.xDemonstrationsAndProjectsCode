#pragma once
#include "cocos2d.h"
USING_NS_CC;
class spriteTouch :	public Sprite
{
public:
	spriteTouch(void);
	~spriteTouch(void);
private:
    // 事件监听器
    EventListener* _listener;
    // 优先级
    int _fixedPriority;
    // 用于保存精灵的图片名称，便于观察结果
    const char* _name;
    
public:
    // ①设置优先级和名称的函数
    void setPriority(int fixedPriority,const char* name);
	 void onEnter() override;
	 void onExit() override;
	 CREATE_FUNC(spriteTouch);

};
