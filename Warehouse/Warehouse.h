#ifndef _WAREHOUSE
#define _WAREHOUSE

#include "Item.h"
#include "Supplier.h"
#include "Batch.h"
#include "Shelf.h"
#include "Section.h"

class Warehouse
{
private:
	int ID_Warehouse;
	Section Sections[128];
	Item Items[128];
	Batch Batches[128];
	Supplier Suppliers[128];
	int itemCount, batchCount, supplierCount, sectionCount;

	void sort_arr(int arr[2000][3], int n);
	int initItem(char*, int, char*);
	int initSupplier(char*);
	void findPlace(Batch);
	void removeBatch(int);
	Item findItem(char*);

public:
	Warehouse();
	void addBatch(char*, char*, int, int, int, int, int, int, int, int, char*);
	bool takeFromWarehouse(char*, int);
	void cleanUP(int, int, int);
	void warehouseHistory(int, int, int, int, int, int);
	void currentSupply();
};

#endif
