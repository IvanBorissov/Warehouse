#ifndef _SHELF
#define _SHELF

#include "Batch.h"

struct Shelf
{
	int ID_Shelf;
	int volume = 1000;
	Batch batchList[1024];   
	int batches;
};

#endif

