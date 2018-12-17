
#include "GameScene.h"
#include "SpriteShape.h"
#include "MainScene.h"
#include "GameOverScene.h"

using namespace CocosDenshion;

GameScene::GameScene()
: spriteSheet(NULL)
, m_time(60)
, score(0)
, isFillSprite(false)
, isAction(true)//start with drop animation
, isTouchEna(true)
, staSprite(NULL)
, endSprite(NULL)
, fourBoom(true)//drop animation is vertical
{
}

Scene* GameScene::createScene( )
{
	auto scene = Scene::create();
	auto layer = GameScene::create();
	scene -> addChild( layer );
	return scene;
}

bool GameScene::init( )
{
	if( !Layer::init() ){
		return false;
	}

	// 添加背景图片
	auto sprite = Sprite::create("scene_bg.png");
	sprite->setPosition(Point(GAME_SCREEN_WIDTH/2,GAME_SCREEN_HEIGHT/2));
    this->addChild(sprite,-1);

	// 添加返回按钮
	auto backItem = MenuItemImage::create(
                                           "btn_back01.png",
                                           "btn_back02.png",
										   CC_CALLBACK_1(GameScene::menuBackCallback, this));
	backItem->setPosition(Vec2(GAME_SCREEN_WIDTH-backItem->getContentSize().width/2,backItem->getContentSize().height/2));

	
	
	auto menu = Menu::create(backItem, NULL);
    menu->setPosition(Vec2::ZERO);
	this -> addChild( menu );

	if(!userDefault->getIntegerForKey("Int")){
		 userDefault->setIntegerForKey("Int",0);
	}

	TTFConfig config("haibaoti.ttf",30);
	// 最高分
	auto labelHScore = Label::createWithTTF(config, "Highest: 0");
	labelHScore -> setPosition(Vec2( GAME_SCREEN_WIDTH - labelHScore->getContentSize().width , GAME_SCREEN_HEIGHT - labelHScore->getContentSize().height ));
	labelHScore -> setString( StringUtils::format("Highest: %d ",userDefault->getIntegerForKey("Int")));
	this->addChild(labelHScore);

	// 分数
	auto labelScore = Label::createWithTTF(config,"Score: 0");
	labelScore -> setPosition(Vec2( GAME_SCREEN_WIDTH/2 , GAME_SCREEN_HEIGHT - labelScore->getContentSize().height*2.6 ));
	labelScore -> setTag(10);
	this->addChild(labelScore);

	// 时间
	auto labelTime = Label::createWithTTF(config,"Time: 60");
	labelTime -> setPosition(Vec2( labelTime->getContentSize().width , GAME_SCREEN_HEIGHT - labelTime->getContentSize().height ));
	labelTime -> setTag(11);
	this ->addChild(labelTime);
	

	// 初始化坐标值
	mapLBX = (GAME_SCREEN_WIDTH - SPRITE_WIDTH * COLS - (COLS - 1) * BOADER_WIDTH) / 2;
	mapLBY = (GAME_SCREEN_HEIGHT - SPRITE_WIDTH * ROWS - (ROWS - 1) * BOADER_WIDTH) / 2;

	// 加载plist和png
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("icon.plist");
    spriteSheet = SpriteBatchNode::create("icon.png");
    addChild(spriteSheet);

	initMap();
	scheduleUpdate();
	schedule(schedule_selector(GameScene::myClock),1.0f );

	// 触摸事件处理
    auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->onTouchBegan = CC_CALLBACK_2(GameScene::onTouchBegan, this);
    touchListener->onTouchMoved = CC_CALLBACK_2(GameScene::onTouchMoved, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);

	return true;
}

void GameScene::createSprite( int row , int col )
{
	// 先创建一个寿司
	SpriteShape *spr = SpriteShape::create(row, col);
    
    // 创建动作动画
    Point endPosition = positionOfItem(row, col);
	Point startPosition = Point(endPosition.x, endPosition.y + GAME_SCREEN_HEIGHT / 2);
    spr->setPosition(startPosition);
	float speed = startPosition.y / (1.5 * GAME_SCREEN_HEIGHT );
    spr->runAction(MoveTo::create(speed, endPosition));
    // 加入到spriteSheet中,等待绘制
    spriteSheet->addChild(spr);

	// 数组相应位置，置上寿司对象
    map[row][col] = spr;
	
}

// 获取坐标值
Point GameScene::positionOfItem(int row, int col)
{
	float x = mapLBX + (SPRITE_WIDTH + BOADER_WIDTH) * col + SPRITE_WIDTH / 2;
    float y = mapLBY + (SPRITE_WIDTH + BOADER_WIDTH) * row + SPRITE_WIDTH / 2;
    return Point(x, y);
}

// 初始化二维数组
void GameScene::initMap( )
{
	for( int r = 0 ; r < ROWS ; ++r ){
		for( int c = 0 ; c < COLS ; ++c ){
			createSprite(r,c);
		}
	}
}

// 更新函数
void GameScene::update( float t )
{
	 // 检测是否在执行动作
	if ( isAction ) {
        // 设置为false
        isAction = false;
		for( int r = 0 ; r < ROWS ; ++r )	{
			for( int c = 0  ; c < COLS ; ++c )	{
				SpriteShape* spr = map[r][c];
				if (spr && spr->getNumberOfRunningActions() > 0) {
					isAction = true;
					break;
				}
			}
		}
	}
    
    // 如果寿司正在移动中，忽视触摸事件
	isTouchEna = !isAction;
    
    if (!isAction) {
		if ( isFillSprite ) {
            //爆炸效果结束后才掉落新寿司，增强打击感
            fillSprite();
            isFillSprite = false;

			// 检测有没有可移动精灵
			if( isHaveMove() == false )
			{
				for( int r = 0 ; r < ROWS ; ++r )
					for( int c = 0 ; c < COLS ; ++c )
						map[r][c]->setIsNeedRemove(true);
				removeSprite();
			}
        } else {
            checkAndRemoveSprite();
        }
    }

	// 分数变化
	Label *labelScore = (Label *)this -> getChildByTag(10);
	labelScore -> setString( StringUtils::format("Score: %d ",this->getScore()));

}

void GameScene::fillSprite()
{
	 // 重置移动方向标志
    fourBoom = true;
    isAction = true;
    int sum = 0;

    int *colEmptyInfo = (int *)malloc(sizeof(int) * COLS);
    memset((void *)colEmptyInfo, 0, sizeof(int) * COLS);
    
    // 将存在的寿司降落下来
	SpriteShape *spr = NULL;
    for (int c = 0; c < COLS; c++) {
        int removedSpriteOfCol = 0;
        // 自底向上
        for (int r = 0; r < ROWS; r++ ) {
            spr = map[r][c];
            if ( spr == NULL ) {
                ++removedSpriteOfCol;
            } else {
                if ( removedSpriteOfCol > 0) {
                    // evey item have its own drop distance
                    int newRow = r - removedSpriteOfCol;
                    // switch in matrix
                    map[newRow][c] = spr;
                    map[r][c] = NULL;
                    // move to new position
                    Point startPosition = spr->getPosition();
                    Point endPosition = positionOfItem(newRow, c);
					float speed = (startPosition.y - endPosition.y) / GAME_SCREEN_HEIGHT*3;
                    spr->stopAllActions();// must stop pre drop action
                    spr->runAction(CCMoveTo::create(speed, endPosition));
                    // set the new row to item
                    spr->setRow(newRow);
                }
            }
        }
        
        // 记录相应列数移除的数量
        colEmptyInfo[c] = removedSpriteOfCol;
		sum+=removedSpriteOfCol;
    }
    
    // 新建新的寿司，并降落
    for (int c = 0; c < COLS; ++c ) {
        for (int r = ROWS - colEmptyInfo[c]; r < ROWS ; ++r ) {
            createSprite(r,c);
        }
    }
    
	setScore(getScore()+sum*30);
    free(colEmptyInfo);
}

void GameScene::checkAndRemoveSprite()
{
	SpriteShape *spr;
    // 设定寿司的忽视检查
	for( int r = 0 ; r < ROWS ; ++r )	{
		for( int c = 0 ; c < COLS ; ++c )	{
			spr = map[r][c];
			if( !spr )	{
				continue;
			}
			spr -> setIgnoreCheck(false);
		}
	}

	for( int r = 0 ; r < ROWS ; ++r )	{
		for( int c = 0 ; c < COLS ; ++c )	{
			spr = map[r][c];
			if( !spr )	{
				continue;
			}

			if( spr -> getIsNeedRemove() )	{
				continue;
			}

			if ( spr -> getIgnoreCheck() ) {
				continue;// 新变化的特殊寿司，不消除
			}
			std::list< SpriteShape *> colChainList;
			getColChain( spr , colChainList );

			std::list< SpriteShape *> rowChainList;
			getRowChain( spr , rowChainList );

			std::list< SpriteShape *> &longerList = colChainList.size() > rowChainList.size() ? colChainList : rowChainList;
			if( longerList.size() < 3 )	{
				continue;
			}

			std::list<SpriteShape *>::iterator itList;
			bool isSetedIgnoreCheck = false;

			for( itList = longerList.begin() ; itList != longerList.end() ; ++itList ) {
				spr = ( SpriteShape * )* itList;
				if( !spr )	{
					continue;
				}

				if( longerList.size() > 3 )	{
					if ( spr == staSprite || spr == endSprite ) {
						isSetedIgnoreCheck = true;
						spr->setIgnoreCheck(true);
						spr->setIsNeedRemove(false);
						spr->setDisplayMode( fourBoom ? DISPLAY_MODE_VERTICAL : DISPLAY_MODE_HORIZONTAL);
						continue;
					}
				}
				markRemove( spr );
			}   
			// 如何是自由掉落产生的4消, 取最后一个变化为特殊寿司
			if (!isSetedIgnoreCheck && longerList.size() > 3) {
				spr -> setIgnoreCheck(true);
				spr -> setIsNeedRemove(false);
				spr -> setDisplayMode( fourBoom ? DISPLAY_MODE_VERTICAL : DISPLAY_MODE_HORIZONTAL);
			}
		}
	}

	// 3.消除标记了的寿司
	removeSprite();
}

// 移除寿司
void GameScene::removeSprite()
{
	// 做一套移除的动作
    isAction = true;
    
	for( int r = 0 ; r < ROWS ; ++r )	{
		for( int c = 0 ; c < COLS ; ++c )	{
			SpriteShape* spr = map[r][c];
			if( !spr )	{
				continue;
			}

			if( spr -> getIsNeedRemove() )	{
				isFillSprite = true;

				if( spr -> getDisplayMode() == DISPLAY_MODE_HORIZONTAL)
				{
					this->m_time += 3;
					addTime();
					explodeSpecialH( spr -> getPosition() );
				}
				else if ( spr -> getDisplayMode() == DISPLAY_MODE_VERTICAL)
				{
					this->m_time += 3;
					addTime();
					explodeSpecialV( spr -> getPosition() );
				}
				explodeSprite( spr );
			}
		}
	}
}

void GameScene::markRemove( SpriteShape* spr )
{
	if ( spr -> getIsNeedRemove()) {
        return;
    }
    if ( spr -> getIgnoreCheck() ) {
        return;
    }
    
    // mark self
    spr -> setIsNeedRemove(true);
    // check for type and mark for certical neighbour
    if ( spr ->getDisplayMode() == DISPLAY_MODE_VERTICAL) {
        for ( int r = 0; r < ROWS ; ++r ) {
			SpriteShape* tmp = map[r][spr->getCol()];
            if ( !tmp || tmp == spr ) {
                continue;
            }
            
            if (tmp->getDisplayMode() == DISPLAY_MODE_NORMAL) {
                tmp->setIsNeedRemove(true);
            } else {
                markRemove(tmp);
            }
        }
    // check for type and mark for horizontal neighbour
    } else if ( spr -> getDisplayMode() == DISPLAY_MODE_HORIZONTAL) {
        for (int c = 0; c < COLS ; ++c ) {
            SpriteShape *tmp = map[ spr -> getRow()][c];
            if (!tmp || tmp == spr) {
                continue;
            }
            
            if (tmp->getDisplayMode() == DISPLAY_MODE_NORMAL) {
                tmp->setIsNeedRemove(true);
            } else {
                markRemove(tmp);
            }
        }
    }
}

void GameScene::explodeSprite( SpriteShape* spr )
{
	if (UserDefault::getInstance()->getBoolForKey(SOUND_KEY)) {                      
        SimpleAudioEngine::getInstance()->playEffect("music_explode.wav",false);  
    }

	float time = 0.2;
    
    // 精灵的动作
    spr->runAction(Sequence::create(
                                      ScaleTo::create(time, 0.0),
									  CallFuncN::create(CC_CALLBACK_1(GameScene::actionEndCallback, this)),
                                      NULL));
    
    // 爆炸效果 圆圈的动作
    auto circleSprite = Sprite::create("circle.png");
	addChild(circleSprite, 10);
	circleSprite->setPosition(spr->getPosition());
	circleSprite->setScale(0);// start size
    circleSprite->runAction(Sequence::create(ScaleTo::create(time, 1.0),
                                             CallFunc::create(CC_CALLBACK_0(Sprite::removeFromParent, circleSprite)),
                                             NULL));

	
}

void GameScene::explodeSpecialH(Point point)
{
	if (UserDefault::getInstance()->getBoolForKey(SOUND_KEY)) {                      
        SimpleAudioEngine::getInstance()->playEffect("music_explodeOne.wav",false);  
    }

    float scaleX = 4 ;
    float scaleY = 0.7 ;
    float time = 0.3;
    Point startPosition = point;
    float speed = 0.6f;
    
    auto colorSpriteRight = Sprite::create("colorHRight.png");
	addChild(colorSpriteRight, 10);
	Point endPosition1 = Point(point.x - GAME_SCREEN_WIDTH, point.y);
    colorSpriteRight->setPosition(startPosition);
    colorSpriteRight->runAction(Sequence::create(ScaleTo::create(time, scaleX, scaleY),
                                             MoveTo::create(speed, endPosition1),
                                             CallFunc::create(CC_CALLBACK_0(Sprite::removeFromParent, colorSpriteRight)),
                                             NULL));
    
    auto colorSpriteLeft = Sprite::create("colorHLeft.png");
	addChild(colorSpriteLeft, 10);
    Point endPosition2 = Point(point.x + GAME_SCREEN_WIDTH, point.y);
    colorSpriteLeft->setPosition(startPosition);
    colorSpriteLeft->runAction(Sequence::create(ScaleTo::create(time, scaleX, scaleY),
                                             MoveTo::create(speed, endPosition2),
                                             CallFunc::create(CC_CALLBACK_0(Sprite::removeFromParent, colorSpriteLeft)),
                                             NULL));
    
	
}

void GameScene::explodeSpecialV(Point point)
{
	if (UserDefault::getInstance()->getBoolForKey(SOUND_KEY)) {                      
        SimpleAudioEngine::getInstance()->playEffect("music_explodeOne.wav",false);  
    }

    float scaleY = 4 ;
    float scaleX = 0.7 ;
    float time = 0.3;
    Point startPosition = point;
    float speed = 0.6f;

    auto colorSpriteDown = Sprite::create("colorVDown.png");
	addChild(colorSpriteDown, 10);
	Point endPosition1 = Point(point.x , point.y - GAME_SCREEN_HEIGHT);
    colorSpriteDown->setPosition(startPosition);
    colorSpriteDown->runAction(Sequence::create(ScaleTo::create(time, scaleX, scaleY),
                                             MoveTo::create(speed, endPosition1),
                                             CallFunc::create(CC_CALLBACK_0(Sprite::removeFromParent, colorSpriteDown)),
                                             NULL));
    
    auto colorSpriteUp = Sprite::create("colorVUp.png");
	addChild(colorSpriteUp, 10);
    Point endPosition2 = Point(point.x , point.y + GAME_SCREEN_HEIGHT);
    colorSpriteUp->setPosition(startPosition);
    colorSpriteUp->runAction(Sequence::create(ScaleTo::create(time, scaleX, scaleY),
                                             MoveTo::create(speed, endPosition2),
                                             CallFunc::create(CC_CALLBACK_0(Sprite::removeFromParent, colorSpriteUp)),
                                             NULL));

	
}

void GameScene::actionEndCallback(Node *node)
{
	SpriteShape *spr = (SpriteShape *)node;
	map[spr->getRow()][spr->getCol()] = NULL;
	spr -> removeFromParent();
}

void GameScene::swapSprite()
{
	// 移动中，不允许再次触摸，执行动作设置为true
    isAction = true;
    isTouchEna = false;

	if (!staSprite || !endSprite) {
        fourBoom = true;
        return;
    }
    
	Point posOfSrc = staSprite->getPosition();
	Point posOfDest = endSprite->getPosition();

    float time = 0.2;
    
    // 在数组中交换位置
	map[ staSprite -> getRow() ][staSprite -> getCol() ] = endSprite;
	map[ endSprite -> getRow() ][endSprite -> getCol() ] = staSprite;

    int tmpRow = staSprite->getRow();
    int tmpCol = staSprite->getCol();
    staSprite->setRow(endSprite->getRow());
    staSprite->setCol(endSprite->getCol());
    endSprite->setRow(tmpRow);
    endSprite->setCol(tmpCol);
    
    // 检查是否能消除
	std::list<SpriteShape *> colChainListOfFirst;
    getColChain(staSprite, colChainListOfFirst);
    
    std::list<SpriteShape *> rowChainListOfFirst;
    getRowChain(staSprite, rowChainListOfFirst);
    
    std::list<SpriteShape *> colChainListOfSecond;
    getColChain(endSprite, colChainListOfSecond);
    
    std::list<SpriteShape *> rowChainListOfSecond;
    getRowChain(endSprite, rowChainListOfSecond);
    
    if (colChainListOfFirst.size() >= 3
        || rowChainListOfFirst.size() >= 3
        || colChainListOfSecond.size() >= 3
        || rowChainListOfSecond.size() >= 3) {
        // 如果能够消除，仅仅进行移动（不会移动回来）
        staSprite->runAction(MoveTo::create(time, posOfDest));
        endSprite->runAction(MoveTo::create(time, posOfSrc));
        return;
    }
    
    // 不能消除，则移动过去还要返回
	map[ staSprite -> getRow()][staSprite -> getCol() ] = endSprite;
	map[ endSprite -> getRow()][endSprite -> getCol() ] = staSprite;

    tmpRow = staSprite->getRow();
    tmpCol = staSprite->getCol();
    staSprite->setRow(endSprite->getRow());
    staSprite->setCol(endSprite->getCol());
    endSprite->setRow(tmpRow);
    endSprite->setCol(tmpCol);
    
    staSprite->runAction(Sequence::create(
                                      MoveTo::create(time, posOfDest),
                                      MoveTo::create(time, posOfSrc),
                                      NULL));
    endSprite->runAction(Sequence::create(
                                      MoveTo::create(time, posOfSrc),
                                      MoveTo::create(time, posOfDest),
                                      NULL));
}

SpriteShape *GameScene::spriteOfPoint(Point *point)
{
    SpriteShape *spr = NULL;
    Rect rect = Rect(0, 0, 0, 0);
	Size sz;
	sz.height=SPRITE_WIDTH;
	sz.width=SPRITE_WIDTH;

	for( int r = 0 ; r < ROWS ; ++r )	{
		for( int c = 0 ; c < COLS ; ++c )	{
			spr = map[r][c];
			if( spr )	{
				rect.origin.x = spr->getPositionX() - ( SPRITE_WIDTH / 2);
				rect.origin.y = spr->getPositionY() - ( SPRITE_WIDTH / 2);

				rect.size = sz;
				if (rect.containsPoint(*point)) {
					return spr;
				}
			}
		}
	}
    
    return NULL;
}

bool GameScene::onTouchBegan(Touch *touch, Event *unused)
{
	staSprite = NULL;
	endSprite = NULL;

	if ( isTouchEna ) {
        auto location = touch->getLocation();
		staSprite = spriteOfPoint(&location);
    }
	return isTouchEna;
}

void GameScene::onTouchMoved(Touch *touch, Event *unused)
{
	if (!staSprite || !isTouchEna) {
        return;
    }
    
    int row = staSprite->getRow();
    int col = staSprite->getCol();
    
    auto location = touch->getLocation();
    auto halfSpriteWidth = SPRITE_WIDTH / 2;
    auto halfSpriteHeight = SPRITE_WIDTH / 2;
    
    auto  upRect = Rect(staSprite->getPositionX() - halfSpriteWidth,
                        staSprite->getPositionY() + halfSpriteHeight,
                        SPRITE_WIDTH,
                        SPRITE_WIDTH);
    
    if (upRect.containsPoint(location)) {
        ++row;
        if ( row < ROWS ) {
            endSprite = map[row][col];
        }
        fourBoom = true;
        swapSprite();
        return;
    }
    
    auto  downRect = Rect(staSprite->getPositionX() - halfSpriteWidth,
                        staSprite->getPositionY() - (halfSpriteHeight * 3),
                        SPRITE_WIDTH,
                        SPRITE_WIDTH);
    
    if (downRect.containsPoint(location)) {
        --row;
        if ( row >= 0 ) {
            endSprite = map[row][col];
        }
        fourBoom = true;
        swapSprite();
        return;
    }
    
    auto  leftRect = Rect(staSprite->getPositionX() - (halfSpriteWidth * 3),
                          staSprite->getPositionY() - halfSpriteHeight,
                          SPRITE_WIDTH,
						  SPRITE_WIDTH);
    
    if (leftRect.containsPoint(location)) {
        --col;
        if ( col >= 0 ) {
            endSprite = map[row][col];
        }
        fourBoom = true;
        swapSprite();
        return;
    }
    
    auto  rightRect = Rect(staSprite->getPositionX() + halfSpriteWidth,
                          staSprite->getPositionY() - halfSpriteHeight,
                          SPRITE_WIDTH,
                          SPRITE_WIDTH);
    
    if (rightRect.containsPoint(location)) {
        ++col;
        if ( col < COLS ) {
			endSprite = map[row][col];
        }
        fourBoom = true;
        swapSprite();
        return;
    }
    
    // 否则，并非一个有效的移动
}

void GameScene::getColChain(SpriteShape *spr, std::list<SpriteShape *> &chainList)
{
	// 添加第一个寿司（自己）
    chainList.push_back(spr);
    
	// 向左查找
    int neighborCol = spr->getCol() - 1;
    while (neighborCol >= 0) {
        SpriteShape *neighborSprite = map[spr->getRow()][neighborCol];
        if (neighborSprite
            && (neighborSprite->getImgIndex() == spr->getImgIndex())
            && !neighborSprite->getIsNeedRemove()
            && !neighborSprite->getIgnoreCheck()) {
            chainList.push_back(neighborSprite);
            neighborCol--;
        } else {
            break;
        }
    }
    
	// 向右查找
    neighborCol = spr->getCol() + 1;
    while (neighborCol < COLS) {
        SpriteShape *neighborSprite = map[spr->getRow()][neighborCol];
		if (neighborSprite
            && (neighborSprite->getImgIndex() == spr->getImgIndex())
            && !neighborSprite->getIsNeedRemove()
            && !neighborSprite->getIgnoreCheck()) {
            chainList.push_back(neighborSprite);
            neighborCol++;
        } else {
            break;
        }
    }
}

void GameScene::getRowChain(SpriteShape *spr, std::list<SpriteShape *> &chainList)
{
	chainList.push_back(spr);// add first sushi
    
    int neighborRow = spr->getRow() - 1;
    while (neighborRow >= 0) {
        SpriteShape *neighborSprite = map[neighborRow][spr->getCol()];
        if (neighborSprite
            && (neighborSprite->getImgIndex() == spr->getImgIndex())
            && !neighborSprite->getIsNeedRemove()
            && !neighborSprite->getIgnoreCheck()) {
            chainList.push_back(neighborSprite);
            neighborRow--;
        } else {
            break;
        }
    }
    
    neighborRow = spr->getRow() + 1;
    while (neighborRow < ROWS) {
        SpriteShape *neighborSprite = map[neighborRow][spr->getCol()];
        if (neighborSprite
            && (neighborSprite->getImgIndex() == spr->getImgIndex())
            && !neighborSprite->getIsNeedRemove()
            && !neighborSprite->getIgnoreCheck()) {
            chainList.push_back(neighborSprite);
            neighborRow++;
        } else {
            break;
        }
    }
}

void GameScene::menuBackCallback( Ref *pSender )
{
	auto scene = MainScene::createScene();
	CCTransitionScene* reScene = CCTransitionMoveInR::create(1.0f, scene);
    CCDirector::sharedDirector()->replaceScene(reScene);
}

void GameScene::myClock( float dt )
{
	// 时间变化
	--m_time;
	if( m_time == 0 )
	{
		SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic(); 
		if (UserDefault::getInstance()->getBoolForKey(SOUND_KEY)) {                      
			SimpleAudioEngine::getInstance()->playEffect("music_gameOver.mp3",false);  
		}

		Label *labelTime = (Label *)this -> getChildByTag(11);
		labelTime->setScale(0);

		// 游戏结束 动画
		auto gmov = Sprite::create("pic_gameover.png");
		gmov->setPosition(Point(GAME_SCREEN_WIDTH/2,GAME_SCREEN_HEIGHT*1.5));
		this->addChild(gmov);

		auto action = MoveTo::create(3.0f, Point(GAME_SCREEN_WIDTH/2, GAME_SCREEN_HEIGHT/2));  

		gmov -> runAction( action );

		scheduleOnce(schedule_selector(GameScene::gameOver),3.5f);
		return;
	}
	if( m_time > 0 )	{
		Label *labelTime = (Label *)this -> getChildByTag(11);
		labelTime -> setString( StringUtils::format("Time: %d ",m_time));
	}
}

bool GameScene::isHaveMove()
{
	for( int r = 0 ; r < ROWS ; ++r )	{
		for( int c = 0 ; c < COLS ; ++c )	{
			if( map[r][c]->getImgIndex() == find(r,c-1,r-1,c+1,r+1,c+1) )
				return true;
			if( map[r][c]->getImgIndex() == find(r,c+1,r-1,c-1,r+1,c-1) )
				return true;
			if( map[r][c]->getImgIndex() == find(r-1,c,r+1,c-1,r+1,c+1) )
				return true;
			if( map[r][c]->getImgIndex() == find(r+1,c,r-1,c-1,r-1,c+1) )
				return true;
		}
	}
	return false;
}

int GameScene::find( int r1 , int c1 , int r2 , int c2 , int r3 , int c3 )
{
	bool isr1,isr2,isr3;
	isr1 = false;
	isr2 = false;
	isr3 = false;

	if( r1 >= 0 && r1 < ROWS && c1 >= 0 && c1 < COLS )	isr1 = true;
	if( r2 >= 0 && r2 < ROWS && c2 >= 0 && c2 < COLS )  isr2 = true;
	if( r3 >= 0 && r3 < ROWS && c3 >= 0 && c3 < COLS )	isr3 = true;

	if( isr1 )	{
		if( isr2 )
			if( map[r1][c1]->getImgIndex() == map[r2][c2]->getImgIndex() )
				return map[r1][c1]->getImgIndex();
		
		if( isr3 )
			if( map[r1][c1]->getImgIndex() == map[r3][c3]->getImgIndex() )
				return map[r1][c1]->getImgIndex();
	}

	if( isr2 && isr3 )
		if( map[r2][c2]->getImgIndex() == map[r3][c3]->getImgIndex() )
			return map[r2][c2]->getImgIndex();

	return -1;
}

void GameScene::gameOver(float dt)
{
	auto scene = Scene::create();
	auto layer = GameOver::create();
	layer -> setScore( getScore() );
	scene -> addChild( layer );

	CCTransitionScene* reScene= CCTransitionFadeUp::create(1.0f, scene);
	CCDirector::sharedDirector()->replaceScene(reScene);
}

void GameScene::addTime( )
{
	Label *labelTime = (Label *)this -> getChildByTag(11);

	auto plus = Sprite::create("sprite_plus3.png");
	plus->setPosition(Vec2( labelTime->getContentSize().width + plus->getContentSize().width*1.3 , GAME_SCREEN_HEIGHT - labelTime->getContentSize().height*0.4 ));
	plus->setScale(1.6);
	this->addChild(plus);

	auto action = ScaleTo::create(0.4f ,0);
	plus -> runAction( action );  

}

void GameScene::onEnter()
{
	Layer::onEnter();
}

void GameScene::onEnterTransitionDidFinish()
{
	Layer::onEnterTransitionDidFinish();  
	if (UserDefault::getInstance()->getBoolForKey(MUSIC_KEY)) {                      
        SimpleAudioEngine::getInstance()->playBackgroundMusic("music_bg.mp3", true);  
    } 
}

void GameScene::onExit()
{
	Layer::onExit();
}

void GameScene::onExitTransitionDidStart()
{
	Layer::onExitTransitionDidStart();
}

void GameScene::cleanup()
{
	Layer::cleanup();
	SimpleAudioEngine::getInstance()->stopBackgroundMusic("music_bg.mp3");
}