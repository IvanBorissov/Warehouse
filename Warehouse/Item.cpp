#include <iostream>
#include <cstring>
#include "Item.h"

using namespace std;

void Item::Copy(const Item& s)
{
	int sz;

	sz = strlen(s.name) + 1;
	this->name = new char[sz];
	strcpy_s(this->name, sz, s.name);

	sz = strlen(s.basicParameter) + 1;
	this->basicParameter = new char[sz];
	strcpy_s(this->basicParameter, sz, s.basicParameter);

	this->volumeForOne = s.volumeForOne;
	this->ID_Item = s.ID_Item;
}

void Item::Erase()
{
	delete[] name;
	delete[] basicParameter;
}

Item::Item()
{
	this->name = nullptr;
	this->basicParameter = nullptr;
	this->ID_Item = -1;
	this->volumeForOne = -1;
}

Item::Item(int ID, char* name, int volume, char* parameter)
{
	int sz;

	sz = strlen(name) + 1;
	this->name = new char[sz];
	strcpy_s(this->name, sz, name);

	sz = strlen(parameter) + 1;
	this->basicParameter = new char[sz];
	strcpy_s(this->basicParameter, sz, parameter);

	this->volumeForOne = volume;
	this->ID_Item = ID;
}

Item::Item(Item const& s)
{
	Copy(s);
}

Item& Item::operator=(const Item& s)
{
	if (this != &s)
	{
		Erase();
		Copy(s);
	}

	return *this;
}

Item::~Item()
{
	Erase();
}

int Item::getItem_ID()const
{
	return this->ID_Item;
}

int Item::getItem_volume()const
{
	return this->volumeForOne;
}

char* Item::getItem_name()const
{
	return this->name;
}

char* Item::getItem_parameter()const
{
	return this->basicParameter;
}

void Item::setItem_ID(int newID)
{
	this->ID_Item = newID;
}

void Item::setItem_name(char* newName)
{
	int sz;
	delete[] this->name;
	sz = strlen(newName) + 1;
	this->name = new char[sz];
	strcpy_s(this->name, sz, newName);
}

void Item::setItem_volume(int newVolume)
{
	this->volumeForOne = newVolume;
}

void Item::setItem_parameter(char* newParameter)
{
	int sz;
	delete[] this->basicParameter;
	sz = strlen(newParameter) + 1;
	this->basicParameter = new char[sz];
	strcpy_s(this->basicParameter, sz, newParameter);
}