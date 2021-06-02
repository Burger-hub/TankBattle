#include "Game.h"

Game::Game(){}
Game::~Game(){}

void Game::setGameLevel(int nGameLevel) {
	GameLevel = nGameLevel;
};

void Game::ReduceLives() {
	Lives--;
}
void Game::SetLives(int nLives) {
	Lives = nLives;
}

//��Ϸ������ʼ�������ǰ��׼����//�Ѳ���
void Game::GameInit()
{	//���ع��
	ShowCursor(false);
	//�л����뷨        
	ChangeEnglish();
	//���ÿ���̨����ʹ�С
	SetWindowSize("TankBattle", 40, 30);	
}

//��Ϸ���г�ʼ����̹�˵ĳ�ʼ�������Ѳ��ԣ�λ�ô�������
void Game::GameRunInit()
{
	//��ʼ��
	objMap.clearMap();
	
	//��ʼ�����̹��
	Tank TempTank0({ 5,10 }, UP, PLAYER_TANK, FAST_SPEED, clock(), 0);//����time.h��
	Tank::arrTank[0] = TempTank0;
	Tank::arrTank[0].SetID(0);
	Tank::arrTank[0].DrawTank();//�������̹��
	
	//��ʼ���з�̹�ˣ�����,���,λ�ã�
	for (int i = 1; i < 5; i++) {
		Tank TempTanki({ 3,6 }, UP, ENEMY_TANK, LOW_SPEED, clock(), 0);//���ѡ�˸�λ�ù���̹��
		Tank::arrTank[i] = TempTanki;
		Tank::arrTank[i].SetID(i);
		ResetTank(Tank::arrTank[i]);
	}
	//��ʼ������
	Score = 0;	
}

//��Ϸ����������(����ֵΪ��ǰ��Ϸ״̬��0������1����)
int Game::GameStart()
{
	int nKill = GameLevel * 10;//Ŀ��ɱ����
	int nState = -1;//���ڴ����Ϸ״̬ ��-1��ʾ������1��ʾ������0��ʾ�˳���
	int nOper = -1;//��ȡ��Ұ�������  (-1��ʾ������)
	GameRunInit();
	while (nState == -1)//��Ϊ-1��һֱѭ��
	{
		if (Lives == 0) {
			GameLevel = 7;
			nState = 0;//����������꣬���˳�ѭ�����˳���־Ϊ0
		}
		//��������ˣ��ؿ����������˳���Ϸѭ�����˳���־Ϊ1
		if (Tank::arrTank[0].GetKillNumber() >= nKill)
		{
			GameLevel++;
			nState = 1;
		}

		//��ʾ��Ϸ״̬��
		GameStatusBar();

		//��ȡ��������
		nOper = getPlayerInput();
		if (nOper != -1)	//���̹�˳��Բ�����ֵΪ-1��ʾ�����루��-1����Ϊ����ֵ��ռ�ˣ�
		{
			//�ж��Ƿ񵽴���Ӧʱ�䣨����̹���ٶȣ������ƶ��ٶȺͷ����ٶȣ�
			if (clock() - Tank::arrTank[0].GetClock() > Tank::arrTank[0].GetSpeed())
			{
				if (nOper != FIRE)	//�ƶ�
				{
					Tank::arrTank[0].MoveTank(nOper);
				}
				else	//����
				{
					CreateBullet(Tank::arrTank[0]);
				}
				//ֻҪ��Ҳ���������״̬����Ϊ�� ��Ϊ�ع��ʼ���������һֱ�ƶ�
				nOper = -1;
				//����̹��ʱ�䣬��Ӧʱ��Ϊ����ǰʱ��-�ϴ����õ�ʱ�䣩�����ϴβ��������ڵ�ʱ��
				Tank::arrTank[0].SetClock(clock());
			}
		}
		
		//�����з�̹�����飬���������Ӧʱ�䣬�����
		for (int i = 1; i < 5; i++)
		{
			if (clock() - Tank::arrTank[i].GetClock() > Tank::arrTank[i].GetSpeed())
			{
				//�����±����̹�˲���
				MoveNPCTank(i);//�ƶ�����
				Tank::arrTank[i].SetClock(clock());//����ʱ��
			}

		}
		//�����ӵ����飬���Ƿ񵽴���Ӧʱ��
		for (unsigned int i = 0; i < vecBullets.size(); i++)//size��ʾ����Ĵ�С
		{
			if (clock() - vecBullets[i].GetClock() > vecBullets[i].GetSpeed())
			{
				//�ӵ��ƶ�
				vecBullets[i].MoveBullet();
				//�ӵ�����ײ����
				BulletCollision(vecBullets[i]);
				//����ʱ��
				vecBullets[i].SetClock(clock());
			}
		}
		//�����ӵ������������������Ч�ӵ�
		BulletManage();
	}
	return GameLevel;//����ֵΪ0��ʾ������1��ʾ����
}

//״̬��
void Game::GameStatusBar()//�Ѳ��ԣ���ԭ����
{
	char Buffer[20];//Ԥ�ȷ��仺����
	
	SetEle(12, 2, "��ǰ�ؿ�:");//%d��int���ͱ����ĸ�ʽ���������,\n��ʾ����
	sprintf_s(Buffer, "% d\n", GameLevel);//����<stdio.h>��
	SetEle(18, 2, Buffer);//����������������С����ʽ�ַ���
	
	SetEle(12, 3, "ʣ�������:");
	sprintf_s(Buffer, "% d\n", Lives);
	SetEle(18, 3, Buffer);
	
	SetEle(12, 5, "Ŀ��ɱ����:");
	sprintf_s(Buffer, "% d\n", GameLevel*10);
	SetEle(18, 5, Buffer);
	
	SetEle(12, 4, "��ǰɱ����:");
	sprintf_s(Buffer, "% d\n", Tank::arrTank[0].GetKillNumber());
	SetEle(18, 4, Buffer);
}

//��Ϸ����,�ܹ�ʵ�ֹؿ�ת��
void Game::GameUI()           //���������
{
	//��������ʼ��������Ϸ�����б�������ͼ��̹��λ��
	objMap.clearMap();
	//��ȡ��ǰ��Ϸ״̬
	setGameLevel(1);
	
	//��ȡ��ǰ�Ĺؿ�
	while (GameLevel<=5)
	{
		//����̹�˵�ͼ
		Tank::TransformMap(objMap);
		objMap.drawMap(); 
		char Buffer[5][10] = {"��1��","��2��","��3��","��4��","��5��"};
		SetEle(4, 10, Buffer[GameLevel-1]);//��ʾ��ǰ�ؿ���
		Sleep(2000);
		objMap.clearMap();
		
		//������Ϸ������ѭ��������ֵΪѭ�����
		GameLevel = GameStart();
		//һ�ؽ���������ӵ�����
		vecBullets.clear();	
	}
	
	//��Ϸ��������
	if (GameLevel==6)//���ݷ���ֵ�Ĳ�ͬ��ʾ��ͬ����
	{
		//ͨ��
		objMap.clearMap();
		SetEle(2, 10, "��ϲ��ͨ����!!");
	}
	else
	{
		//ʧ��
		objMap.clearMap();
		SetEle(2, 10, "����ʧ��!!");
	}
	system("pause");//ֹͣ�ڵ�ǰ����
}

//��ʼ����(��ȡ�������룬������Ϸģʽѡ��)
void Game::BeginUI()       //�Ѽ��
{
	
	//���ڴ洢ѡ�������ַ���
	char Buffer[2][20] = { "1.��ʼ��Ϸ","2.�˳���Ϸ" };
	//���ڱ����û���ѡ��
	int nIndex = 1;
	//���ڱ���ѡ���������
	int nKeyTemp = 1;
	//�ж��Ƿ��а�������
	int nFlag = 1;

	
	//�����û�ѡ�����ѡ�������
	//ѭ����ⰴ�����ı�ѡ��
	//J��ȷ��
	while (true)
	{
		//����а������£����ݵ�ǰ������������2��ѡ��
		if (nFlag)                     
		{
			nFlag = 0;
			for (int i = 0; i < 2; i++)
			{
				if (i + 1 == nKeyTemp)//ÿ�ΰ��������»�����ͨ����ɫ��ʾ��ǰͣ��ѡ���δʵ�֣�
					SetEle(3, 10 + i, Buffer[i]);
				else
					SetEle(3, 10 + i, Buffer[i]);
			}
		}
		//��ȡ�û����� ��Դ�����磩
		if (_kbhit()) {
			char ch = _getch();
			if (ch == 'j' || ch == 'J')
				break;
			else if (ch == 'w' || ch == 'W')
			{
				nKeyTemp--;
				nFlag = 1;
			}
			else if (ch == 's' || ch == 'S')
			{
				nKeyTemp++;
				nFlag = 1;
			}
		}
		if (nKeyTemp < 1)
			nKeyTemp += 2;
		else if (nKeyTemp > 2)
			nKeyTemp -= 2;
	}
	GameMode = nKeyTemp;
}

//��Ϸ������ѭ��(����ʼ���棬��ӭ���棬��Ϸ���н���)
void Game::Run()
{
	GameLevel = 1;//��Ϸ��ʼ�ؿ�Ϊ1
	SetLives(3);//��ʼ������Ϊ3
	//��ʼ�����棨�����߽磩
	objMap.initMap();
	//��ʱ2s
	Sleep(2000);
	BeginUI();//ѡ�����
	if (GameMode == 1)
	{
		GameUI();
	}
}

void Game::CreateBullet(Tank objTank)
{
	//1.����̹�˳�ʼ���ӵ�����
	Bullet TempBullet;
	TempBullet = objTank;
	//2.��ײ��⣬�����Խ�磬������ӵ�����,�����ӵ�,������ִ�н���
	COORD pos = TempBullet.GetPos();//̹�����ĵ�����
	if (pos.X > 0 && pos.X < mainWidth-1 && pos.Y > 0 && pos.Y < mainHeight-1)  //�����߿���һȦ
	{
		vecBullets.push_back(TempBullet);    //��vectorβ������һ������
		TempBullet.DrawBullet();
	}
}

//�ӵ���ײ���
void Game::BulletCollision(Bullet& objBullet)
{
	//���ݴ����ӵ���λ��λ���жϵ�ǰ�ӵ���״̬��ײ�����ⶫ������ǰ�ӵ����״̬��Ϊ��
	//ײ���ϰ���ײ��̹�ˣ�ײ�������ӵ�������ʲô��ûײ��
	//1.�ж��Ƿ�ײ���ϰ����̹��
	COORD pos = objBullet.GetPos();
	int nType = objMap.getMapType(pos);
	switch (nType)
	{
		case 1://ײ���߽�
		{
			//ɾ���ӵ�,����ǽ
			objBullet.SetIsAlive(false);
			objMap.drawImage(pos, 1);
			return;
			break;
		}
		case 0://���ǿյأ�����̹�˺��ӵ�
		{	//2.����̹�����飬���Ƿ�ײ��̹��
				for (int i = 0; i < 6; i++)
				{
				if (Tank::arrTank[i].TankBodyExist(pos))	//��̹������
				{
					objBullet.SetIsAlive(false);//������ӵ������ж��Ƿ��������ɱ
					if(!(objBullet == Tank::arrTank[i])){//����ͬһ��Ӫ/���غ���
						ResetTank(Tank::arrTank[i]);//����̹��
						if(i!=0){//���ез�̹��
							Tank::arrTank[0].AddKillNumber();//������ҵ�ɱ����
						}
						else {//�з��������̹��
							ReduceLives();
						}
					}	
				}
			}
			//3.�����ӵ����飬���Ƿ�ײ���ӵ�
			for (unsigned int i = 0; i < vecBullets.size(); i++)
			{
				//���Լ��ų�
				if (&objBullet == &vecBullets[i])
					continue;
				//�����ײ
				if (objBullet.BulletCrash(vecBullets[i]))
				{
					objBullet.SetIsAlive(false);
					objBullet.ClearBullet();
					vecBullets[i].SetIsAlive(false);
				}
			}
			break;
		}
	}
}
	
	
void Game::BulletManage()//���ö�̬���������еĺ���
	{
		Bullet TempObj;
		for (auto item = vecBullets.cbegin(); item != vecBullets.cend();)//��������
		{
			TempObj = *item;
			if (!TempObj.GetIsAlive())	//�����ǰ�ӵ��Ѿ�����
			{
				item = vecBullets.erase(item);//����
			}
			else
			{
				++item;
			}
		}
	}
	
// ̹������(���ݴ���̹�˵Ĳ�������������һֻ��Ҳ������̹�˳�ʼ��)
void Game::ResetTank(Tank& objTank)
{
		//�Ȳ����Լ�
		objTank.ClearTank();
		//���Ϊ���̹�ˣ���˵�������ˣ�����̹��λ��
		if (objTank.GetType() == PLAYER_TANK)
		{
			objTank.SetPos({ 5,10 });
		}
		else
		{
			int nSpeed = LOW_SPEED;
			int n = 0;//�����Ƿ����óɹ�
			//��̹�����ĸ����������
			while (n == 0) {//��n=1,��˵��̹���ѷ���
				int posType = rand() % 4;
				switch (posType) {
				case 0:
					if (objTank.TankCollision({3 , 3 }))	//�����һ����û���ϰ���
					{
						Tank TempTank({ 3,3 }, DOWN, ENEMY_TANK, nSpeed, clock(), 0);
						TempTank.SetID(objTank.GetID());
						objTank = TempTank;
						n = 1;
					};
					break;
				case 1:
					if (objTank.TankCollision({ 9,3 }))//����ڶ�����û���ϰ���
					{
						Tank TempTank({ 9,3 }, DOWN, ENEMY_TANK, nSpeed, clock(), 0);
						TempTank.SetID(objTank.GetID());
						objTank = TempTank;
						n = 1;
					};
					break;
				case 2:
					if (objTank.TankCollision({ 3, 19 }))//�����������û���ϰ���
					{
						Tank TempTank({ 3, 19 }, UP, ENEMY_TANK, nSpeed, clock(), 0);
						TempTank.SetID(objTank.GetID());
						objTank = TempTank;
						n = 1;
					}
					break;
				case 3:
					if (objTank.TankCollision({ 9, 19 }))//������ĸ���û���ϰ���
					{
						Tank TempTank({ 9, 19 }, UP, ENEMY_TANK, nSpeed, clock(), 0);
						TempTank.SetID(objTank.GetID());
						objTank = TempTank;
						n = 1;
					}
					break;
				default:break;
				}
			}
		}
		//����̹��
		objTank.DrawTank();
}

void Game::MoveNPCTank(int nID)
{
	//�������ǰ���ƶ����ǿ��ڣ��ƶ����ʵô��ڿ���
	bool nFire = (rand() % 10 < 2 ? true : false);
	//���������
	int nDir = rand() % 4;
	if (nFire)
	{
		CreateBullet(Tank::arrTank[nID]);
	}
	else
	{
		Tank::arrTank[nID].MoveTank(nDir);
	}	
}

int Game::getPlayerInput()//base.h
{
	if (KEY_DOWN('W') || KEY_DOWN('w'))
		return UP;
	if (KEY_DOWN('S') || KEY_DOWN('s'))
		return DOWN;
	if (KEY_DOWN('A') || KEY_DOWN('a'))
		return LEFT;
	if (KEY_DOWN('D') || KEY_DOWN('d'))
		return RIGHT;
	if (KEY_DOWN('J') || KEY_DOWN('j'))
		return FIRE;
	return -1;
}