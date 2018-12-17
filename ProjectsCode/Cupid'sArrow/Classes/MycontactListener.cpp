#include "MycontactListener.h"


bool MycontactListener::iscollision(Sprite *sprite2,Sprite *sprite1){
	auto rect1 = sprite1->boundingBox();
	auto rect2 = sprite2->boundingBox();
	Vec2 v2(rect2.getMidX(),rect2.getMidY());
	//return rect1.intersectsRect(rect2);
	return rect1.containsPoint(v2);
}
