#ifndef _SHELF
#define _SHELF

#include "Batch.h"

struct Shelf
{
	int ID_Shelf;
	int volume = 100;
	Batch batchList[128]; 
	int batches;
	Shelf()
	{
		batches = 0;
		for (int i = 0; i < 128; i++)
		{
			batchList[i].setBatch_ID(-1);
		}
	}
};

#endif

