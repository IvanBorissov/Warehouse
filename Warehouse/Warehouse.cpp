#include <iostream>
#include <cstring>
#include <fstream>
#include <ctime>
#include "Item.h"
#include "Supplier.h"
#include "Batch.h"
#include "Shelf.h"
#include "Section.h"
#include "Warehouse.h"
#pragma warning(disable : 4996) //_CRT_SECURE_NO_WARNINGS
using namespace std;

void Warehouse::saveToLog(int iTypeOfOperation, long long timer, Batch batch, char* dt)
{
	/*ofstream log;
	log.open(logFile);
	cout << iTypeOfOperation << ";" << batch << dt << endl;
	log.close();
	*/
	ofstream os(logFile, ios::app);
	if (!os)
	{
		cout << "File not open!" << endl;
		return;
	}
	os << timer << ";" << iTypeOfOperation << ";" << batch << dt;
	os.close();
}

void Warehouse::sort_arr(int arr[2048][3], int n)
{
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
				//cout << "minava operaciqta" << endl;
				swap(arr[j], arr[j + 1]);
				//cout << "i swapa mina" << endl;
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

bool Warehouse::findPlace(Batch b)
{
	//cout << "pyrvi for" << endl;
	int sectionIdx=-1, shelfIdx=-1;
	///checks it there is a place on the same shelf near the same batch
	for (int i = 0; i < sectionCount; i++)
	{
		int nb = Sections[i].shelfCount;
		for (int j = 0; j < nb; j++)
		{
			int nb2 = Sections[i].Shelves[j].batches;
			for (int k = 0; k < nb2; k++)
			{
				Batch tempBatch = Sections[i].Shelves[j].batchList[k];
				if (b == tempBatch && b.getItem_ID() == tempBatch.getItem_ID())///???????? why batch ID
				{
					sectionIdx = i; shelfIdx = j;
					if (Sections[i].Shelves[j].volume - b.getVolume() >= 0)
					{
						int count = Sections[i].Shelves[j].batches++;
						Sections[i].Shelves[j].batchList[count] = b;
						Sections[i].Shelves[j].volume -= b.getVolume();
						cout << "found batch with the same expiration date" << endl;
						cout << "new batch in Section:" << i << " Shelf:" << j << " num of batch:" << count << endl;
						return true;
					}
				}
			}

		}
	}

	//cout << "vtori for" << endl;
	///There was no room for the batch on the same shelf
	int possiblePlace[2048][2], placeCounter=0;
	///going throgh the whole warehouse to find all the possible places for the batch
	for (int i = 0; i < sectionCount; i++)
		{
			//cout << "imame sekcii" << endl;
			int nb = Sections[i].shelfCount;
			for (int j = 0; j < nb; j++)
			{
				//cout << "Imame raftove" << endl;
				int nb2 = Sections[i].Shelves[j].batches;
				int volume = Sections[i].Shelves[j].volume;
				bool lamp = false;
				for (int k = 0; k < nb2; k++)
				{
					Batch a = Sections[i].Shelves[j].batchList[k];
					if (b != a && b.getItem_ID() == a.getItem_ID())
					{
						///we have the same item in the batch but with different expiration date
						///so that shelf is not valid for us to put our new batch
						///thus we no longer need to check the other items on the shelf
						//cout << "lelele" << endl;
						lamp = true;
						break;
					}
				}

				//cout << lamp << "lamp" << volume << " shelf volume " << b.getVolume()<< " batch volume" << endl;
				if (lamp == false && volume - b.getVolume() >= 0)
				{
					///we didn't see a batch with the same item but different expiration date
					///there's place on the shelf
					///we save the place in the array, so we can check with possible place meets the criteria best
					cout << i << " Possibe Section and shelf " << j << endl;
					cout << volume << " " << b.getVolume() << endl;
					possiblePlace[placeCounter][0] = i;
					possiblePlace[placeCounter][1] = j;
					placeCounter++;
				}

			}
		}

	if (placeCounter == 0)
	{
		///we didn't find a suitable place
		///that means that the warehouse is full and can't add that item
		cout << "No place for the current Batch. Warehouse full" << endl;
		return false;
	}
	
	int minSection = 150000, minShelf = 150000;
	if (sectionIdx != -1 && shelfIdx != -1)
	{
		///we've found a similiar Batch, so now we need to find the closest place
		///first by section, then by shelf
		cout << sectionIdx << " The place we need to be closest to " << shelfIdx << endl;
		for (int i = 0; i < placeCounter; i++)
		{
			cout << "Section" << possiblePlace[i][0] << " Shelf" << possiblePlace[i][1] << endl;
		}
		for (int i = 0; i < placeCounter; i++)
		{
			cout << minSection << " " << sectionIdx << " " << possiblePlace[i][0] << " " << possiblePlace[i][1] << endl;
			if (abs(minSection - sectionIdx) > abs(possiblePlace[i][0] - sectionIdx))
			{
				//cout << "tuk koga vlizame 1? "<<i<<" " << minSection << " " << minShelf << " " << possiblePlace[i][0] << possiblePlace[i][1] << endl;
				minSection = possiblePlace[i][0];
				minShelf = possiblePlace[i][1];
			}
			if (abs(minSection - sectionIdx) == abs(possiblePlace[i][0] - sectionIdx)
				&& abs(minShelf - shelfIdx) > abs(possiblePlace[i][1] - sectionIdx))
			{
				//cout << "tuk koga vlizame 2? "<<i<<" " << minSection << " " << minShelf << " " << possiblePlace[i][0] << possiblePlace[i][1] << endl;
				minSection = possiblePlace[i][0];
				minShelf = possiblePlace[i][1];
			}
		}
	}
	else
	{
		///there's now similiar batch in the warehouse
		///no limitations first possible place
		minSection = possiblePlace[0][0];
		minShelf = possiblePlace[0][1];
	}

	///adding batch to the warehouse in minSection, minShelf position
	int cnt = Sections[minSection].Shelves[minShelf].batches++;
	Sections[minSection].Shelves[minShelf].batchList[cnt] = b;
	cout << Sections[minSection].Shelves[minShelf].volume << " volume of shelf and new item " << b.getVolume() << endl;
	Sections[minSection].Shelves[minShelf].volume -= b.getVolume();
	cout << "new batch is in Section:" << minSection << " Shelf:" << minShelf << " num of batch:" << cnt << endl;

	return true;
}

void Warehouse::updateWarehouse(int section, int shelf, int batch, int newQty)
{
	///find batch on the shelf
	char defaultt[5] = { "null" };

	int tempID = Sections[section].Shelves[shelf].batchList[batch].getItem_ID();
	int prevVolume = Sections[section].Shelves[shelf].batchList[batch].getVolume();
	Item  tempItem = getItemBy_ID(tempID);

	cout << tempItem << endl;
	
	int newVolume = tempItem.getItem_volume() * newQty;
	cout << newVolume << " newVolume" << endl;

	Batch logBatch = Sections[section].Shelves[shelf].batchList[batch];
	int logQty = logBatch.getQuantity() - newQty;
	int logVolume = logQty * tempItem.getItem_volume();

	logBatch.setQuantity(logQty);
	logBatch.setVolume(logVolume);

	time_t timer;
	time(&timer);
	char* dt = ctime(&timer);

	saveToLog(1, timer, logBatch, dt);

	Sections[section].Shelves[shelf].batchList[batch].setQuantity(newQty);
	Sections[section].Shelves[shelf].batchList[batch].setVolume(newVolume);


	Sections[section].Shelves[shelf].volume += prevVolume - newVolume;

	cout << Sections[section].Shelves[shelf].batchList[batch].getVolume() << " new volume of the batch" << endl;

	if (Sections[section].Shelves[shelf].batchList[batch].getVolume() == 0)
	{
		Batch defaultBatch(-1, -1, -1, defaultt, -1, -1, defaultt);
		Sections[section].Shelves[shelf].batchList[batch] = defaultBatch;
	}

}

bool Warehouse::checkDate(char* date, long long fromDate, long long toDate)
{
	int sz = strlen(date);
	long long num=0;
	char comma;

	int i=0;
	while (i<sz)
	{
		num = num * 10 + int(date[i] - '0');
		i++;
	}
	
	if (fromDate <= num)
	{
		return true;
	}
	return false;
}

Item Warehouse::getItemBy_ID(int ID)
{
	char defaultt[5] = { "null" };
	for (int i = 0; i < itemCount; i++)
	{
		if (Items[i].getItem_ID() == ID)
		{
			return Items[i];
		}
	}
	return Item(-1,defaultt, -1, defaultt);
}

Item Warehouse::findItem(char* name)
{
	for (int i = 0; i < itemCount; i++)
	{
		//cout << name << " " << Items[i].getItem_name() << endl;
		if (strcmp(name, Items[i].getItem_name())==0)
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
	itemCount = batchCount = supplierCount = 0;
	newIDBatch = 1;
	for (int i = 0; i < 2048; i++)
	{
		Batches[i].setBatch_ID(-1);		
	}
	///-1 means that there are no batches any further

	/*loadItems();
	loadBatches();
	loadSuppliers();
	loadShelves();
	loadSections();*/
}

void Warehouse::addBatch(char* itemName, char* suppName,int entryDay, int entryMonth, int entryYear, int expiryDay, int expiryMonth, int expiryYear, int volumeForOne, int quantity, char* basicParameter)
{
	int ID_Item, ID_Supplier;
	
	///finding ID of the Item and supplier, or assigning new ones
	ID_Item = initItem(itemName, volumeForOne, basicParameter);
	ID_Supplier = initSupplier(suppName);

	char buff[20];
	time_t timer;
	time(&timer);
	strftime(buff, 20, "%Y-%m-%d", localtime(&timer));
	///write timer
	Batch tempBatch(newIDBatch, ID_Item, ID_Supplier, entryDay, entryMonth, entryYear, quantity, expiryDay, expiryMonth, expiryYear, volumeForOne);
	
	Batches[batchCount] = tempBatch;
	newIDBatch++;
	batchCount++;

	cout << itemName << " " << suppName << " " << basicParameter << endl;
	cout << tempBatch << endl;

	if (findPlace(tempBatch))
	{

		///timestamp of entrance
		time_t timer;
		time(&timer);
		//time_t now = time(0);
		char* dt = ctime(&timer);
		struct tm tm1;

		tm1.tm_year = entryYear - 1900;
		tm1.tm_mon = entryMonth - 1;
		tm1.tm_mday = entryDay;
		tm1.tm_hour = 0;
		tm1.tm_min = 0;
		tm1.tm_sec = 0;

		long long entryDate = mktime(&tm1);
		//cout << "pishem nova partida" << endl;
		saveToLog(0, entryDate, tempBatch, dt);
	}
}

bool Warehouse::takeFromWarehouse(char* name, int quantity)
{
	int possibleBatches[2000][3], count = 0, sumOfQuantities = 0;
	
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
					sumOfQuantities += temp.getQuantity();
					count++;
				}
			}
		}
	}
	cout << "imame partidi" << endl;

	///sort them by expiry date
	sort_arr(possibleBatches, count);

	/*
	for (int i = 0; i < count; i++)
	{
		int section = possibleBatches[i][0], shelf = possibleBatches[i][1], batch = possibleBatches[i][2];
		Batch a = Sections[section].Shelves[shelf].batchList[batch];
		cout << a << endl;
	}
	*/
	cout << "imame sortirani partidi" << endl;

	if (sumOfQuantities < quantity)
	{
		cout << "Total Quantity of all batches is less than requested: " << sumOfQuantities << endl;
		for (int i = 0; i < count; i++)
		{
			int section = possibleBatches[i][0], shelf = possibleBatches[i][1], batch = possibleBatches[i][2];
			Batch a = Sections[section].Shelves[shelf].batchList[batch];
			cout << a << endl;
		}

		///dialog that offers entering emptying the batches of item

		char answer[4], defaultt[4] = { "YES" };
		cout << "Type: YES if you want to take the remaining quantity, NO if you want to abondon the operation" << endl;
		cin >> answer;
		if (strcmp(answer, defaultt)==0)
		{
			quantity = sumOfQuantities;
		}
		else
		{
			return false;
		}
	}

	for (int i = 0; i < count; i++)
	{
		cout << "ehoooo" << endl;
		int section = possibleBatches[i][0], shelf = possibleBatches[i][1], batch = possibleBatches[i][2];
		int currQuantity = Sections[section].Shelves[shelf].batchList[batch].getQuantity();
		int currVolume = Sections[section].Shelves[shelf].batchList[batch].getVolume();
		cout << Sections[section].Shelves[shelf].batchList[batch] << "ni e partidata " << quantity << " ni e broikata" << endl;
		if (currQuantity >= quantity)
		{
			int newQty = currQuantity - quantity;

			updateWarehouse(section, shelf, batch, newQty);
			
			cout << "promenihme broikata" << endl;
			///time stamp of exit
			time_t now = time(0);
			char* dt = ctime(&now);
			cout << "vzehme vremeto" << endl;
			//saveToLog(1, Sections[section].Shelves[shelf].batchList[batch], dt);
			cout << "zapazihme vyv file" << endl;
			return true;
		}
		else
		{
			cout << "mahame tazi partida" << endl;
			quantity -= currQuantity;
			updateWarehouse(section, shelf, batch, 0);

			///time stamp of exit
			time_t now = time(0);
			char* dt = ctime(&now);
			//saveToLog(1, Sections[section].Shelves[shelf].batchList[batch], dt);
			cout << "zapazvame batcha" << endl;
		}
	}
	return true;
}

void Warehouse::cleanUP(int day, int month, int year)
{
	///goes through all the batches and checks if something has expired with before that date
	///gets the ID of all expired batches and removes them from the warehouse
	
	///write the correct file name
	char fileName[] = ("cleanup - yyyy-mm-dd.txt");
	ofstream os(fileName);
	//log.open(fileName);
	if (!os)
	{
		cout << "File problem" << endl;
		return;
	}

	for (int i = 0; i < sectionCount; i++)
	{
		int nb = Sections[i].shelfCount;
		for (int j = 0; j < nb; j++)
		{
			int nb2 = Sections[i].Shelves[j].batches;
			for (int k = 0; k < nb2; k++)
			{
				Batch tempBatch = Sections[i].Shelves[j].batchList[k];
				if (tempBatch.getExpiryYear() <= year)
				{
					if (tempBatch.getExpiryMonth() <= month)
					{
						if (tempBatch.getExpiryDay() <= day)
						{
							os << tempBatch << endl;
							updateWarehouse(i, j ,k ,0);
						}
					}
				}
			}

		}
	}
	os.close();
}

void Warehouse::warehouseHistory(int fromDay, int fromMonth, int fromYear, int toDay, int toMonth, int toYear)
{
	///check validity of the dates
	///reads from log file all the changes and outputs them in the console
	/// read every batch and find the correct asking date
	struct tm tm1, tm2;

	tm1.tm_year = fromYear - 1900;
	tm1.tm_mon = fromMonth - 1;
	tm1.tm_mday = fromDay;
	tm1.tm_hour = 0;
	tm1.tm_min = 0;
	tm1.tm_sec = 0;

	long long fromDate = mktime(&tm1);

	tm2.tm_year = toYear - 1900;
	tm2.tm_mon = toMonth - 1;
	tm2.tm_mday = toDay;
	tm2.tm_hour = 0;
	tm2.tm_min = 0;
	tm2.tm_sec = 0;

	long long toDate = mktime(&tm2);

	ifstream log(logFile);

	if (log.is_open())
	{
		char line[512];
		while (log.getline(line, 512))
		{
			char date[64];
			int i = 0;
			while (line[i] != ';')
			{
				date[i] = line[i];
				i++;
			}
			date[i] = '\0';

			if(checkDate(date, fromDate, toDate))///function for check

			cout << line << endl;
		}
	}

	log.close();
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

Warehouse::~Warehouse()
{
	/*saveItems();
	saveBatches();
	saveSuppliers();
	saveShelves();
	saveSections();*/
}
