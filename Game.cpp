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

//游戏环境初始化（完成前期准备）//已测试
void Game::GameInit()
{	//隐藏光标
	ShowCursor(false);
	//切换输入法        
	ChangeEnglish();
	//设置控制台标题和大小
	SetWindowSize("TankBattle", 40, 30);	
}

//游戏运行初始化（坦克的初始化）（已测试，位置待调整）
void Game::GameRunInit()
{
	//初始化
	objMap.clearMap();
	
	//初始化玩家坦克
	Tank TempTank0({ 5,10 }, UP, PLAYER_TANK, FAST_SPEED, clock(), 0);//调用time.h库
	Tank::arrTank[0] = TempTank0;
	Tank::arrTank[0].SetID(0);
	Tank::arrTank[0].DrawTank();//画出玩家坦克
	
	//初始化敌方坦克（类型,编号,位置）
	for (int i = 1; i < 5; i++) {
		Tank TempTanki({ 3,6 }, UP, ENEMY_TANK, LOW_SPEED, clock(), 0);//随便选了个位置构造坦克
		Tank::arrTank[i] = TempTanki;
		Tank::arrTank[i].SetID(i);
		ResetTank(Tank::arrTank[i]);
	}
	//初始化分数
	Score = 0;	
}

//游戏运行主界面(返回值为当前游戏状态，0结束，1过关)
int Game::GameStart()
{
	int nKill = GameLevel * 10;//目标杀敌数
	int nState = -1;//用于存放游戏状态 （-1表示继续，1表示升级，0表示退出）
	int nOper = -1;//获取玩家按键操作  (-1表示不输入)
	GameRunInit();
	while (nState == -1)//若为-1则一直循环
	{
		if (Lives == 0) {
			GameLevel = 7;
			nState = 0;//如果机会用完，则退出循环，退出标志为0
		}
		//如果过关了，关卡自增，则退出游戏循环，退出标志为1
		if (Tank::arrTank[0].GetKillNumber() >= nKill)
		{
			GameLevel++;
			nState = 1;
		}

		//显示游戏状态栏
		GameStatusBar();

		//获取按键输入
		nOper = getPlayerInput();
		if (nOper != -1)	//玩家坦克尝试操作，值为-1表示不输入（用-1是因为其他值被占了）
		{
			//判断是否到达响应时间（控制坦克速度，包括移动速度和发射速度）
			if (clock() - Tank::arrTank[0].GetClock() > Tank::arrTank[0].GetSpeed())
			{
				if (nOper != FIRE)	//移动
				{
					Tank::arrTank[0].MoveTank(nOper);
				}
				else	//开炮
				{
					CreateBullet(Tank::arrTank[0]);
				}
				//只要玩家操作，操作状态就置为空 作为回归初始化，否则会一直移动
				nOper = -1;
				//重置坦克时间，响应时间为（当前时间-上次重置的时间），即上次操作距现在的时间
				Tank::arrTank[0].SetClock(clock());
			}
		}
		
		//遍历敌方坦克数组，如果到达响应时间，则操作
		for (int i = 1; i < 5; i++)
		{
			if (clock() - Tank::arrTank[i].GetClock() > Tank::arrTank[i].GetSpeed())
			{
				//根据下标进行坦克操作
				MoveNPCTank(i);//移动或开炮
				Tank::arrTank[i].SetClock(clock());//重置时间
			}

		}
		//遍历子弹数组，看是否到达响应时间
		for (unsigned int i = 0; i < vecBullets.size(); i++)//size表示数组的大小
		{
			if (clock() - vecBullets[i].GetClock() > vecBullets[i].GetSpeed())
			{
				//子弹移动
				vecBullets[i].MoveBullet();
				//子弹的碰撞处理
				BulletCollision(vecBullets[i]);
				//重置时间
				vecBullets[i].SetClock(clock());
			}
		}
		//调用子弹数组整理函数，清空无效子弹
		BulletManage();
	}
	return GameLevel;//返回值为0表示结束，1表示升级
}

//状态栏
void Game::GameStatusBar()//已测试，但原理不明
{
	char Buffer[20];//预先分配缓冲区
	
	SetEle(12, 2, "当前关卡:");//%d是int整型变量的格式化输出符号,\n表示换行
	sprintf_s(Buffer, "% d\n", GameLevel);//调用<stdio.h>，
	SetEle(18, 2, Buffer);//缓冲区，缓冲区大小，格式字符串
	
	SetEle(12, 3, "剩余机会数:");
	sprintf_s(Buffer, "% d\n", Lives);
	SetEle(18, 3, Buffer);
	
	SetEle(12, 5, "目标杀敌数:");
	sprintf_s(Buffer, "% d\n", GameLevel*10);
	SetEle(18, 5, Buffer);
	
	SetEle(12, 4, "当前杀敌数:");
	sprintf_s(Buffer, "% d\n", Tank::arrTank[0].GetKillNumber());
	SetEle(18, 4, Buffer);
}

//游戏界面,能够实现关卡转换
void Game::GameUI()           //检查无问题
{
	//清屏，初始化单人游戏的所有变量，地图，坦克位置
	objMap.clearMap();
	//获取当前游戏状态
	setGameLevel(1);
	
	//获取当前的关卡
	while (GameLevel<=5)
	{
		//放入坦克地图
		Tank::TransformMap(objMap);
		objMap.drawMap(); 
		char Buffer[5][10] = {"第1关","第2关","第3关","第4关","第5关"};
		SetEle(4, 10, Buffer[GameLevel-1]);//显示当前关卡数
		Sleep(2000);
		objMap.clearMap();
		
		//进入游戏运行主循环，返回值为循环结果
		GameLevel = GameStart();
		//一关结束，清空子弹数组
		vecBullets.clear();	
	}
	
	//游戏结束画面
	if (GameLevel==6)//根据返回值的不同显示不同内容
	{
		//通关
		objMap.clearMap();
		SetEle(2, 10, "恭喜你通关啦!!");
	}
	else
	{
		//失败
		objMap.clearMap();
		SetEle(2, 10, "闯关失败!!");
	}
	system("pause");//停止在当前界面
}

//开始界面(获取按键输入，进行游戏模式选择)
void Game::BeginUI()       //已检查
{
	
	//用于存储选择界面的字符串
	char Buffer[2][20] = { "1.开始游戏","2.退出游戏" };
	//用于保存用户的选择
	int nIndex = 1;
	//用于保存选择的亮度条
	int nKeyTemp = 1;
	//判断是否有按键按下
	int nFlag = 1;

	
	//根据用户选择决定选项，高亮等
	//循环检测按键，改变选项
	//J键确认
	while (true)
	{
		//如果有按键按下，根据当前的亮度条画出2个选项
		if (nFlag)                     
		{
			nFlag = 0;
			for (int i = 0; i < 2; i++)
			{
				if (i + 1 == nKeyTemp)//每次按键后都重新画出（通过颜色表示当前停留选项）（未实现）
					SetEle(3, 10 + i, Buffer[i]);
				else
					SetEle(3, 10 + i, Buffer[i]);
			}
		}
		//获取用户输入 （源于网络）
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

//游戏管理主循环(管理开始界面，欢迎界面，游戏运行界面)
void Game::Run()
{
	GameLevel = 1;//游戏初始关卡为1
	SetLives(3);//初始机会数为3
	//初始化界面（画出边界）
	objMap.initMap();
	//延时2s
	Sleep(2000);
	BeginUI();//选择界面
	if (GameMode == 1)
	{
		GameUI();
	}
}

void Game::CreateBullet(Tank objTank)
{
	//1.根据坦克初始化子弹对象
	Bullet TempBullet;
	TempBullet = objTank;
	//2.碰撞检测，如果不越界，则加入子弹数组,画出子弹,否则函数执行结束
	COORD pos = TempBullet.GetPos();//坦克中心的坐标
	if (pos.X > 0 && pos.X < mainWidth-1 && pos.Y > 0 && pos.Y < mainHeight-1)  //包括边框内一圈
	{
		vecBullets.push_back(TempBullet);    //在vector尾部加入一个数据
		TempBullet.DrawBullet();
	}
}

//子弹碰撞检测
void Game::BulletCollision(Bullet& objBullet)
{
	//根据传入子弹的位置位置判断当前子弹的状态，撞到任意东西，当前子弹存活状态都为空
	//撞到障碍，撞到坦克，撞到其他子弹，或者什么都没撞到
	//1.判断是否撞到障碍物和坦克
	COORD pos = objBullet.GetPos();
	int nType = objMap.getMapType(pos);
	switch (nType)
	{
		case 1://撞到边界
		{
			//删除子弹,画出墙
			objBullet.SetIsAlive(false);
			objMap.drawImage(pos, 1);
			return;
			break;
		}
		case 0://若是空地，则检测坦克和子弹
		{	//2.遍历坦克数组，看是否撞到坦克
				for (int i = 0; i < 6; i++)
				{
				if (Tank::arrTank[i].TankBodyExist(pos))	//在坦克身上
				{
					objBullet.SetIsAlive(false);//先清除子弹，再判断是否是自相残杀
					if(!(objBullet == Tank::arrTank[i])){//不是同一阵营/重载函数
						ResetTank(Tank::arrTank[i]);//重置坦克
						if(i!=0){//击中敌方坦克
							Tank::arrTank[0].AddKillNumber();//增加玩家的杀敌数
						}
						else {//敌方击中玩家坦克
							ReduceLives();
						}
					}	
				}
			}
			//3.遍历子弹数组，看是否撞到子弹
			for (unsigned int i = 0; i < vecBullets.size(); i++)
			{
				//把自己排除
				if (&objBullet == &vecBullets[i])
					continue;
				//如果碰撞
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
	
	
void Game::BulletManage()//利用动态数组中已有的函数
	{
		Bullet TempObj;
		for (auto item = vecBullets.cbegin(); item != vecBullets.cend();)//遍历数组
		{
			TempObj = *item;
			if (!TempObj.GetIsAlive())	//如果当前子弹已经死亡
			{
				item = vecBullets.erase(item);//擦除
			}
			else
			{
				++item;
			}
		}
	}
	
// 坦克重置(根据传入坦克的参数决定重置哪一只，也可用于坦克初始化)
void Game::ResetTank(Tank& objTank)
{
		//先擦掉自己
		objTank.ClearTank();
		//如果为玩家坦克，则说明过关了，重置坦克位置
		if (objTank.GetType() == PLAYER_TANK)
		{
			objTank.SetPos({ 5,10 });
		}
		else
		{
			int nSpeed = LOW_SPEED;
			int n = 0;//储存是否重置成功
			//让坦克在四个角随机出现
			while (n == 0) {//若n=1,则说明坦克已放置
				int posType = rand() % 4;
				switch (posType) {
				case 0:
					if (objTank.TankCollision({3 , 3 }))	//如果第一个点没有障碍物
					{
						Tank TempTank({ 3,3 }, DOWN, ENEMY_TANK, nSpeed, clock(), 0);
						TempTank.SetID(objTank.GetID());
						objTank = TempTank;
						n = 1;
					};
					break;
				case 1:
					if (objTank.TankCollision({ 9,3 }))//如果第二个点没有障碍物
					{
						Tank TempTank({ 9,3 }, DOWN, ENEMY_TANK, nSpeed, clock(), 0);
						TempTank.SetID(objTank.GetID());
						objTank = TempTank;
						n = 1;
					};
					break;
				case 2:
					if (objTank.TankCollision({ 3, 19 }))//如果第三个点没有障碍物
					{
						Tank TempTank({ 3, 19 }, UP, ENEMY_TANK, nSpeed, clock(), 0);
						TempTank.SetID(objTank.GetID());
						objTank = TempTank;
						n = 1;
					}
					break;
				case 3:
					if (objTank.TankCollision({ 9, 19 }))//如果第四个点没有障碍物
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
		//画出坦克
		objTank.DrawTank();
}

void Game::MoveNPCTank(int nID)
{
	//随机出当前是移动还是开炮，移动概率得大于开炮
	bool nFire = (rand() % 10 < 2 ? true : false);
	//随机出方向
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