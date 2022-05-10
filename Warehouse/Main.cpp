#include <iostream>
#include <cstring>
#include <fstream>
#include "Item.h"
#include "Supplier.h"
#include "Batch.h"
#include "Shelf.h"
#include "Section.h"
#include "Warehouse.h"
using namespace std;

void printMenu()
{
	cout << endl;
	cout << "/---------------------------------------------------------" << endl;
	cout << endl;
	cout << "1. Warehouse invenory" << endl;
	cout << "2. Add Batch" << endl;
	cout << "3. Take from Warehouse" << endl;
	cout << "4. See History" << endl;
	cout << "5. Clear Warehouse" << endl;
	cout << "6. Save Warehouse to file" << endl;
	cout << "7. Load Warehouse from file" << endl;
	cout << "0. Exit" << endl;
	cout << endl;
	cout << "/---------------------------------------------------------" << endl;
	cout << endl;
}

void printInventory(Warehouse& warehouse)
{
	warehouse.currentSupply();
}

void addBatch(Warehouse& warehouse)
{
	char name[256], supplier[128], parameter[64];
	int volumeForOne, quantity, entryDay, entryMonth, entryYear, expiryDay, expiryMonth, expiryYear;

	cout << "Enter Item name" << endl;
	cin >> name;
	
	cout << "Enter Supplier name" << endl;
	cin >> supplier;
	
	cout << "Enter single Item's volume" << endl;
	cin >> volumeForOne;
	
	cout << "Enter quantity of the Batch" << endl;
	cin >> quantity;

	cout << "Enter the parameter of the Item (ex. Kg, Litres, pieces, etc)" << endl;
	cin >> parameter;

	cout << "Enter Batch's Day of entrance" << endl;
	cin >> entryDay;

	cout << "Enter Batch's Month of entrance" << endl;
	cin >> entryMonth;

	cout << "Enter Batch's Year of entrance" << endl;
	cin >> entryYear;

	cout << "Enter Batch's Day of expiration" << endl;
	cin >> expiryDay;

	cout << "Enter Batch's Month of expiration" << endl;
	cin >> expiryMonth;

	cout << "Enter Batch's Year of expiration" << endl;
	cin >> expiryYear;

	warehouse.addBatch(name, supplier, entryDay, entryMonth, entryYear, expiryDay, expiryMonth, expiryYear, volumeForOne, quantity, parameter);
}

void takeItem(Warehouse& warehouse)
{
	int quantity;
	char name[256];
	cout << "Enter Item's full entrance name (there might be items like Egg_sizeL, Egg_sizeM) specify fully" << endl;
	cin >> name;
	cout << "Enter how many Items you need from the warehouse" << endl;
	cin >> quantity;

	warehouse.takeFromWarehouse(name, quantity);
}

void printHistory(Warehouse& warehouse)
{
	int fromDay, fromMonth, fromYear, toDay, toMonth, toYear;

	cout << "Enter starting day of the Warehouse look up" << endl;
	cin >> fromDay;

	cout << "Enter staritng month of the Warehouse look up" << endl;
	cin >> fromMonth;

	cout << "Enter starting year of the Warehouse look up" << endl;
	cin >> fromYear;

	cout << "Enter final day of the Warehouse look up" << endl;
	cin >> toDay;

	cout << "Enter final month of the Warehouse look up" << endl;
	cin >> toMonth;

	cout << "Enter final year of the Warehouse look up" << endl;
	cin >> toYear;

	warehouse.warehouseHistory(fromDay, fromMonth, fromYear, toDay, toMonth, toYear);
}

void cleanWarehouse(Warehouse& warehouse)
{
	int expiryDay, expiryMonth, expiryYear;

	cout << "Enter Batch's Day of expiration" << endl;
	cin >> expiryDay;

	cout << "Enter Batch's Month of expiration" << endl;
	cin >> expiryMonth;

	cout << "Enter Batch's Year of expiration" << endl;
	cin >> expiryYear;

	warehouse.cleanUP(expiryDay, expiryMonth, expiryYear);
}

void saveWarehouse(Warehouse& warehouse)
{
	cout << "Enter file name in which the warehouse will be saved" << endl;
	///3 files
}

void loadWarehouse(Warehouse& warehouse)
{
	cout << "Enter the file name from which the warehouse will be loaded" << endl;
	///3 files
}

void warehouseInterface(Warehouse& warehouse)
{
	int command;
	do
	{
		printMenu();
		cin >> command;
		if (command < 0 || command>7)
		{
			cout << "Incorrect number!" << endl;
			cout << "Enter a number between 0 and 6" << endl;
			continue;
		}
		if (command == 1)
		{
			printInventory(warehouse);
		}
		if(command == 2)
		{
			addBatch(warehouse);
		}
		if (command == 3)
		{
			takeItem(warehouse);
		}
		if (command == 4)
		{
			printHistory(warehouse);
		}
		if (command == 5)
		{
			cleanWarehouse(warehouse);
		}
		if (command == 6)
		{
			saveWarehouse(warehouse);
		}
		if (command == 7)
		{
			loadWarehouse(warehouse);
		}

	} while (command != 0);
}

int main()
{
	Warehouse warehouse;

	warehouseInterface(warehouse);

	return 0;
}