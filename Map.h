#pragma once
#include "Base.h"

class Map {
private:
	int map[12][22];
public:
	Map();
	~Map();
	void setMapType(COORD pos,int Type);//载入数据
	int getMapType(COORD pos);//读取数据
	void clearMap();//清除地图，重画边界
	void drawMap();//根据整个地图数组中点的类型画图
	
	void drawImage(COORD pos, int Type);//根据类型画出当前坐标的图像
	void initMap();//初始化地图（加上边框）

};