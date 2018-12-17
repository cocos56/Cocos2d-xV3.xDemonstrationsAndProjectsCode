
#ifndef  _Inkmoo_GameScene_h_
#define  _Inkmoo_GameScene_h_

#include "cocos2d.h"
#include "GameDefine.h"

USING_NS_CC;

class SpriteShape;

class GameScene : public Layer
{
public:
	GameScene();
	static Scene* createScene();
	CREATE_FUNC(GameScene);
	int m_time;
	
	void myClock( float dt );
	virtual bool init();
	virtual void onEnter();
	virtual void onEnterTransitionDidFinish();
	virtual void onExit();
	virtual void onExitTransitionDidStart();
	virtual void cleanup();

	void update( float dt );
	bool onTouchBegan(Touch *touch, Event *unused);
    void onTouchMoved(Touch *touch, Event *unused);
	// 删除一行或者一列  加3秒时间
	void addTime();
	// 返回主界面
	void menuBackCallback(Ref *pSender);
	void menuSetCallback(Ref *pSender);
	void gameOver(float dt);
	CC_SYNTHESIZE(int, score, Score);

private:
	// 绘图的最下角坐标位置
	float mapLBX,mapLBY;
	// 绘制一批图片
	SpriteBatchNode *spriteSheet;
	// 二维数组
	SpriteShape* map[ROWS][COLS];
	// 判断是否在执行动作
	bool isAction;
	// 触摸事件是否可以执行
	bool isTouchEna;
	//是否有空缺需要填补
    bool isFillSprite;
	// 源精灵，目标精灵
	SpriteShape* staSprite;
	SpriteShape* endSprite;
	// true: 4消除产生纵向炸弹.  false: 4消除产生横向炸弹.
    bool fourBoom;


	// 创建精灵
	void createSprite( int row , int col );
	//得到对应行列精灵的坐标值
	Point positionOfItem(int row,int col);
	// 初始化二维数组
	void initMap();
	// 填补空缺位置
	void fillSprite();
	// 检查并移动精灵
	void checkAndRemoveSprite();
	// 移除精灵
	void removeSprite();
	// 检查Chain
	void getColChain(SpriteShape *spr, std::list<SpriteShape *> &chainList);
    void getRowChain(SpriteShape *spr, std::list<SpriteShape *> &chainList);
	// 
	void markRemove( SpriteShape* spr );
	// 爆炸
	void explodeSprite( SpriteShape* spr );
	void explodeSpecialH(Point point);
    void explodeSpecialV(Point point);
	//
	void actionEndCallback(Node *node);
	// 交换精灵
	void swapSprite();
	// 获取精灵位置
	SpriteShape *spriteOfPoint(Point *point);

	// 检测是否有可移动的精灵
	bool isHaveMove();
	int find( int r1 , int c1 , int r2 , int c2 , int r3 , int c3 );
};





#endif