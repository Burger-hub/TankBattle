#pragma once
#include "Map.h"

class Tank 
{
public:
	Tank();//Ĭ�Ϲ��캯��

	Tank(COORD npos, int nDir, int nType, int nSpeed, int nClock, int nKill) :
		pos(npos), Dir(nDir), Type(nType),
		Speed(nSpeed), Clock(nClock), Kill(nKill) {}
		//���캯��
	~Tank();//��������

	//ȫ�ֵ�һ����ͼ 
	static Map objTankMap;
	//ȫ�ֵ�һ��̹�����飬��������̹�ˣ���һ���±������
	static Tank arrTank[5];

	//��ͼ��غ��� 
	//��̬��������������Ϸ�����潫��Ϸ��ͼת��Ϊ̹�˵�ͼ
	static void TransformMap(Map objGameMap);
	//��̬������������̹�˵�ͼ��ĳһ�㻭��һȦ�ϰ�����ֹ̹����ײ
	static void IncreaseRange(COORD pos); 

	//̹����غ���
	//��̹��
	void DrawTank();
	//����̹��
	void ClearTank();
	//̹���ƶ�
	void MoveTank(int nDir);
	//̹����ײ���
	bool TankCollision(COORD pos);
	//�жϸ������Ƿ���̹������
	bool TankBodyExist(COORD pos);
	

	//̹��������غ���
	//��ȡ̹�����һ����Ӧʱ��
	int GetClock();
	//����̹�����һ����Ӧʱ��
	void SetClock(int nClock);
	//��ȡ̹�����ͣ��з���������
	int GetType();
	//����̹�����ͣ�����̹�˳�ʼ��
	void SetType(int nType);
	//��ȡ̹���ٶ�
	int GetSpeed();
	//��ȡ̹�˷���
	int GetTankDir();
	//��ȡ̹������
	COORD GetPos();
	//����̹������
	void SetPos(COORD pos);
	//��ȡ̹��ID
	int GetID();
	//����̹��ID
	void SetID(int nID);

	//��¼�ĺ���
	//̹��ɱ��������
	void AddKillNumber();
	//��ȡ̹��ɱ����
	int GetKillNumber();
	
private:
	//̹������
	COORD pos;
	//̹�˵ķ���
	int Dir;
	//̹�˵�����(���̹��PLAYER_TANK������̹��ENEMY_TANK)
	int Type;
	//̹�˵����һ����Ӧʱ��
	int Clock;
	//̹�˵��ƶ��ٶ�
	int Speed;
	//̹�˵�ID
	int ID;
	//̹�˵�ɱ����
	int Kill;
	
};