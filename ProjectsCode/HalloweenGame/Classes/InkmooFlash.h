#ifndef Inkmoo_InkmooFlash_h
#define Inkmoo_InkmooFlash_h

#include "cocos2d.h"

USING_NS_CC;

class InkmooFlash : public LayerColor
{
public:
	static Scene* createScene( );
	void jumpToMain( float t );
	virtual bool init();
	CREATE_FUNC(InkmooFlash);
};


#endif