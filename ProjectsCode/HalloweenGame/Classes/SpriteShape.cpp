
#include "SpriteShape.h"


SpriteShape::SpriteShape()
: m_col(0)
, m_row(0)
, m_imgIndex(0)
, m_isNeedRemove(false)
, m_ignoreCheck(false)
, m_displayMode(DISPLAY_MODE_NORMAL)
{
}

SpriteShape *SpriteShape::create(int row, int col)
{
	SpriteShape *spr = new SpriteShape();
	spr->m_row = row;
	spr->m_col = col;
    spr->m_imgIndex = rand() % TOTAL_SP;
    spr->initWithSpriteFrameName(sprNormal[spr->m_imgIndex]);
	spr->autorelease();
	return spr;
}

void SpriteShape::setDisplayMode(DisplayMode mode)
{
	m_displayMode = mode;
    
    SpriteFrame *frame;
    switch (mode) {
        case DISPLAY_MODE_VERTICAL:
            frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(sprVertical[m_imgIndex]);
            break;
        case DISPLAY_MODE_HORIZONTAL:
            frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(sprHorizontal[m_imgIndex]);
            break;
        default:
            return;
    }
    setDisplayFrame(frame);
}