#ifndef _GRAF_
#define _GRAF_

#include <memory.h>
#include <stdlib.h>
#include <stdio.h>

#define SPD 4

typedef struct tagListItem
{
	struct tagListItem* nNext;
	double dist;
	double time;
	int nInfo; //0-dom, 1 -sklep
	int nIndex; //numer punktu
}ListItem;

typedef struct
{
	ListItem* vNext;
	double road;
	int vInfo;
	int vShopNumb;
	int* Path;
	double allTime;
}Vertex;

double Dijkstra(Vertex* village, int nSize, int First);
void DFS(Vertex* village, int* pVisit, int x, int speed);

#endif
