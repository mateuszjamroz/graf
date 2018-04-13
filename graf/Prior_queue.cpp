#include "Prior_queue.h"

void UpdateDown(PQueue* PQ, int l, int p);
void UpdateUp(PQueue* PQ, int l, int p);

//---------------------------------------

PQueue* PQInit(int nSize)
{
	PQueue* pqList = (PQueue*)calloc(1, sizeof(PQueue));
	if (!pqList)
	{
		printf("Unable to allocate memory!\n");
		return NULL;
	}
	PQItem* pqItem = (PQItem*)calloc(nSize, sizeof(PQItem));
	if (!pqItem)
	{
		printf("Unable to allocate memory!\n");
		return NULL;
	}
	pqList->PQCurrSize = 0;
	pqList->PQSize = nSize;
	pqList->PQueue = pqItem;
	return pqList;
}

int PQEmpty(PQueue* PQ)
{
	return !(PQ->PQCurrSize);
}

void PQEnQueue(PQueue* PQ, int nKey, int Prior)
{
	if (PQ->PQCurrSize==PQ->PQSize)
	{
		printf("Queue is full!\n");
		return;
	}
	PQ->PQueue[PQ->PQCurrSize] = { nKey,Prior };
	UpdateUp(PQ, 0, PQ->PQCurrSize);
	PQ->PQCurrSize++;
}

int PQDeQueue(PQueue* PQ)
{
	if (PQEmpty(PQ))
	{
		printf("Queue is empty!\n");
		return 1;
	}
	int tmp = PQ->PQueue[0].nKey;
	PQ->PQCurrSize--;
	PQ->PQueue[0] = PQ->PQueue[PQ->PQCurrSize];
	UpdateDown(PQ, 0, PQ->PQCurrSize);
	return tmp;
}

void PQRealease(PQueue** PQ)
{
	while (PQEmpty(*PQ))
	{
		free((*PQ)->PQueue);
	}
	free(*PQ);
	*PQ = NULL;
}

void DecreaseKey(PQueue* PQ, int ix, int Prior)
{
	
	if (PQ->PQueue[ix].nPrior > Prior)
	{
		printf("Unable to decrease prior!\n");
		return;
	}
	PQ->PQueue[ix].nPrior = Prior;
	UpdateUp(PQ, ix, PQ->PQCurrSize - 1);

}

void IncreaseKey(PQueue* PQ, int ix, int Prior)
{
	
	if (PQ->PQueue[ix].nPrior < Prior)
	{
		printf("Unable to increase prior!\n");
		return;
	}
	PQ->PQueue[ix].nPrior = Prior;
	UpdateDown(PQ, 0, ix);


}
//-------------------------------


void UpdateDown(PQueue* PQ, int l, int p)
{
	if (l == p)
		return;
	int i = l;
	int j = (i * 2) + 1;
	PQItem temp = PQ->PQueue[i];
	while (j <= p)
	{
		if (j < p)
		{
			if (PQ->PQueue[j].nPrior > PQ->PQueue[j + 1].nPrior)
				j++;
		}
		if (temp.nPrior < PQ->PQueue[j].nPrior)
			break;
		PQ->PQueue[i] = PQ->PQueue[j];
		i = j;
		j = (2 * i) + 1;
	}
	PQ->PQueue[i] = temp;
}


void UpdateUp(PQueue* PQ, int l, int p)
{
	if (l == p)
		return;
	int i = p;
	int j = (i - 1) / 2;
	PQItem temp = PQ->PQueue[i];
	while (i > l &&PQ->PQueue[j].nPrior > temp.nPrior ) //!!!!!!
	{
		PQ->PQueue[i] = PQ->PQueue[j];
		i = j;
		j = (i - 1) / 2;
	}
	PQ->PQueue[i] = temp;
}