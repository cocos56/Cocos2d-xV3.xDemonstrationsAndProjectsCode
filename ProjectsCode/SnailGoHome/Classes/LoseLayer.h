#include "cocos2d.h"
using namespace cocos2d;
class LoseLayer : public LayerColor
{
public:
	virtual bool init();
	CREATE_FUNC(LoseLayer);
	void clickButton(Ref* sender);

private:
	Size size;
};