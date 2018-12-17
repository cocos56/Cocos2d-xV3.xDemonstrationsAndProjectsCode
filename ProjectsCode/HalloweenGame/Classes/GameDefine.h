#ifndef  _Inkmoo_xiaochu_h_
#define  _Inkmoo_xiaochu_h_

// 定义屏幕宽高
#define GAME_SCREEN_WIDTH 480
#define GAME_SCREEN_HEIGHT 800

// 定义每个精灵大小
#define SPRITE_WIDTH 48
#define BOADER_WIDTH 2

#define ROWS 8
#define COLS 8

// 精灵种类个数
#define TOTAL_SP 6

// 音乐音效
#include "SimpleAudioEngine.h"
#define SOUND_KEY "sound_key"
#define MUSIC_KEY "music_key"

// 分数存储
#define userDefault CCUserDefault::sharedUserDefault()

// 精灵的显示模式，Hor 横向消除一行，Ver纵向消除一列
enum DisplayMode{
    DISPLAY_MODE_NORMAL = 0,
    DISPLAY_MODE_HORIZONTAL,
    DISPLAY_MODE_VERTICAL,
};


// 获取精灵 普通
static const char *sprNormal[TOTAL_SP] = {
	"icon1.png",
	"icon2.png",
	"icon3.png",
	"icon4.png",
	"icon5.png",
    "icon6.png"
};

// 垂直
static const char *sprVertical[TOTAL_SP] = {
	"icon1_z.png",
	"icon2_z.png",
	"icon3_z.png",
	"icon4_z.png",
	"icon5_z.png",
    "icon6_z.png"
};

// 水平
static const char *sprHorizontal[TOTAL_SP] = {
	"icon1_h.png",
	"icon2_h.png",
	"icon3_h.png",
	"icon4_h.png",
	"icon5_h.png",
    "icon6_h.png"
};






#endif