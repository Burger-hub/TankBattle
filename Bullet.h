#pragma once
#include "base.h"
#include "Tank.h"

class Bullet
{
public:
	Bullet();//Ĭ�Ϲ��캯��
	Bullet(COORD npos, int nDir, int nSpeed, int nClock) :pos(npos), Dir(nDir),
		Speed(nSpeed), Clock(nClock) {}//���캯��
	~Bullet();

	//�ӵ�����ƶ�
	void MoveBullet();
	//���ӵ�
	void DrawBullet();
	//�����ӵ�
	void ClearBullet();
	//�жϸ��ӵ��Ƿ����ײ
	bool BulletCrash(Bullet objBullet);


	//��ȡ�ӵ��ϴ��ƶ���ʱ�䣨���ڿ����ӵ����ٶȣ�
	int GetClock();
	//�����ӵ��ϴ��ƶ���ʱ��
	void SetClock(int nClock);
	//��ȡ�ӵ�������
	COORD GetPos();
	//��ȡ�ӵ����״̬
	bool GetIsAlive();
	//�����ӵ����״̬
	void SetIsAlive(bool bState);
	//��ȡ�ӵ��ٶ�
	int GetSpeed();
	//��ȡ�ӵ�����
	int GetDir();
	
	//���صȺ�������������ӵ����̹����������ж�
	bool operator==(Tank objTank);
	//���ظ�ֵ�����������̹���ഴ���ӵ�
	void operator=(Tank objTank);

private:
	//�ӵ���λ��
	COORD pos;
	//�ӵ��ķ���
	int Dir;
	//�ӵ��ϴ��ƶ���ʱ��
	int Clock;
	//�ӵ����ƶ��ٶ�
	int Speed;
	//�ӵ��Ĵ��״̬
	bool Alive;
	// �ӵ�����Ӫ
	int Camp;
};