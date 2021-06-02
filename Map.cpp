#include "Map.h"


Map::Map(){}
Map::~Map(){}

//载入地图数据
void Map::setMapType(COORD pos, int Type)
{
	map[pos.X][pos.Y] = Type;
}

//读取地图数据
int Map::getMapType(COORD pos)
{
	return map[pos.X][pos.Y];
}

//清空界面（没有对地图数组进行清空，只是画出来了
void Map::clearMap()
{
	for (short i = 0; i < mainWidth; i++)
		for (short j = 0; j < mainHeight; j++)
		{
			if (i == 0 || j == 0 || i == mainWidth-1 || j == mainHeight-1)
				drawImage({ i,j }, 1);
			else
				drawImage({ i,j }, 0);
		}
}

//根据地图数组中点的类型画图
void Map::drawMap()
{
	for (short i = 0; i < mainWidth; i++)
		for (short j = 0; j < mainHeight; j++)
		{
			drawImage({ i,j }, map[i][j]);
		}
}

//在制定位置输出相关元素
void Map::drawImage(COORD pos, int Type)
{
	switch (Type)
	{
	case 0:				//空地
		SetEle(pos.X, pos.Y, "  ");
		break;
	case 1:				//边界
		SetEle(pos.X, pos.Y, "■");
		break;	
	}
}

//初始化界面（对地图数组赋值，同时画出边界
void Map::initMap()
{
	for (short i = 0; i < mainWidth; i++)
		for (short j = 0; j < mainHeight; j++)
		{
			if (i == 0 || j == 0 || i == mainWidth - 1 || j == mainHeight - 1)
			{
				map[i][j] = 1;
				drawImage({ i,j }, 1);//输出墙壁
			}
			else 
			{
				map[i][j] = 0;
				drawImage({ i,j }, 0);//输出空格
			}
		}
}
