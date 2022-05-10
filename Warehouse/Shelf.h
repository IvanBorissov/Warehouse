#ifndef _SHELF
#define _SHELF

#include "Batch.h"

struct Shelf
{
	int ID_Shelf;
	int volume = 100;
	Batch batchList[128];   
	int batches;
};

#endif

