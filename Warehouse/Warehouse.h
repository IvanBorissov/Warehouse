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
	Section Sections[4];
	Item Items[2048];
	Batch Batches[2048];
	Supplier Suppliers[2048];
	int itemCount, batchCount, supplierCount, sectionCount;

	const char	items[10]      =  "items.txt",
				batches[12]    =  "batches.txt" ,
				suppliers[14]  =  "suppliers.txt" , 
				shelves[12]    =  "shelves.txt" ,
				sections[13]   =  "sections.txt" ,
				logFile[8]     =  "log.txt";

	/*void loadItems();
	void loadBatches();
	void loadSuppliers();
	void loadShelves();
	void loadSections();

	void saveItems();
	void saveBatches();
	void saveSuppliers();
	void saveShelves();
	void saveSections();*/
	void saveToLog(int iTypeOfOperation /* 0 - IN; 1 - OUT*/, Batch, char*);
	void saveToCleanUp(Batch);

	void sort_arr(int arr[2048][3], int n);
	int initItem(char*, int, char*);
	int initSupplier(char*);
	void findPlace(Batch);
	void removeBatch(int);
	bool checkDate(char*, int fromDay, int fromMonth, int fromYear, int toDay, int toMonth, int toYear);
	Item findItem(char*);

public:
	Warehouse();
	void addBatch(char*, char*, int, int, int, int, int, int, int, int, char*);
	bool takeFromWarehouse(char*, int);
	void cleanUP(int, int, int);
	void warehouseHistory(int, int, int, int, int, int);
	void currentSupply();
	~Warehouse();
};

#endif
