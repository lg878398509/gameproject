#ifndef __GLOBALDEFINE_H__
#define __GLOBALDEFINE_H__


#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
#define BG_MUSIC        "sound/background.wav"
#define LEVEL_BG_MUSIC "sound/background.wav"
#define PUSH_CLAW_MUSIC "sound/dig.wav"        //扔绳子声音
#define PULL_CLAW_MUSIC "sound/pull.mp3"       //拉绳子声音
#define CONTACT_STONE_MUSIC "sound/low-value.mp3"//钩子碰撞到石头的声音
#define CONTACT_GOLD_BIG_MUSIC "sound/high-value.mp3"//钩子碰撞到大金块的声音
#define CONTACT_GOLD_NORMAL_MUSIC "sound/normal-value.mp3"//钩子碰撞到正常的声音
#define GET_GOLD_MUSIC "sound/score1.mp3"//金块拉到老爷爷的声音
#define ADD_SCORE_MUSIC "sound/score2.mp3"//加金币的声音
#else
#define BG_MUSIC        "sound/menu-bg.mp3"    //菜单背景音乐
#define LEVEL_BG_MUSIC "sound/level-bg.mp3"    //关卡背景音乐
#define PUSH_CLAW_MUSIC "sound/dig.mp3"        //扔绳子声音
#define PULL_CLAW_MUSIC "sound/pull.mp3"       //拉绳子声音
#define CONTACT_STONE_MUSIC "sound/low-value.mp3"//钩子碰撞到石头的声音
#define CONTACT_GOLD_BIG_MUSIC "sound/high-value.mp3"//钩子碰撞到大金块的声音
#define CONTACT_GOLD_NORMAL_MUSIC "sound/normal-value.mp3"//钩子碰撞到正常的声音
#define CONTACT_GOLD_NORMAL_MUSIC "sound/normal-value.mp3"//钩子碰撞到正常的声音
#define GET_GOLD_MUSIC "sound/score1.mp3"//金块拉到老爷爷的声音
#define ADD_SCORE_MUSIC "sound/score2.mp3"//加金币的声音
#endif // CC_PLATFOR_WIN32

#define IS_PLAY_BG_MUSIC "isPlayBgMusic"//是否播放背景音乐
#define IS_PLAY_EFFECT "isPlayEffect"//是否播放背景音乐
#define IS_FIRST_PLAY "isFirstPlay"//是否是第一次启动游戏
#define CUR_LEVEL "curLevel"//当前游戏关卡
#define CUR_GOLD "curGold"//当前分数



#define GOAL_COIN(x) 650 +  135 * (x - 1)*(x - 1) + 410*(x -1)

#endif // __GLOBALDEFINE_H__
