#pragma once
//����Ԫ�ص�ʵ�֣���Ϸ���ڴ�С��̹��Ԫ�ص�
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <iostream>
#include <Windows.h>
#include <vector>
#include <time.h>
using namespace std;

#define High 22  // �ܻ���ߴ�
#define Width 18

#define mainHeight 22  // ��Ϸ����ߴ�
#define mainWidth 12

//�ж�ָ���İ����Ƿ���
#define KEY_DOWN(vk_code) ((GetAsyncKeyState(vk_code)&0x8000)?1:0)
//�ж�ָ���İ����Ƿ���
#define KEY_UP(vk_code) ((GetAsyncKeyState(vk_code)&0x8000)?1:0)

//���巽��Ĵ���ֵ//��ô���ǣ���
#define UP			0
#define DOWN		3
#define LEFT		1
#define RIGHT		2
#define FIRE		4

//����̹������
#define PLAYER_TANK		10
#define ENEMY_TANK		11

//������Ӧ�ٶ�
#define LOW_SPEED		600
#define NOMAL_SPEED		400
#define FAST_SPEED		200
#define GOD_SPEED		100

extern const char TankSharp[2][4][3][7];//̹������
void SetEle(short x, short y, const char* ele);//���Ԫ�ط���

bool SetWindowSize(const char* pszWindowTitle, short nX, short nY); //���ÿ���̨������Ϣ

void ShowCursor(bool isShow);//	���ع��

void ChangeEnglish();//�л���Ӣ�����뷨
