#pragma once
#include "Map.h"

class Tank 
{
public:
	Tank();//默认构造函数

	Tank(COORD npos, int nDir, int nType, int nSpeed, int nClock, int nKill) :
		pos(npos), Dir(nDir), Type(nType),
		Speed(nSpeed), Clock(nClock), Kill(nKill) {}
		//构造函数
	~Tank();//析构函数

	//全局的一个地图 
	static Map objTankMap;
	//全局的一个坦克数组，包含所有坦克，第一个下标是玩家
	static Tank arrTank[5];

	//地图相关函数 
	//静态方法，用于在游戏类里面将游戏地图转换为坦克地图
	static void TransformMap(Map objGameMap);
	//静态方法，用于在坦克地图上某一点画出一圈障碍，防止坦克碰撞
	static void IncreaseRange(COORD pos); 

	//坦克相关函数
	//画坦克
	void DrawTank();
	//擦除坦克
	void ClearTank();
	//坦克移动
	void MoveTank(int nDir);
	//坦克碰撞检测
	bool TankCollision(COORD pos);
	//判断该坐标是否在坦克身上
	bool TankBodyExist(COORD pos);
	

	//坦克设置相关函数
	//获取坦克最后一次响应时间
	int GetClock();
	//设置坦克最后一次响应时间
	void SetClock(int nClock);
	//获取坦克类型（敌方，己方）
	int GetType();
	//设置坦克类型，用于坦克初始化
	void SetType(int nType);
	//获取坦克速度
	int GetSpeed();
	//获取坦克方向
	int GetTankDir();
	//获取坦克坐标
	COORD GetPos();
	//设置坦克坐标
	void SetPos(COORD pos);
	//获取坦克ID
	int GetID();
	//设置坦克ID
	void SetID(int nID);

	//记录的函数
	//坦克杀敌数增加
	void AddKillNumber();
	//获取坦克杀敌数
	int GetKillNumber();
	
private:
	//坦克坐标
	COORD pos;
	//坦克的方向
	int Dir;
	//坦克的类型(玩家坦克PLAYER_TANK，敌人坦克ENEMY_TANK)
	int Type;
	//坦克的最后一次响应时间
	int Clock;
	//坦克的移动速度
	int Speed;
	//坦克的ID
	int ID;
	//坦克的杀敌数
	int Kill;
	
};