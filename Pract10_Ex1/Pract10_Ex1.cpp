#include <iostream>
#include "StudentArray.h"

int main()
{
	Student st("Gosheto", "Injenera", 2312);

	StudentArray sArr;

	// this throws an error
	sArr.pushBack(st);
}