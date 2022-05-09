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

	int initItem(char*, int, char*);
	int initSupplier(char*);
	void findPlace(Batch);
	void removeBatch(int);

public:
	Warehouse();
	void addBatch(char*, char*, int, int, int, int, int, int, int, int, char*);
	void takeFromWarehouse(char*, int);
	void cleanUP(int, int, int);
	void warehouseHistory(int, int, int, int, int, int);
	void currentSupply();
	//friend void sort_arr(int&);
};

#endif
