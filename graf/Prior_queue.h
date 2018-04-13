#ifndef _PRIOR_QUEUE_
#define _PRIOR_QUEUE_

#include <stdlib.h>
#include <stdio.h>
#include <memory.h> 
#include <time.h>

using namespace std;

typedef struct tagPQItem
{
	int nKey;
	int nPrior;
}PQItem;

typedef struct tagPQueue
{
	PQItem* PQueue;
	int PQSize;
	int PQCurrSize;
}PQueue;



PQueue* PQInit(int);
int PQEmpty(PQueue* PQ);
void PQEnQueue(PQueue* PQ, int nKey, int Prior);
int PQDeQueue(PQueue* PQ);
void PQRealease(PQueue** PQ);
void DecreaseKey(PQueue* PQ, int nKey, int Prior);
void IncreaseKey(PQueue* PQ, int nKey, int prior);


#endif
