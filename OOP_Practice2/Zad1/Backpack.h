#pragma once
#include "Book.h"
#include "ISBN.h"

class Backpack
{
    float maxWeight = 10;
	float currentWeight = 0;
	Book* books = nullptr;
	unsigned count = 0;
	unsigned cap = 0;

	void swap(Backpack& other);
	void copyDynamic(const Backpack& other);
	void free();
	void setCountAndCap(const unsigned count, const unsigned cap);
	void setWeightAndMaxWeight(const float weight, const float maxWeight);
	void resize();

public:

	Backpack() = default;
	Backpack(const Backpack& other);
	explicit Backpack(const float maxWeight);
	Backpack& operator=(const Backpack& other);
	~Backpack();

	void add(const Book& book);
	void remove(const ISBN& isbn);
	void serialize(const char* fileName) const;
	void deserialize(const char* fileName);

};