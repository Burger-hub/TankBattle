#include "Bullet.h"

Bullet::Bullet(){}
Bullet::~Bullet(){}

void Bullet::MoveBullet()//�ƶ��ӵ�
{
	ClearBullet();
	//����Ҫ��ײ�жϣ�����Ҫд���ͼ��ֻ��Ҫ���ݷ���ı����꣬����������
	switch (Dir)
	{
	case UP:
		pos.Y--;//ע��ԭ��λ�������Ϸ�
		break;
	case DOWN:
		pos.Y++;
		break;
	case LEFT:
		pos.X--;
		break;
	case RIGHT:
		pos.X++;
		break;
	default:
		break;
	}
	DrawBullet();
}

void Bullet::DrawBullet()//�����ӵ�
{
	SetEle(pos.X, pos.Y, "��");
}

void Bullet::ClearBullet()//����ӵ�
{
	SetEle(pos.X, pos.Y, "  ");
}

bool Bullet::BulletCrash(Bullet objBullet)//�жϴ����ӵ��뼺���ӵ��Ƿ���ײ
{
	//��ײ����true��û����ײ�򷵻�false
	//ֱ����ײ
	if (pos.X == objBullet.GetPos().X &&
		pos.Y == objBullet.GetPos().Y)
		return true;
	//����Ǳ�Ҫ�ģ�������������ʱ���ܻ���������ͬʱ����ͬһλ��
	//1.���ж��ӵ��Ƿ��ڼ����ӵ��ĸ���λ
	int nArrDir[4][2] = { {0,-1},{0,1},{-1,0},{1,0} };
	for (int i = 0; i < 4; i++)
	{
		if (((pos.X + nArrDir[i][0]) == objBullet.GetPos().X) &&
			((pos.Y + nArrDir[i][1]) == objBullet.GetPos().Y))
		{
			//2.���ݼ����ӵ������жϳ�·���Ƿ���һ��ֱ����
			switch (Dir)
			{
			case UP:
			case DOWN:
			{
				if (pos.X == objBullet.GetPos().X)//X��ͬ
				{
					//3.����Է��ӵ��ڼ����ӵ������£����ж�2���ӵ��ķ����Ƿ��෴
					return (Dir + objBullet.GetDir() == 3) ? true : false;//�෴����ײ
				}
			}
			case LEFT:
			case RIGHT:
			{
				if (pos.Y == objBullet.GetPos().Y)//Y��ͬ
				{
					//3.����Է��ӵ��ڼ����ӵ������ң����ж�2���ӵ��ķ����Ƿ��෴
					return (Dir + objBullet.GetDir() == 3) ? true : false;//�෴����ײ
				}
			}
			default:
				break;
			}
		}
	}
	return false;//����������������ײ
}

int Bullet::GetClock()//��ȡʱ��
{
	return Clock;
}

void Bullet::SetClock(int nClock)//����ʱ��
{
	Clock = nClock;
}

COORD Bullet::GetPos()//��ȡλ��
{
	return pos;
}

bool Bullet::GetIsAlive()//��ȡ�ӵ����״̬
{
	return Alive;
}

void Bullet::SetIsAlive(bool bState)//�����ӵ����״̬
{
	Alive = bState;
}

int Bullet::GetSpeed()//��ȡ�ٶ�
{
	return Speed;
}

int Bullet::GetDir()//��ȡ����
{
	return Dir;
}

//����������������ж��ӵ�����Ӫ
bool Bullet::operator==(Tank objTank)
{
	return Camp == objTank.GetType();
}

//���ظ�ֵ�����������̹���ഴ���ӵ�����̹�˶�������Դ��ݸ��ӵ�
void Bullet::operator=(Tank objTank)
{
	Clock = clock();//��ǰʱ��
	Dir = objTank.GetTankDir();
	Speed = GOD_SPEED;//�ӵ��ٶ�
	pos = objTank.GetPos();//pos��̹�����ĵ�����
	Camp = objTank.GetType();//�ӵ�������Ӫ

	switch (Dir)//ֱ�Ӵ��ڿڷ���
	{
	case UP:
		pos.Y -= 2;
		break;
	case DOWN:
		pos.Y += 2;
		break;
	case LEFT:
		pos.X -= 2;
		break;
	case RIGHT:
		pos.X += 2;
		break;
	}
}

