#pragma once
#include "Base.h"

class Map {
private:
	int map[12][22];
public:
	Map();
	~Map();
	void setMapType(COORD pos,int Type);//��������
	int getMapType(COORD pos);//��ȡ����
	void clearMap();//�����ͼ���ػ��߽�
	void drawMap();//����������ͼ�����е�����ͻ�ͼ
	
	void drawImage(COORD pos, int Type);//�������ͻ�����ǰ�����ͼ��
	void initMap();//��ʼ����ͼ�����ϱ߿�

};