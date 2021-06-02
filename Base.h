#pragma once
//基础元素的实现：游戏窗口大小，坦克元素等
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <iostream>
#include <Windows.h>
#include <vector>
#include <time.h>
using namespace std;

#define High 22  // 总画面尺寸
#define Width 18

#define mainHeight 22  // 游戏画面尺寸
#define mainWidth 12

//判断指定的按键是否按下
#define KEY_DOWN(vk_code) ((GetAsyncKeyState(vk_code)&0x8000)?1:0)
//判断指定的按键是否弹起
#define KEY_UP(vk_code) ((GetAsyncKeyState(vk_code)&0x8000)?1:0)

//定义方向的代表值//怎么考虑？？
#define UP			0
#define DOWN		3
#define LEFT		1
#define RIGHT		2
#define FIRE		4

//定义坦克类型
#define PLAYER_TANK		10
#define ENEMY_TANK		11

//定义响应速度
#define LOW_SPEED		600
#define NOMAL_SPEED		400
#define FAST_SPEED		200
#define GOD_SPEED		100

extern const char TankSharp[2][4][3][7];//坦克数组
void SetEle(short x, short y, const char* ele);//输出元素符号

bool SetWindowSize(const char* pszWindowTitle, short nX, short nY); //设置控制台窗口信息

void ShowCursor(bool isShow);//	隐藏光标

void ChangeEnglish();//切换至英文输入法
