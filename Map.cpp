#include "Map.h"


Map::Map(){}
Map::~Map(){}

//�����ͼ����
void Map::setMapType(COORD pos, int Type)
{
	map[pos.X][pos.Y] = Type;
}

//��ȡ��ͼ����
int Map::getMapType(COORD pos)
{
	return map[pos.X][pos.Y];
}

//��ս��棨û�жԵ�ͼ���������գ�ֻ�ǻ�������
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

//���ݵ�ͼ�����е�����ͻ�ͼ
void Map::drawMap()
{
	for (short i = 0; i < mainWidth; i++)
		for (short j = 0; j < mainHeight; j++)
		{
			drawImage({ i,j }, map[i][j]);
		}
}

//���ƶ�λ��������Ԫ��
void Map::drawImage(COORD pos, int Type)
{
	switch (Type)
	{
	case 0:				//�յ�
		SetEle(pos.X, pos.Y, "  ");
		break;
	case 1:				//�߽�
		SetEle(pos.X, pos.Y, "��");
		break;	
	}
}

//��ʼ�����棨�Ե�ͼ���鸳ֵ��ͬʱ�����߽�
void Map::initMap()
{
	for (short i = 0; i < mainWidth; i++)
		for (short j = 0; j < mainHeight; j++)
		{
			if (i == 0 || j == 0 || i == mainWidth - 1 || j == mainHeight - 1)
			{
				map[i][j] = 1;
				drawImage({ i,j }, 1);//���ǽ��
			}
			else 
			{
				map[i][j] = 0;
				drawImage({ i,j }, 0);//����ո�
			}
		}
}
