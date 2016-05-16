#ifndef __GLOBALDEFINE_H__
#define __GLOBALDEFINE_H__


#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
#define BG_MUSIC        "sound/background.wav"
#define LEVEL_BG_MUSIC "sound/background.wav"
#else
#define BG_MUSIC        "sound/menu-bg.mp3"
#define LEVEL_BG_MUSIC "sound/level-bg.mp3"
#endif // CC_PLATFOR_WIN32

#define IS_PLAY_BG_MUSIC "isPlayBgMusic"//是否播放背景音乐
#define IS_PLAY_EFFECT "isPlayEffect"//是否播放背景音乐
#define IS_FIRST_PLAY "isFirstPlay"//是否是第一次启动游戏
#define CUR_LEVEL "curLevel"//当前游戏关卡
#define CUR_GOLD "curGold"//当前分数



#define GOAL_COIN(x) 650 +  135 * (x - 1)*(x - 1) + 410*(x -1)

#endif // __GLOBALDEFINE_H__
