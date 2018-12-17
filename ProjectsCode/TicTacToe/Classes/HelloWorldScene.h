#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "Card.h"

class HelloWorld : public cocos2d::Layer
{
public:
    
    static cocos2d::Scene* createScene();

    virtual bool init();  
   
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    CREATE_FUNC(HelloWorld);

	//添加卡片
	void addCard();

	//判断游戏是否结束
	void isGameOver(); 

	//重新开始游戏
	void reStart();

private:
	Size visibleSize;
	Point origin;

	 //记录点击的次数，奇数次的为图案1，偶数次的为图案2
	int count;

	//卡片二维数组，方便操作
	Card *cardArr[3][3];

	//用于初始化图案标记
	int initPatternNum;
	
    Vector<Card*> *c;  
};

#endif // __HELLOWORLD_SCENE_H__