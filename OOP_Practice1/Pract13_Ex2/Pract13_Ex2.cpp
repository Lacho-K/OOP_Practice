#pragma warning (disable:4996)
#include <iostream>
#include "Relation.hpp"


int main()
{
	Relation<int> rel(2, 6, "is smaller than");
	rel.print();

}