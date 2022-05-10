#ifndef _ITEM
#define _ITEM

class Item
{
private:
	int ID_Item;
	char* name;
	int volumeForOne;
	char* basicParameter;

	void Copy(const Item&);
	void Erase();
public:
	Item();
	Item(int, char*, int, char*);
	Item(Item const&);
	Item& operator= (const Item&);
	~Item();

	int getItem_ID()const;
	int getItem_volume()const;
	char* getItem_name()const;
	char* getItem_parameter()const;

	void setItem_ID(int);
	void setItem_name(char*);
	void setItem_volume(int);
	void setItem_parameter(char*);

	bool operator==(const Item&) const;

	void saveToFile(const char*);
	void readFromFile(char*);

	friend std::ostream& operator<<(std::ostream& os, const Item& item);
	friend std::istream& operator>>(std::istream& is, Item& item);
};

#endif
