#include "graf.h"
#include "Prior_queue.h"
double Dijkstra(Vertex* village, int nSize, int First)
{
	PQueue* PQ = PQInit(nSize);
	double* PathLen = (double*)calloc(nSize, sizeof(double));
	if (!PathLen)
	{
		printf("Unable to allocate memory!");
		return -1;
	}
	double* PathTime = (double*)calloc(nSize, sizeof(double));
	if (!PathTime)
	{
		printf("Unable to allocate memory!");
		return -1;
	}
	PQEnQueue(PQ, First, 0);
	for (int i = 0; i < nSize; i++)
	{
		if (i == First)
			continue;
		PathLen[i] = INT_MAX; //infinity
	}
	double x = 0;
	while (!PQEmpty(PQ))
	{
		int k = PQDeQueue(PQ);
		if (village[k].vNext->nInfo) //if shop
		{
			village[First].vShopNumb = k;
			village[First].allTime = PathTime[k];
			x = village[First].road = PathLen[k];
			PQRealease(&PQ);
			break;
		}
		ListItem* pVert = village[k].vNext;
		while (pVert)
		{
			int nNode = pVert->nIndex; //nb of node
			if (PathLen[k] + pVert->dist < PathLen[nNode])
			{
				PathLen[nNode] = PathLen[k] + pVert->dist;
				PathTime[nNode] = PathTime[k] + pVert->time;
				PQEnQueue(PQ, nNode, PathLen[nNode]);
				village[First].Path[nNode] = k;
			}
			pVert = pVert->nNext;
		}
	}
	free(PathLen);
	free(PathTime);
	return x;
}

void DFS(Vertex* village, int* pVisit, int x, int speed)
{
	village[x].vNext->time = village[x].vNext->dist / speed;
	for (ListItem* pV = village[x].vNext; pV; pV = pV->nNext)
		pV->time = pV->dist / speed;
	pVisit[x] = 1;
	for (ListItem* pV2 = village[x].vNext; pV2; pV2 = pV2->nNext)
		if (!pVisit[pV2->nIndex])
			DFS(village, pVisit, pV2->nIndex, speed);
}