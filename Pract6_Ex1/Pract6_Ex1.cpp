#include <iostream>
#include <fstream>
#include "Stock.h"

int main()
{
	unsigned nums[12] = { 1,2,3,4,5,6,7,8,9,10,11,12 };
	Stock tets("goj", "koorororo", nums);


	std::cout << tets.isProfitable();
}