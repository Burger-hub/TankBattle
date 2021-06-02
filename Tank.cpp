#include "Tank.h"


extern const char TankSharp[2][4][3][7];
Map Tank::objTankMap;//Tank类里面的全局地图
Tank Tank::arrTank[5];//对象数组

Tank::Tank() {}
Tank::~Tank() {}

void Tank::TransformMap(Map objGameMap)//原始地图转换为坦克地图，即多画一圈，结果储存在全局地图中
{
	objTankMap.initMap();
	//遍历地图，如果遇到边界，画一圈障碍物(仅仅改变类型）
	for (short i = 0; i < mainWidth; i++)
	{
		for (short j = 0; j < mainHeight; j++)
		{
			int nType = objGameMap.getMapType({ i,j });
			if (nType == 1)//1表示有障碍
				IncreaseRange({ i,j });
		}
	}
}

void Tank::IncreaseRange(COORD pos)//将该坐标周围的位置都设置为障碍，但不画出来（主界面以内）
{
	for (short nX = pos.X - 1; nX <= pos.X + 1; nX++)
		for (short nY = pos.Y - 1; nY <= pos.Y + 1; nY++)//遍历以坐标为中心的九宫格
		{
			if (nX >= 0 && nX < mainWidth && nY >= 0 && nY < mainHeight)	//当在地图范围内时，增加
				objTankMap.setMapType({ nX,nY }, 1);
		}
}

void Tank::DrawTank()//将坦克在地图中画出
{	
	for (short nY = pos.Y - 1, i = 0; nY < pos.Y + 2; nY++, i++)
	{
		SetEle(pos.X - 1, nY, TankSharp[Type % 10][Dir][i]);//测试无问题
	}
}

void Tank::ClearTank()//将坦克从屏幕上删除
{
	//根据中心点，推断出起点，直接填充空格     	
	for (short nY = pos.Y - 1; nY < pos.Y + 2; nY++)
	{
		SetEle(pos.X - 1, nY, "      ");
	}
}

void Tank::MoveTank(int nDir)//移动坦克
{
	//只要调用移动，必然重画坦克
	ClearTank();
	//1.计算出移动后的中心点
	COORD TempPos = pos;
	if (nDir + Dir == 3)//根据base.h中的定义
	{
		//反向，则坐标不变,只改变方向，不需要碰撞检测
		Dir = nDir;
		DrawTank();
		return;
	}
	else {
		//不是反向，则根据方向改变坐标
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
		//2.对移动后的点进行碰撞检测
		if (TankCollision(TempPos))
		{
			//如果可以移动，则更改坐标，画出来
			pos = TempPos;
			Dir = nDir;
			DrawTank();
		}
		else //如果不可以移动，则不移动,只改变坦克的方向
		{
			Dir = nDir;
			DrawTank();
		}
	}
}

bool Tank::TankCollision(COORD pos)//碰撞检测,ture表示可以移动
{
	//遍历坦克数组，判断是否会撞到除自己以外的坦克
	for (int i = 0; i < 6; i++)
	{
		//排除自身
		if (this == &arrTank[i])
			continue;    //结束本次循环        
		else
		{	//否则，测试以该点为中心的所有点是不是会撞到
			for (short nX = pos.X - 1; nX < pos.X + 2; nX++)
				for (short nY = pos.Y - 1; nY < pos.Y + 2; nY++)
				{
					//检测该坦克边缘点是否在别的坦克上
					if (arrTank[i].TankBodyExist({ nX,nY }))
						return false;      //如果在别的坦克上，则不可以移动  
				}

		}
	}
	//没有撞到坦克，判断是否到边界
	if (pos.X >= 0 && pos.X < mainWidth && pos.Y >= 0 && pos.Y < mainHeight &&
		Tank::objTankMap.getMapType(pos) == 0)//后一个判断保证坦克不会被障碍物碰到
	{
		return true;//没有被撞到，可以移动
	}
	return false;//碰到了边界
}

bool Tank::TankBodyExist(COORD npos)//该坐标是否在坦克身上
{
	for (short nX = pos.X - 1; nX < pos.X + 2; nX++)
		for (short nY = pos.Y - 1; nY < pos.Y + 2; nY++)//遍历坦克中心九宫格
		{
			if (npos.X == nX && npos.Y == nY)
				return true;//输入坐标在坦克身上
		}
	return false;//输入坐标不在坦克身上
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


