#include "Tank.h"


extern const char TankSharp[2][4][3][7];
Map Tank::objTankMap;//Tank�������ȫ�ֵ�ͼ
Tank Tank::arrTank[5];//��������

Tank::Tank() {}
Tank::~Tank() {}

void Tank::TransformMap(Map objGameMap)//ԭʼ��ͼת��Ϊ̹�˵�ͼ�����໭һȦ�����������ȫ�ֵ�ͼ��
{
	objTankMap.initMap();
	//������ͼ����������߽磬��һȦ�ϰ���(�����ı����ͣ�
	for (short i = 0; i < mainWidth; i++)
	{
		for (short j = 0; j < mainHeight; j++)
		{
			int nType = objGameMap.getMapType({ i,j });
			if (nType == 1)//1��ʾ���ϰ�
				IncreaseRange({ i,j });
		}
	}
}

void Tank::IncreaseRange(COORD pos)//����������Χ��λ�ö�����Ϊ�ϰ������������������������ڣ�
{
	for (short nX = pos.X - 1; nX <= pos.X + 1; nX++)
		for (short nY = pos.Y - 1; nY <= pos.Y + 1; nY++)//����������Ϊ���ĵľŹ���
		{
			if (nX >= 0 && nX < mainWidth && nY >= 0 && nY < mainHeight)	//���ڵ�ͼ��Χ��ʱ������
				objTankMap.setMapType({ nX,nY }, 1);
		}
}

void Tank::DrawTank()//��̹���ڵ�ͼ�л���
{	
	for (short nY = pos.Y - 1, i = 0; nY < pos.Y + 2; nY++, i++)
	{
		SetEle(pos.X - 1, nY, TankSharp[Type % 10][Dir][i]);//����������
	}
}

void Tank::ClearTank()//��̹�˴���Ļ��ɾ��
{
	//�������ĵ㣬�ƶϳ���㣬ֱ�����ո�     	
	for (short nY = pos.Y - 1; nY < pos.Y + 2; nY++)
	{
		SetEle(pos.X - 1, nY, "      ");
	}
}

void Tank::MoveTank(int nDir)//�ƶ�̹��
{
	//ֻҪ�����ƶ�����Ȼ�ػ�̹��
	ClearTank();
	//1.������ƶ�������ĵ�
	COORD TempPos = pos;
	if (nDir + Dir == 3)//����base.h�еĶ���
	{
		//���������겻��,ֻ�ı䷽�򣬲���Ҫ��ײ���
		Dir = nDir;
		DrawTank();
		return;
	}
	else {
		//���Ƿ�������ݷ���ı�����
		switch (nDir)
		{
		case UP:
			TempPos.Y--;
			break;
		case DOWN:
			TempPos.Y++;
			break;
		case LEFT:
			TempPos.X--;
			break;
		case RIGHT:
			TempPos.X++;
			break;
		}
		//2.���ƶ���ĵ������ײ���
		if (TankCollision(TempPos))
		{
			//��������ƶ�����������꣬������
			pos = TempPos;
			Dir = nDir;
			DrawTank();
		}
		else //����������ƶ������ƶ�,ֻ�ı�̹�˵ķ���
		{
			Dir = nDir;
			DrawTank();
		}
	}
}

bool Tank::TankCollision(COORD pos)//��ײ���,ture��ʾ�����ƶ�
{
	//����̹�����飬�ж��Ƿ��ײ�����Լ������̹��
	for (int i = 0; i < 6; i++)
	{
		//�ų�����
		if (this == &arrTank[i])
			continue;    //��������ѭ��        
		else
		{	//���򣬲����Ըõ�Ϊ���ĵ����е��ǲ��ǻ�ײ��
			for (short nX = pos.X - 1; nX < pos.X + 2; nX++)
				for (short nY = pos.Y - 1; nY < pos.Y + 2; nY++)
				{
					//����̹�˱�Ե���Ƿ��ڱ��̹����
					if (arrTank[i].TankBodyExist({ nX,nY }))
						return false;      //����ڱ��̹���ϣ��򲻿����ƶ�  
				}

		}
	}
	//û��ײ��̹�ˣ��ж��Ƿ񵽱߽�
	if (pos.X >= 0 && pos.X < mainWidth && pos.Y >= 0 && pos.Y < mainHeight &&
		Tank::objTankMap.getMapType(pos) == 0)//��һ���жϱ�֤̹�˲��ᱻ�ϰ�������
	{
		return true;//û�б�ײ���������ƶ�
	}
	return false;//�����˱߽�
}

bool Tank::TankBodyExist(COORD npos)//�������Ƿ���̹������
{
	for (short nX = pos.X - 1; nX < pos.X + 2; nX++)
		for (short nY = pos.Y - 1; nY < pos.Y + 2; nY++)//����̹�����ľŹ���
		{
			if (npos.X == nX && npos.Y == nY)
				return true;//����������̹������
		}
	return false;//�������겻��̹������
}

int Tank::GetClock()
{
	return Clock;
}

void Tank::SetClock(int nClock)
{
	Clock = nClock;
}

int Tank::GetType()
{
	return Type;
}

void Tank::SetType(int nType)
{
	Type = nType;
}

int Tank::GetSpeed()
{
	return Speed;
}

int Tank::GetTankDir()
{
	return Dir;
}

COORD Tank::GetPos()
{
	return pos;
}

void Tank::SetPos(COORD npos)
{
	pos = npos;
}

int Tank::GetID()
{
	return ID;
}

void Tank::SetID(int nID)
{
	ID = nID;
}

void Tank::AddKillNumber()
{
	Kill++;
}

int Tank::GetKillNumber()
{
	return Kill;
}


