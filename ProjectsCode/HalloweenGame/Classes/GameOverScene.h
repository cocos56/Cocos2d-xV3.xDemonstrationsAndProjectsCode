
#ifndef  _Inkmoo_GameOver_h_
#define  _Inkmoo_GameOver_h_

#include "cocos2d.h"
#include "GameDefine.h"

USING_NS_CC;

class GameOver : public Layer
{
public:
	static Scene* createScene();
	CREATE_FUNC(GameOver);
	virtual bool init();

	void setScore( int sc );
	void menuRestartCallback(Ref *pSender);
	void menuBackCallback( Ref *pSender );
};




#endif