#include "Base.h"

//在指定坐标输出元素符号(来源于网络）
void SetEle(short x, short y, const char * ele) {
	//获取句柄
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	//设置坐标位置
	COORD loc;
	loc.X = x * 2;
	loc.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), loc);
	//打印字符串
	printf(ele);
	//画图形
}

//坦克形状
const char TankSharp[2][4][3][7] = { 
	{
		{"  ■  ","■■■","■  ■"},		//上
		{"  ■■","■■  ","  ■■"},		//左
		{"■■  ","  ■■","■■  "},		//右
		{"■  ■","■■■","  ■  "}		//下
	},
	{
		{"  □  ","□□□","□  □"},		//上
		{"  □□","□□  ","  □□"},		//左
		{"□□  ","  □□","□□  "},		//右
		{"□  □","□□□","  □  "}		//下
	}
};//第一分量表示敌我双方；第二分量表示坦克的朝向；第三分量是行数，第四分量储存每一行的字符串


  //设置控制台（来源于网络）
bool SetWindowSize(const char* pszWindowTitle, short nX, short nY)
{
	//设置控制台标题
	SetConsoleTitleA(pszWindowTitle);
	HANDLE hStdIn, hStdOut;
	hStdIn = GetStdHandle(STD_INPUT_HANDLE);
	hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	//获取最大控制台的窗口大小
	COORD pos = GetLargestConsoleWindowSize(hStdOut);
	COORD BufferSize = { pos.X + 1,pos.Y + 1 };
	//设置控制台缓冲区大小
	if (!SetConsoleScreenBufferSize(hStdOut, BufferSize))
	{	//设置失败
		printf("buffer err(%d,%d)%d\n", BufferSize.X, BufferSize.Y, GetLastError());
		return false;
	}
	SMALL_RECT srctWindow = { 0,0,nX,nY };
	if (!SetConsoleWindowInfo(hStdOut, true, &srctWindow))
	{	//设置控制台窗口大小
		printf("size err %d\n", GetLastError());
		return false;
	}
	COORD Buffer = { nX + 1,nY + 1 };
	//设置控制台缓冲区大小
	if (!SetConsoleScreenBufferSize(hStdOut, Buffer))
	{	//设置控制台窗口缓冲区失败
		printf("buffer err(%d,%d) %d\n", BufferSize.X, BufferSize.Y, GetLastError());
		return false;
	}
	return true;
}

//隐藏光标（来源于网络）
void ShowCursor(bool isShow)
{	//光标结构，用于隐藏光标
	CONSOLE_CURSOR_INFO stcCursorInfo;
	//隐藏光标
	stcCursorInfo.bVisible = isShow;
	stcCursorInfo.dwSize = sizeof(stcCursorInfo);
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &stcCursorInfo);
}

//改变输入法（来源于网络）
void ChangeEnglish()
{
	keybd_event(VK_SHIFT, 0, 0, 0);
	Sleep(100);
	keybd_event(VK_SHIFT, 0, KEYEVENTF_KEYUP, 0);
}