#include "Bullet.h"

Bullet::Bullet(){}
Bullet::~Bullet(){}

void Bullet::MoveBullet()//移动子弹
{
	ClearBullet();
	//不需要碰撞判断，不需要写入地图，只需要根据方向改变坐标，画出来即可
	switch (Dir)
	{
	case UP:
		pos.Y--;//注意原点位置在左上方
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

void Bullet::DrawBullet()//画出子弹
{
	SetEle(pos.X, pos.Y, "●");
}

void Bullet::ClearBullet()//清除子弹
{
	SetEle(pos.X, pos.Y, "  ");
}

bool Bullet::BulletCrash(Bullet objBullet)//判断传入子弹与己方子弹是否相撞
{
	//碰撞返回true，没有碰撞则返回false
	//直接碰撞
	if (pos.X == objBullet.GetPos().X &&
		pos.Y == objBullet.GetPos().Y)
		return true;
	//检测是必要的，否则正面相遇时可能会错过而不会同时出现同一位置
	//1.先判断子弹是否在己方子弹四个方位
	int nArrDir[4][2] = { {0,-1},{0,1},{-1,0},{1,0} };
	for (int i = 0; i < 4; i++)
	{
		if (((pos.X + nArrDir[i][0]) == objBullet.GetPos().X) &&
			((pos.Y + nArrDir[i][1]) == objBullet.GetPos().Y))
		{
			//2.根据己方子弹方向，判断出路径是否在一条直线上
			switch (Dir)
			{
			case UP:
			case DOWN:
			{
				if (pos.X == objBullet.GetPos().X)//X相同
				{
					//3.如果对方子弹在己方子弹的上下，则判断2个子弹的方向是否相反
					return (Dir + objBullet.GetDir() == 3) ? true : false;//相反则碰撞
				}
			}
			case LEFT:
			case RIGHT:
			{
				if (pos.Y == objBullet.GetPos().Y)//Y相同
				{
					//3.如果对方子弹在己方子弹的左右，则判断2个子弹的方向是否相反
					return (Dir + objBullet.GetDir() == 3) ? true : false;//相反则碰撞
				}
			}
			default:
				break;
			}
		}
	}
	return false;//都不满足条件则不碰撞
}

int Bullet::GetClock()//获取时间
{
	return Clock;
}

void Bullet::SetClock(int nClock)//设置时间
{
	Clock = nClock;
}

COORD Bullet::GetPos()//获取位置
{
	return pos;
}

bool Bullet::GetIsAlive()//获取子弹存活状态
{
	return Alive;
}

void Bullet::SetIsAlive(bool bState)//设置子弹存活状态
{
	Alive = bState;
}

int Bullet::GetSpeed()//获取速度
{
	return Speed;
}

int Bullet::GetDir()//获取方向
{
	return Dir;
}

//重载运算符，用于判断子弹的阵营
bool Bullet::operator==(Tank objTank)
{
	return Camp == objTank.GetType();
}

//重载赋值运算符，用于坦克类创建子弹（把坦克对象的特性传递给子弹
void Bullet::operator=(Tank objTank)
{
	Clock = clock();//当前时刻
	Dir = objTank.GetTankDir();
	Speed = GOD_SPEED;//子弹速度
	pos = objTank.GetPos();//pos是坦克中心的坐标
	Camp = objTank.GetType();//子弹所属阵营

	switch (Dir)//直接从炮口发射
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

