#pragma once
class Issue
{
public:

	Issue() = default;
	Issue(char* title, double price, unsigned yearlyEditions);
	Issue(const Issue& other);
	Issue(Issue&& other);

	Issue& operator=(const Issue& other);
	Issue& operator=(Issue&& other);

	virtual Issue* clone() const = 0;

	virtual ~Issue();

	const char* getTitle() const;
	void setTitle(const char* title);

	double getPrice() const;
	void setPrice(double newPrice);

	unsigned getEditions() const;
	void setEditions(unsigned editions);

private:
	char* title = nullptr;
	double price = 0.0;
	unsigned yearlyEditions = 0;

	void free();
	void swap(Issue& other);
};