#include "cocos2d.h"
using namespace cocos2d;
class WinLayer : public LayerColor
{
public:
	virtual bool init();
	CREATE_FUNC(WinLayer);
	void clickButton(Ref* sender);
	static void setstarNum(int starNum);
private:
	static int win_star;//为了保存通关星星的数量（static只初始化一次，保留数据）
	Size size;
};