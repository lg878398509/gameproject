#ifndef __GLOBALDEFINE_H__
#define __GLOBALDEFINE_H__


#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
#define BG_MUSIC        "sound/background.wav"
#define LEVEL_BG_MUSIC "sound/background.wav"
#define PUSH_CLAW_MUSIC "sound/dig.wav"        //����������
#define PULL_CLAW_MUSIC "sound/pull.mp3"       //����������
#define CONTACT_STONE_MUSIC "sound/low-value.mp3"//������ײ��ʯͷ������
#define CONTACT_GOLD_BIG_MUSIC "sound/high-value.mp3"//������ײ�����������
#define CONTACT_GOLD_NORMAL_MUSIC "sound/normal-value.mp3"//������ײ������������
#define GET_GOLD_MUSIC "sound/score1.mp3"//���������үү������
#define ADD_SCORE_MUSIC "sound/score2.mp3"//�ӽ�ҵ�����
#else
#define BG_MUSIC        "sound/menu-bg.mp3"    //�˵���������
#define LEVEL_BG_MUSIC "sound/level-bg.mp3"    //�ؿ���������
#define PUSH_CLAW_MUSIC "sound/dig.mp3"        //����������
#define PULL_CLAW_MUSIC "sound/pull.mp3"       //����������
#define CONTACT_STONE_MUSIC "sound/low-value.mp3"//������ײ��ʯͷ������
#define CONTACT_GOLD_BIG_MUSIC "sound/high-value.mp3"//������ײ�����������
#define CONTACT_GOLD_NORMAL_MUSIC "sound/normal-value.mp3"//������ײ������������
#define CONTACT_GOLD_NORMAL_MUSIC "sound/normal-value.mp3"//������ײ������������
#define GET_GOLD_MUSIC "sound/score1.mp3"//���������үү������
#define ADD_SCORE_MUSIC "sound/score2.mp3"//�ӽ�ҵ�����
#endif // CC_PLATFOR_WIN32

#define IS_PLAY_BG_MUSIC "isPlayBgMusic"//�Ƿ񲥷ű�������
#define IS_PLAY_EFFECT "isPlayEffect"//�Ƿ񲥷ű�������
#define IS_FIRST_PLAY "isFirstPlay"//�Ƿ��ǵ�һ��������Ϸ
#define CUR_LEVEL "curLevel"//��ǰ��Ϸ�ؿ�
#define CUR_GOLD "curGold"//��ǰ����



#define GOAL_COIN(x) 650 +  135 * (x - 1)*(x - 1) + 410*(x -1)

#endif // __GLOBALDEFINE_H__
