#pragma once
#include "base.h"
#include "Tank.h"

class Bullet
{
public:
	Bullet();//默认构造函数
	Bullet(COORD npos, int nDir, int nSpeed, int nClock) :pos(npos), Dir(nDir),
		Speed(nSpeed), Clock(nClock) {}//构造函数
	~Bullet();

	//子弹类的移动
	void MoveBullet();
	//画子弹
	void DrawBullet();
	//擦除子弹
	void ClearBullet();
	//判断该子弹是否会碰撞
	bool BulletCrash(Bullet objBullet);


	//获取子弹上次移动的时间（用于控制子弹的速度）
	int GetClock();
	//设置子弹上次移动的时间
	void SetClock(int nClock);
	//获取子弹的坐标
	COORD GetPos();
	//获取子弹存活状态
	bool GetIsAlive();
	//设置子弹存活状态
	void SetIsAlive(bool bState);
	//获取子弹速度
	int GetSpeed();
	//获取子弹方向
	int GetDir();
	
	//重载等号运算符，用于子弹类和坦克类的类型判断
	bool operator==(Tank objTank);
	//重载赋值运算符，用于坦克类创建子弹
	void operator=(Tank objTank);

private:
	//子弹的位置
	COORD pos;
	//子弹的方向
	int Dir;
	//子弹上次移动的时间
	int Clock;
	//子弹的移动速度
	int Speed;
	//子弹的存活状态
	bool Alive;
	// 子弹的阵营
	int Camp;
};