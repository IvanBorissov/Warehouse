#include <iostream>
#include <cstring>
#include "Item.h"
#include "Supplier.h"
#include "Batch.h"
#include "Shelf.h"
#include "Section.h"
#include "Warehouse.h"
using namespace std;

void Warehouse::sort_arr(int arr[2000][3], int n)
{
	int i, j;
	for (int i = 0; i < n - 1; i++)
	{
		for (int j = 0; j < n - i - 1; j++)
		{
			int sec, shelf, batch;
			
			sec = arr[j][0];
			shelf = arr[j][1];
			batch = arr[j][2];
			Batch a = Sections[sec].Shelves[shelf].batchList[batch];

			sec = arr[j+1][0];
			shelf = arr[j+1][1];
			batch = arr[j+1][2];
			Batch b = Sections[sec].Shelves[shelf].batchList[batch];

			///define operator < for comparing batches by date
			if (a > b)
			{
				swap(arr[j], arr[j + 1]);
			}
		}
	}
}

int Warehouse::initItem(char* name, int volume, char* parameter)
{
	///checks if we already have an item with these parameters
	///if we have already the same item in the database we return the same ID
	///otherwise we make a new item with a new ID and add it to the database 
	Item a(-1, name, volume, parameter);
	for (int i = 0; i < itemCount; i++)
	{
		///define operator == in item
		if (a == Items[i])
		{
			return Items[i].getItem_ID();
		}
	}

	a.setItem_ID(itemCount);
	Items[itemCount] = a;
	itemCount++;

	return a.getItem_ID();
}

int Warehouse::initSupplier(char* name)
{
	///checks if we already have an supplier with the same name 
	///if we have already the same suplier in the database we return the same ID
	///otherwise we make a new supplier with a new ID and add it to the database 
	Supplier a(-1, name);
	for (int i = 0; i < supplierCount; i++)
	{
		///define operator == for Class Supplier
		if (a == Suppliers[i])
		{
			return Suppliers[i].getSupplier_ID();
		}
	}

	a.setSupplier_ID(supplierCount);
	Suppliers[supplierCount] = a;
	supplierCount++;

	return a.getSupplier_ID();
}

void Warehouse::findPlace(Batch b)
{
	int sectionIdx=-1, shelfIdx=-1;
	///checks it there is a place on the same shelf near the same batch
	for (int i = 1; i < sectionCount; i++)
	{
		int nb = Sections[i].shelfCount;
		for (int j = 1; j < nb; j++)
		{
			int nb2 = Sections[i].Shelves[j].batches;
			for (int k = 1; k < nb2; k++)
			{
				if (b == Sections[i].Shelves[j].batchList[k])
				{
					sectionIdx = i; shelfIdx = j;
					if (Sections[i].Shelves[j].volume - b.getVolume() >= 0)
					{
						int count = Sections[i].Shelves[j].batches++;
						Sections[i].Shelves[j].batchList[count] = b;
						Sections[i].Shelves[j].volume -= b.getVolume();
						///write to log file
						return;
					}
				}
			}

		}
	}

	///There was no room for the batch on the same shelf
	int possiblePlace[2000][2], placeCounter=0;
	///going throgh the whole warehouse to find all the possible places for the batch
	for (int i = 1; i < sectionCount; i++)
		{
			int nb = Sections[i].shelfCount;
			for (int j = 1; j < nb; j++)
			{
				int nb2 = Sections[i].Shelves[j].batches;
				int volume = Sections[i].Shelves[j].volume;
				bool lamp = false;
				for (int k = 1; k < nb2; k++)
				{
					Batch a = Sections[i].Shelves[j].batchList[k];
					if (b != a && b.getItem_ID() == a.getItem_ID())
					{
						lamp = true;
						break;
					}
				}
				if (lamp == false && volume - b.getVolume() >= 0)
				{
					possiblePlace[placeCounter][0] = i;
					possiblePlace[placeCounter][1] = j;
					placeCounter++;
				}

			}
		}

	if (placeCounter == 0)
	{
		cout << "No place for the current Batch. Warehouse full" << endl;
		return;
	}
	
	int minSection=1e31-1, minShelf=1e31-1;
	if (sectionIdx != -1 && shelfIdx != -1)
	{
		
		for (int i = 0; i < placeCounter; i++)
		{
			if (abs(minSection - sectionIdx) > abs(possiblePlace[i][0] - sectionIdx))
			{
				minSection = possiblePlace[i][0];
				minShelf = possiblePlace[i][1];
			}
			if (abs(minSection - sectionIdx) == abs(possiblePlace[i][0] - sectionIdx)
				&& abs(minShelf - shelfIdx) > abs(possiblePlace[i][1] - sectionIdx))
			{
				minShelf = possiblePlace[i][1];
			}
		}
	}
	else
	{
		///no limitations first possible place
		minSection = possiblePlace[0][0];
		minShelf = possiblePlace[0][1];
	}

	int cnt = Sections[minSection].Shelves[minShelf].batches++;
	Sections[minSection].Shelves[minShelf].batchList[cnt] = b;
	Sections[minSection].Shelves[minShelf].volume -= b.getVolume();
	///write to log file
}

void Warehouse::removeBatch(int b_ID)
{
	///separate ID of the batches from their count
	///set default values for the batch
	///remove batch from its shelf
}

Item Warehouse::findItem(char* name)
{
	for (int i = 0; i < itemCount; i++)
	{
		if (strcmp(name, Items[i].getItem_name()))
		{
			return Items[i];
		}
	}
	///item does not exist
	char n[3] = { "No" };
	Item a(-1, n, -1, n);
	return a;
}

Warehouse::Warehouse()
{
	itemCount = batchCount = supplierCount = sectionCount = 0;
}

void Warehouse::addBatch(char* itemName, char* suppName, int entryDay, int entryMonth, int entryYear, int expiryDay, int expiryMonth, int expiryYear, int volumeForOne, int quantity, char* basicParameter)
{
	int ID_Item, ID_Supplier;
	ID_Item = initItem(itemName, volumeForOne, basicParameter);
	ID_Supplier = initSupplier(suppName);
	Batch a(batchCount, ID_Item, ID_Supplier, entryDay, entryMonth, entryYear, quantity, expiryDay, expiryMonth, expiryYear, volumeForOne);
	Batches[batchCount] = a;
	findPlace(a);
	///history file
	batchCount++;
}

bool Warehouse::takeFromWarehouse(char* name, int quantity)
{
	int possibleBatches[2000][3], count = 0, totalVolume = 0;
	
	///write findItem by Item name
	Item a = findItem(name);
	if (a.getItem_ID() == -1)
	{
		cout << "No such Item in the warehouse" << endl;
		return false;
	}

	for (int i = 0; i < sectionCount; i++)
	{
		int nb = Sections[i].shelfCount;
		for (int j = 0; j < nb; j++)
		{
			int nb2 = Sections[i].Shelves[j].batches;
			for (int k = 0; k < nb2; k++)
			{
				Batch temp = Sections[i].Shelves[j].batchList[k];
				if (a.getItem_ID() == temp.getItem_ID())
				{
					possibleBatches[count][0] = i;
					possibleBatches[count][1] = j;
					possibleBatches[count][2] = k;
					totalVolume += temp.getVolume();
					count++;
				}
			}
		}
	}

	///write sort function outside the class
	///sort them by expiry date
	sort_arr(possibleBatches, count);

	if (totalVolume < quantity)
	{
		cout << "Total Volume of all batches is less than requested: " << totalVolume << endl;
		for (int i = 0; i < count; i++)
		{
			int section = possibleBatches[i][0], shelf = possibleBatches[i][1], batch = possibleBatches[i][2];
			Batch a = Sections[section].Shelves[shelf].batchList[batch];
			cout << a << endl;
		}

		///dialog that offers entering emptying the batches of item

		char answer[4], defaultt[4] = { "YES" };
		cout << "Type: YES if you want to take the remaining quantity, NO if you want to abondon the " << endl;
		cin.ignore();
		cin >> answer;
		if (strcmp(answer, defaultt))
		{
			quantity = totalVolume;
		}
		else
		{
			return false;
		}
	}

	for (int i = 0; i < count; i++)
	{
		int section = possibleBatches[i][0], shelf = possibleBatches[i][1], batch = possibleBatches[i][2];
		int volume = Sections[section].Shelves[shelf].batchList[batch].getVolume();
		if (volume >= quantity)
		{
			Sections[section].Shelves[shelf].batchList[batch].setVolume(volume - quantity);
			return true;
			///write to log file
		}
		else
		{
			quantity -= volume;
			Sections[section].Shelves[shelf].batchList[batch].setVolume(0);
			///write to log file
			///remove batch from warehouse
		}
	}
	return true;
}

void Warehouse::cleanUP(int day, int month, int year)
{
	///goes through all the batches and checks if something has expired with before that date
	///gets the ID of all expired batches and removes them from the warehouse
	for (int i = 0; i < batchCount; i++)
	{
		if (Batches[i].getExpiryYear() <= year)
		{
			if (Batches[i].getExpiryMonth() <= month)
			{
				if (Batches[i].getExpiryDay() <= day)
				{
					removeBatch(Batches[i].getBatch_ID());
					///write to file the bathes
				}
			}
		}
	}
}

void Warehouse::warehouseHistory(int fromDay, int fromMonth, int fromYear, int toDay, int toMonth, int toYear)
{
	///check validity of the dates
	///reads from log file all the changes and outputs them in the console
	/// read every batch and find the correct asking date
}

void Warehouse::currentSupply()
{
	///go around the warehouse and output the batches
	for (int i = 0; i < sectionCount; i++)
	{
		cout << "Section " << i << endl;
		int nb = Sections[i].shelfCount;
		for (int j = 0; j < nb; j++)
		{
			cout << "Shelf " << j << endl;
			int nb2 = Sections[i].Shelves[j].batches;
			for (int k = 0; k < nb2; k++)
			{
				cout << Sections[i].Shelves[j].batchList[k] << endl;
			}
		}
	}
}
