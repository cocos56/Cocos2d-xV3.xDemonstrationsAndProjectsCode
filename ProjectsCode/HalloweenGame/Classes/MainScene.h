
#ifndef  _Inkmoo_MainScene_h_
#define  _Inkmoo_MainScene_h_

#include "cocos2d.h"
#include "GameDefine.h"

USING_NS_CC;

class MainScene : public Layer
{
public:
	static Scene* createScene();
	CREATE_FUNC(MainScene);
	virtual bool init();
	virtual void onEnter();
	virtual void onEnterTransitionDidFinish();
	virtual void onExit();
	virtual void onExitTransitionDidStart();
	virtual void cleanup();

	void menuStartCallback(Ref *pSender);
	void menuSetCallback(Ref *pSender);
	void menuExitCallback(Ref *pSender);
};

#endif