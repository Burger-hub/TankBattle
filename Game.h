#pragma once
#include "Bullet.h"

class Game 
{
public:
	Game();
	~Game();
	void setGameLevel(int nGameLevel);
	//���ٻ�����
	void ReduceLives();
	void SetLives(int nLives);
	
	//��Ϸ������ʼ�������ǰ��׼����
	void GameInit();
	//��Ϸ����׼����ʼ��
	void GameRunInit();
	//��Ϸ����������(����ֵΪ��ǰ��Ϸ״̬��0������1����)
	int GameStart();

	//��Ϸ����״̬�� 
	void GameStatusBar();

	//��Ϸ����,�ܹ�ʵ�ֹؿ�ת��
	void GameUI();
	
	//��ʼ����(��ȡ�������룬��ʼ��Ϸ����)
	//�˳������õ�ǰ��Ϸģʽ
	void BeginUI();
	//��Ϸ������ѭ��(����ʼ���棬��ӭ���棬��Ϸ���н���)
	void Run();

	//�ӵ����    
	//�����ӵ�(����Ϊ���ڵ�̹��)
	void CreateBullet(Tank objTank);
	//�ӵ���ײ����(����Ϊ�ӵ�������)
	void BulletCollision(Bullet& objBullet);
	//�ӵ��������(�����Ч�ӵ�)
	void BulletManage();

	//̹�����     
	//̹������(���ݴ���̹�˵Ĳ�������������һֻ��Ҳ������̹�˳�ʼ��)
	void ResetTank(Tank& objTank);
	//�з�̹���ƶ�(�������)
	void MoveNPCTank(int nID);
	//��ȡ�û�����,����ֵΪ�������ҿ���
	int getPlayerInput();

private:
	//��ͼ���������ֻ�����ϰ�����Ϣ
	Map objMap;

	//��ͼ�ϵ��ӵ����飬��Ŀ��ȷ���������ö�̬����
	vector<Bullet> vecBullets;

	//��ҵķ���
	int Score;
	//��Ϸ�ؿ�,ͨ�غ�ˢ��
	int GameLevel;
	//��Ϸҳ��ѡ�񣨿�ʼ���˳���
	int GameMode;
	//������
	int Lives;
	
};