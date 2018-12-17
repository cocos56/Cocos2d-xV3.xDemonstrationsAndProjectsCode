#ifndef  _Inkmoo_Developer_h_
#define  _Inkmoo_Developer_h_

#include "cocos2d.h"
#include "GameDefine.h"

USING_NS_CC;

class Developer : public Layer
{
public:
	static Scene* createScene();
	CREATE_FUNC(Developer);
	virtual bool init();
	virtual void onEnter();
	virtual void onEnterTransitionDidFinish();
	virtual void onExit();
	virtual void onExitTransitionDidStart();
	virtual void cleanup();

	void menuBackCallback( Ref *pSender );
	void menuMusicCallback( Ref *pSender );
	void menuSoundCallback( Ref *pSender );
};


#endif