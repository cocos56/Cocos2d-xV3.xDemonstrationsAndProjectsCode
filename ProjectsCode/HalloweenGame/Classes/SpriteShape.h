
#ifndef  _Inkmoo_SpriteShape_h_
#define  _Inkmoo_SpriteShape_h_

#include "cocos2d.h"
#include "GameDefine.h"

USING_NS_CC;

class SpriteShape : public Sprite
{
public:
	SpriteShape();
	static SpriteShape* create( int row , int col );

	CC_SYNTHESIZE(int, m_row, Row);
    CC_SYNTHESIZE(int, m_col, Col);
    CC_SYNTHESIZE(int, m_imgIndex, ImgIndex);
	CC_SYNTHESIZE(bool, m_isNeedRemove, IsNeedRemove);
    
	//新产生的4消寿司，本轮不被消除
	CC_SYNTHESIZE(bool, m_ignoreCheck, IgnoreCheck);
    CC_SYNTHESIZE_READONLY(DisplayMode, m_displayMode, DisplayMode);
    void setDisplayMode(DisplayMode mode);
};




#endif