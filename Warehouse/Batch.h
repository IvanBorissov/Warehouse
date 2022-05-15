#ifndef _BATCH
#define _BATCH

class Batch
{
private:
	int ID_Batch;
	int ID_Item;
	int ID_Supplier;
	char dateOfExpiry[11];
	int expiryDay, expiryMonth, expiryYear;
	int quantity;
	int totalVolume;
	char dateOfEntry[11];
	int entryDay, entryMonth, entryYear;

	void Copy(Batch const&);
	bool setExpiryDate(int, int ,int);
	bool setEntryDate(int, int, int);
	void setExpiryFromChar(char*);
	void setEntryFromChar(char*);
	bool compareYears();

public:
	Batch();
	Batch(int, int, int, char*, int, int, char*);
	Batch(int, int, int, int, int, int, int, int, int, int, int);
	Batch(Batch const&);
	Batch& operator=(const Batch&);

	int getBatch_ID();
	int getItem_ID();
	int getSupplier_ID();
	int getQuantity();
	int getVolume();
	int getExpiryDay();
	int getExpiryMonth();
	int getExpiryYear();

	void setVolume(int);
	void setBatch_ID(int);
	void setQuantity(int);

	bool operator<(const Batch&) const;
	bool operator>(const Batch&) const;
	bool operator==(const Batch&) const;///compares if the expiry dates are the same
	bool operator!=(const Batch&) const;///compares if the whole batch is different


	friend std::ostream& operator<<(std::ostream& os, const Batch& batch);
	friend std::istream& operator>>(std::istream& is, Batch& batch);
};

#endif
