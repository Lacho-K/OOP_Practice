#include "Backpack.h"
#include <cassert>
#include <iostream>

ISBN createISBN()
{
	unsigned short digits[13] = { 9,7,8,1,2,3,4,5,6,7,8,9,0 };
	return ISBN(digits, 13);
}


void testBookCreation()
{
	ISBN isbn = createISBN();
	Book b("Title", "Author", 2.5f, isbn);
	assert(b.getWeight() == 2.5f);
	assert(b.getISBN() == isbn);
}

void testBackpackAdd()
{
	Backpack bp(10.0f);
	Book b("Title", "Author", 3.0f, createISBN());
	bp.add(b);
}

void testBackpackCapacityResize()
{
	Backpack bp(50.0f);
	for (int i = 0; i < 10; i++)
	{
		Book b("Book", "Author", 1.0f, createISBN());
		bp.add(b);
	}
}

void testSerializeDeserialize()
{
	Backpack bp(15.0f);
	Book b("Book", "Author", 4.0f, createISBN());
	bp.add(b);
	bp.serialize("testfile.dat");

	Backpack newBp;
	newBp.deserialize("testfile.dat");

	newBp.add(Book("Another", "Author", 3.0f, createISBN()));
}

void testRemoveBook()
{
	ISBN isbn = createISBN();
	Backpack bp(10.0f);
	Book b("Book", "Author", 2.0f, isbn);
	bp.add(b);
	bp.remove(isbn);

	try
	{
		bp.remove(isbn);
		assert(false);
	}
	catch (const std::runtime_error&)
	{
	}
}



int main()
{
	testBookCreation();
	testBackpackAdd();
	testBackpackCapacityResize();
	testSerializeDeserialize();
	testRemoveBook();

	std::cout << "All tests passed\n";
}

