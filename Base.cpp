#include "Base.h"

//��ָ���������Ԫ�ط���(��Դ�����磩
void SetEle(short x, short y, const char * ele) {
	//��ȡ���
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	//��������λ��
	COORD loc;
	loc.X = x * 2;
	loc.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), loc);
	//��ӡ�ַ���
	printf(ele);
	//��ͼ��
}

//̹����״
const char TankSharp[2][4][3][7] = { 
	{
		{"  ��  ","������","��  ��"},		//��
		{"  ����","����  ","  ����"},		//��
		{"����  ","  ����","����  "},		//��
		{"��  ��","������","  ��  "}		//��
	},
	{
		{"  ��  ","������","��  ��"},		//��
		{"  ����","����  ","  ����"},		//��
		{"����  ","  ����","����  "},		//��
		{"��  ��","������","  ��  "}		//��
	}
};//��һ������ʾ����˫�����ڶ�������ʾ̹�˵ĳ��򣻵������������������ķ�������ÿһ�е��ַ���


  //���ÿ���̨����Դ�����磩
bool SetWindowSize(const char* pszWindowTitle, short nX, short nY)
{
	//���ÿ���̨����
	SetConsoleTitleA(pszWindowTitle);
	HANDLE hStdIn, hStdOut;
	hStdIn = GetStdHandle(STD_INPUT_HANDLE);
	hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	//��ȡ������̨�Ĵ��ڴ�С
	COORD pos = GetLargestConsoleWindowSize(hStdOut);
	COORD BufferSize = { pos.X + 1,pos.Y + 1 };
	//���ÿ���̨��������С
	if (!SetConsoleScreenBufferSize(hStdOut, BufferSize))
	{	//����ʧ��
		printf("buffer err(%d,%d)%d\n", BufferSize.X, BufferSize.Y, GetLastError());
		return false;
	}
	SMALL_RECT srctWindow = { 0,0,nX,nY };
	if (!SetConsoleWindowInfo(hStdOut, true, &srctWindow))
	{	//���ÿ���̨���ڴ�С
		printf("size err %d\n", GetLastError());
		return false;
	}
	COORD Buffer = { nX + 1,nY + 1 };
	//���ÿ���̨��������С
	if (!SetConsoleScreenBufferSize(hStdOut, Buffer))
	{	//���ÿ���̨���ڻ�����ʧ��
		printf("buffer err(%d,%d) %d\n", BufferSize.X, BufferSize.Y, GetLastError());
		return false;
	}
	return true;
}

//���ع�꣨��Դ�����磩
void ShowCursor(bool isShow)
{	//���ṹ���������ع��
	CONSOLE_CURSOR_INFO stcCursorInfo;
	//���ع��
	stcCursorInfo.bVisible = isShow;
	stcCursorInfo.dwSize = sizeof(stcCursorInfo);
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &stcCursorInfo);
}

//�ı����뷨����Դ�����磩
void ChangeEnglish()
{
	keybd_event(VK_SHIFT, 0, 0, 0);
	Sleep(100);
	keybd_event(VK_SHIFT, 0, KEYEVENTF_KEYUP, 0);
}