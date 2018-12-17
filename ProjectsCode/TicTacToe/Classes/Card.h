#include "cocos2d.h"

USING_NS_CC;

class Card : public Sprite
{
public:
	static Card* createCards(Color3B bgColor,Size cardSize);  
    virtual bool init(Color3B bgColor,Size cardSize);  
  
    void setLineIndex(int index);  
    int getLineIndex();  
  
    void removeCard();  
  
    //获取向量里的对象  
    static Vector<Card*> *getCard();  
  
    //清空向量  
    static void renewVector();  

    //显示图案1
   void showO();

   //显示图案2
   void showX();

   //设定标记判断是否应经按下
   void setFlag(int i);
   //获取标记数字  ,标记是否有图片
   int getFlag();

   //设定图案标记，标记图片颜色

   void setPattern(int num);
   //获取图案标记
   int getPattern();

private:  
  
    //用向量存放Card  
    static Vector<Card*> *cards;  
  
    //记录卡片所在的行  
    int lineIndex;  

	//Card的Size
	 Size cSize;

	 //判定是否应经被按下
	 int flag;
  
	 //判断当前卡片是什么图案,0是圈，1是叉
	 int pattern;
};