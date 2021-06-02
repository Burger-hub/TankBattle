#pragma once
#include "Bullet.h"

class Game 
{
public:
	Game();
	~Game();
	void setGameLevel(int nGameLevel);
	//减少机会数
	void ReduceLives();
	void SetLives(int nLives);
	
	//游戏环境初始化（完成前期准备）
	void GameInit();
	//游戏运行准备初始化
	void GameRunInit();
	//游戏运行主界面(返回值为当前游戏状态，0结束，1过关)
	int GameStart();

	//游戏运行状态栏 
	void GameStatusBar();

	//游戏界面,能够实现关卡转换
	void GameUI();
	
	//开始界面(获取按键输入，开始游戏操作)
	//退出后，设置当前游戏模式
	void BeginUI();
	//游戏管理主循环(管理开始界面，欢迎界面，游戏运行界面)
	void Run();

	//子弹相关    
	//创建子弹(参数为开炮的坦克)
	void CreateBullet(Tank objTank);
	//子弹碰撞处理(参数为子弹的引用)
	void BulletCollision(Bullet& objBullet);
	//子弹数组管理(清除无效子弹)
	void BulletManage();

	//坦克相关     
	//坦克重置(根据传入坦克的参数决定重置哪一只，也可用于坦克初始化)
	void ResetTank(Tank& objTank);
	//敌方坦克移动(用随机数)
	void MoveNPCTank(int nID);
	//获取用户输入,返回值为上下左右开火
	int getPlayerInput();

private:
	//地图类对象，里面只保存障碍物信息
	Map objMap;

	//地图上的子弹数组，数目不确定，所以用动态数组
	vector<Bullet> vecBullets;

	//玩家的分数
	int Score;
	//游戏关卡,通关后刷新
	int GameLevel;
	//游戏页面选择（开始，退出）
	int GameMode;
	//机会数
	int Lives;
	
};