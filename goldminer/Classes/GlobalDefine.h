#ifndef __GLOBALDEFINE_H__
#define __GLOBALDEFINE_H__


#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
#define BG_MUSIC        "sound/background.wav"
#define LEVEL_BG_MUSIC "sound/background.wav"
#else
#define BG_MUSIC        "sound/menu-bg.mp3"
#define LEVEL_BG_MUSIC "sound/level-bg.mp3"
#endif // CC_PLATFOR_WIN32

#define IS_PLAY_BG_MUSIC "isPlayBgMusic"//�Ƿ񲥷ű�������
#define IS_PLAY_EFFECT "isPlayEffect"//�Ƿ񲥷ű�������
#define IS_FIRST_PLAY "isFirstPlay"//�Ƿ��ǵ�һ��������Ϸ
#define CUR_LEVEL "curLevel"//��ǰ��Ϸ�ؿ�
#define CUR_GOLD "curGold"//��ǰ����



#define GOAL_COIN(x) 650 +  135 * (x - 1)*(x - 1) + 410*(x -1)

#endif // __GLOBALDEFINE_H__
