// graf.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "graf.h"
#include "Prior_queue.h"

void ReadFile(Vertex* village, FILE* f);

int main(int argc, char** argv)
{
	if (argc != 3)
	{
		printf("There is no input or output file!");
		return -1;
	}
	FILE* f = NULL;
	if (!(f = fopen(argv[1], "r")))
	{
		printf("Cannot open file!");
		return -1;
	}
	int nSize;
	fscanf(f, "%d", &nSize);
	Vertex* village = (Vertex*)calloc(nSize, sizeof(Vertex));
	if (!village)
	{
		printf("Unable to allocate memory!");
		return -1;
	}
	for (int i = 0; i < nSize; i++)
		village[i].vNext = NULL; //!
	for (int i = 0; i < nSize; i++)
	{
		village[i].Path = (int*)calloc(nSize, sizeof(int));
		if (!village[i].Path)
		{
			printf("Unable to allocate memory!");
			return -1;
		}
	}
	ReadFile(village, f);
	fclose(f);
	int* pVisit = (int*)calloc(nSize, sizeof(int));
	if (!pVisit)
	{
		printf("Unable to allocate memory!");
		return -1;
	}
	for (int i = 0; i < nSize; i++)
		DFS(village, pVisit, i, SPD);
	free(pVisit);
	int* Path2 = (int*)calloc(nSize, sizeof(int));
	if (!Path2)
	{
		printf("Unable to allocate memory!");
		return -1;
	}
	for (int i = 0; i < nSize; i++)
	{
		if (!village[i].vInfo)
		{
			Dijkstra(village, nSize, i);
			memcpy(Path2, village[i].Path, nSize * sizeof(int));
			memset(village[i].Path, -1, nSize * sizeof(int));
			int k = village[i].vShopNumb;
			village[i].Path[0] = k;
			for (int j = 1; k != i; j++)
			{
				village[i].Path[j] = Path2[k];
				k = Path2[k];
			}
		}
	}
	int temp;
	int tempnb = 0;
	for (int i = 0; i < nSize; i++)
	{
		for (int j = 0; j < nSize; j++)
		{
			if (village[i].Path[j] >= 0)
				tempnb++;
			for (int k = 0; k < tempnb / 2; k++)
			{
				temp = village[i].Path[tempnb - k - 1];
				village[i].Path[tempnb - k - 1] = village[i].Path[k];
				village[i].Path[k] = temp;
			}
			tempnb = 0;
		}
	}
	free(Path2);

	FILE* fout = NULL;
	if (!(fout = fopen(argv[2], "w")))
	{
		printf("Cannot open a file!");
		return -1;
	}
	for (int i = 0; i < nSize; i++)
	{
		if (!village[i].vInfo)
		{
			fprintf(fout, "%d. \tNearest shop: %d \tDistance: %.3lf [km] \tTime: %.3lf [h] \tPath: ", i, village[i].vShopNumb, village[i].road, village[i].allTime);
			for (int j = nSize; j >=0; j--)
			{
				if (village[i].Path[j] < 0)
					continue;
				fprintf(fout, "%d ", village[i].Path[j]);
			}
			fprintf(fout, "\n");
		}
	}
	fclose(fout);
	free(village->vNext);
	free(village);
	return 0;

}

void ReadFile(Vertex* village, FILE* f)
{
	int nVer;
	while (!feof(f))
	{
		fscanf(f, "%d", &nVer);
		ListItem* v = (ListItem*)calloc(1, sizeof(ListItem));
		if (!v)
		{
			printf("Unable to allocate memory!");
			return;
		}
		if (!village[nVer].vNext)
		{
			village[nVer].vNext = v;
			fscanf(f, "%d %lf %d", &(v->nIndex), &(v->dist), &(v->nInfo));
			village[nVer].vInfo = v->nInfo;
		}
		else
		{
			ListItem* a = village[nVer].vNext;
			while (a->nNext)
				a = a->nNext;
			a->nNext = v;
			fscanf(f, "%d %lf %d ", &(v->nIndex), &(v->dist), &(v->nInfo));
			village[nVer].vInfo = v->nInfo;
		}
	}
}
