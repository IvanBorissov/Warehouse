#include <iostream>
#include <cstring>
#include "Item.h"
#include "Supplier.h"
#include "Batch.h"
using namespace std;

void Batch::Copy(Batch const& b)
{
	this->ID_Item = b.ID_Item;
	this->ID_Supplier = b.ID_Supplier;
	this->ID_Batch = b.ID_Batch;

	this->entryDay = b.entryDay;
	this->entryMonth = b.entryMonth;
	this->entryYear = b.entryYear;
	for (int i = 0; i < 11; i++)
	{
		this->dateOfEntry[i] = b.dateOfEntry[i];
	}

	this->expiryDay = b.expiryDay;
	this->expiryMonth = b.entryMonth;
	this->expiryYear = b.entryYear;
	for (int i = 0; i < 11; i++)
	{
		this->dateOfExpiry[i] = b.dateOfExpiry[i];
	}

	this->quantity = b.quantity;
	this->totalVolume = b.totalVolume;
}

bool Batch::setExpiryDate(int day, int month, int year)
{
	///cheking validity of the date
	if (1000 <= year <= 3000)
	{
		if ((month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12) && !(day >= 1 && day <= 31))
		{
			cout << "Not a valid expiry date" << endl; return false;
		}
		else
			if (month == 4 || month == 6 || month == 9 || month == 11 && !(day >= 1 && day <= 30))
			{
				cout << "Not a valid expiry date" << endl; return false;
			}
			else
				if (month == 2)
				{
					if ((year % 400 == 0 || (year % 100 != 0 && year % 4 == 0)) && !(day >= 1 && day <= 29))
					{
						cout << "Not a valid expiry date" << endl; return false;
					}
					else if (!(day >= 1 && day <= 28))
					{
						cout << "Not a valid expiry date" << endl; return false;
					}
				}
	}
	this->expiryDay = day;
	this->expiryMonth = month;
	this->expiryYear = year;

	this->dateOfExpiry[2] = this->dateOfExpiry[5] = '.';

	cout << "day1" << endl;
	///setting day
	if (day < 10)
	{
		this->dateOfExpiry[0] = '0';
	}
	else
	{
		this->dateOfExpiry[0] = char((day / 10) + '0');
	}
	this->dateOfExpiry[1] = char((day % 10) + '0');

	cout << "month1" << endl;
	///setting month
	if (month < 10)
	{
		this->dateOfExpiry[3] = '0';
	}
	else
	{
		this->dateOfExpiry[3] = char((month / 10) + '0');
	}
	this->dateOfExpiry[4] = char((month % 10) + '0');

	cout << "year1" << endl;
	///setting year
	int idx = 9;
	while (year != 0)
	{
		this->dateOfExpiry[idx] = char((year % 10) + '0');
		year /= 10;
		idx--;
	}
	this->dateOfExpiry[10] = '\0';

	return true;
}

bool Batch::setEntryDate(int day, int month, int year)
{
	///cheking validity of the date
	if (1000 <= year <= 3000)
	{
		if ((month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12) && !(day >= 1 && day <= 31))
		{
			cout << "Not a valid entry date" << endl; return false;
		}
		else
			if (month == 4 || month == 6 || month == 9 || month == 11 && !(day >= 1 && day <= 30))
			{
				cout << "Not a valid entry date" << endl; return false;
			}
			else
				if (month == 2)
				{
					if ((year % 400 == 0 || (year % 100 != 0 && year % 4 == 0)) && !(day >= 1 && day <= 29))
					{
						cout << "Not a valid entry date" << endl; return false;
					}
					else if (!(day >= 1 && day <= 28))
					{
						cout << "Not a valid entry date" << endl; return false;
					}
				}
	}
	this->entryDay = day;
	this->entryMonth = month;
	this->entryYear = year;

	this->dateOfEntry[2] = this->dateOfEntry[5] = '.';

	cout << "day" << endl;
	///setting day
	if (day < 10)
	{
		this->dateOfEntry[0] = '0';
	}
	else
	{
		this->dateOfEntry[0] = char((day / 10) + '0');
	}
	this->dateOfEntry[1] = char((day % 10) + '0');

	cout << "month" << endl;
	///setting month
	if (month < 10)
	{
		this->dateOfEntry[3] = '0';
	}
	else
	{
		this->dateOfEntry[3] = char((month / 10) + '0');
	}
	this->dateOfEntry[4] = char((month % 10) + '0');

	cout << "year" << endl;
	///setting year
	int idx = 9;
	while (year != 0)
	{
		this->dateOfEntry[idx] = char((year % 10) + '0');
		year /= 10;
		idx--;
	}
	this->dateOfEntry[10] = '\0';

	return true;
}

bool Batch::compareYears()
{
	if (this->entryYear > this->expiryYear)return false;
	if (this->entryYear == this->expiryYear && this->entryMonth > this->expiryMonth)return false;
	if (this->entryYear == this->expiryYear && this->entryMonth == this->expiryMonth && this->entryDay > this->expiryDay)return false;

	return true;
}

Batch::Batch()
{
	this->ID_Batch = -1;
	this->ID_Item = -1;
	this->ID_Supplier = -1;
	this->quantity = -1;
	this->totalVolume = -1;
}

Batch::Batch(Batch const&b)
{
	Copy(b);
}

Batch::Batch(int ID_Batch, int ID_Item, int ID_Supplier, int entryDay, int entryMonth, int entryYear, int quantity, int expiryDay, int expiryMonth, int expiryYear, int volumeForOne)
{
	this->ID_Batch = ID_Batch;
	this->ID_Item = ID_Item;
	this->ID_Supplier = ID_Supplier;
	this->quantity = quantity;
	this->totalVolume = quantity * volumeForOne;

	cout << "eho" << endl;
	setExpiryDate(expiryDay, expiryMonth, expiryYear);
	setEntryDate(entryDay, entryMonth, entryYear);
	if (compareYears()==false)
	{
		cout << "expiryDate before entryDate" << endl;
	}
	///write batch to file
}

Batch& Batch::operator=(const Batch&b)
{
	Copy(b);
	return *this;
}

int Batch::getBatch_ID()
{
	return this->ID_Batch;
}

int Batch::getItem_ID()
{
	return this->ID_Item;
}

int Batch::getSupplier_ID()
{
	return this->ID_Supplier;
}

int Batch::getQuantity()
{
	return this->quantity;
}

int Batch::getVolume()
{
	return this->totalVolume;
}

int Batch::getExpiryDay()
{
	return this->expiryDay;
}

int Batch::getExpiryMonth()
{
	return this->expiryMonth;
}

int Batch::getExpiryYear()
{
	return this->expiryYear;
}

void Batch::setVolume(int qnty)
{
	this->totalVolume -= qnty;
}

void Batch::printBatch()
{
	cout << this->ID_Batch << " " << this->ID_Item << " " << this->ID_Supplier << endl;
	cout << this->dateOfEntry << endl;
	cout << this->dateOfExpiry << endl;
}
