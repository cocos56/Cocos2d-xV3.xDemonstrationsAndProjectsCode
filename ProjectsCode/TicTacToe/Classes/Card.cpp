#include "Card.h"


USING_NS_CC;  
  
Vector<Card*> *Card::cards = new Vector<Card*>();  
  
Card* Card::createCards(Color3B bgColor,Size cardSize)  
{  
    auto card = new Card();  
    card->init(bgColor,cardSize);  
    card->autorelease();  
	card->flag = 0;

    cards->pushBack(card);  
  
    return card;  
}  
  
  
bool Card::init(Color3B bgColor,Size cardSize)  
{  
    Sprite::init();  
  
    lineIndex = 0;  
    setContentSize(cardSize);  
	cSize = cardSize;
    setAnchorPoint(Point::ZERO);  
    setTextureRect(Rect(0,0,cardSize.width,cardSize.height));  
    setColor(bgColor);  
  
    return true;  
}  
  
Vector<Card*> * Card::getCard()  
{  
    return cards;  
}  
   
void Card::renewVector()  
{  
    cards->clear();  
}  

//显示图案1
void Card::showO()
{
	auto s = Sprite::create("sun.png");
	s->setPosition(Point(cSize.width/2,cSize.height/2));
	addChild(s);
}

//显示图案2
void Card::showX()
{
	auto r = Sprite::create("moon.png");
	r->setPosition(Point(cSize.width/2,cSize.height/2));
	addChild(r);
}


//设定图案标记
void Card::setFlag(int i)
{
	this->flag = i;
}

//获取标记数字
int Card::getFlag()
{
	return this->flag;
}

//设定图案标记
void Card::setPattern(int num)
{
	this->pattern = num;
}

//获取图案标记
int Card::getPattern()
{
	return this->pattern;
}