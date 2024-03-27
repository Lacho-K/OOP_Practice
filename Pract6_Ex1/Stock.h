#pragma once
class Stock
{
	char abbreviation[6] = "unint";
	char name[21] = "unknown";
	unsigned prices[12]{ 0 };
	void copy(const Stock& other);

public:
	const char* getAbbreviation() const;
	const char* getName() const;
	const unsigned* getPrices() const;

	void setAbbreviation(const char* abbreviation);
	void setName(const char* name);
	void setPrices(unsigned* prices);

	Stock() = default;
	Stock(const char* abbreviation, const char* name, unsigned* prices);
	Stock(const Stock& other);
	//Stock& operator=(const Stock& other);

	~Stock() = default;
};
