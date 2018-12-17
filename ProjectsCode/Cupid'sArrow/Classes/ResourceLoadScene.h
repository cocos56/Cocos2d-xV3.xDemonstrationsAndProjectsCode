#include "stdio.h"
#include "cocos2d.h"
USING_NS_CC;
class ResourceLoadScene : public cocos2d::Layer
{
public:
	virtual bool init();
	static Scene * createScence();
	CREATE_FUNC(ResourceLoadScene);

	void nextScene(float dt);
private:
	cocos2d::Label* label;

};

