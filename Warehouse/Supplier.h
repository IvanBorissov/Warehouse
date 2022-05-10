#ifndef _SUPPLIER
#define _SUPPLIER

class Supplier
{
private:
	int ID_Supplier;
	char* name;

	void Copy(Supplier const&);
	void Erase();
public:
	Supplier();
	Supplier(int, char*);
	Supplier(Supplier const&);
	Supplier& operator=(const Supplier&);
	~Supplier();

	int getSupplier_ID()const;
	char* getSupplier_name()const;

	void setSupplier_name(char*);
	void setSupplier_ID(int);

	bool operator==(const Supplier&) const;

	friend std::ostream& operator<<(std::ostream& os, const Supplier& supp);
	friend std::istream& operator>>(std::istream& is, Supplier& supp);
};

#endif

