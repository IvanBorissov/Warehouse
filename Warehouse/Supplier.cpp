#include <iostream>
#include <cstring>
#include <fstream>
#include "Supplier.h"
using namespace std;

void Supplier::Copy(Supplier const& s)
{
	int sz;

	sz = strlen(s.name) + 1;
	this->name = new char[sz];
	strcpy_s(this->name, sz, s.name);

	this->ID_Supplier = s.ID_Supplier; 
}

void Supplier::Erase()
{
	delete[] name;
}

Supplier::Supplier()
{
	this->name = nullptr;
	this->ID_Supplier = -1;
}

Supplier::Supplier(int ID, char* s)
{
	int sz;
	
	sz = strlen(s) + 1;
	this->name = new char[sz];
	strcpy_s(this->name, sz, s);

	this->ID_Supplier = ID;
}

Supplier::Supplier(Supplier const&s)
{
	Copy(s);
}

Supplier& Supplier::operator=(const Supplier& s)
{
	if (this != &s)
	{
		Erase();
		Copy(s);
	}
	return *this;
}

Supplier::~Supplier()
{
	Erase();
}

int Supplier::getSupplier_ID()const
{
	return this->ID_Supplier;
}

char* Supplier::getSupplier_name()const
{
	return this->name;
}

void Supplier::setSupplier_name(char* newName)
{
	int sz;
	delete[] this->name;
	sz = strlen(newName) + 1;
	this->name = new char[sz];
	strcpy_s(this->name, sz, newName);
}

void Supplier::setSupplier_ID(int newID)
{
	this->ID_Supplier = newID;
}

bool Supplier::operator==(const Supplier& sup) const
{
	if (strcmp(this->name, sup.name)==0)return true;
	
	return false;
}

std::ostream& operator<<(std::ostream& os, const Supplier& supp)
{
	os << supp.ID_Supplier << ";" << supp.name << ";" << endl;
	return os;
}

std::istream& operator>>(std::istream& is, Supplier& supp)
{
	char name[256], comma;
	int ID;
	
	is >> ID;
	is >> comma;
	is.getline(name, 256, ';');

	Supplier a(ID, name);
	supp = a;

	return is;
}
