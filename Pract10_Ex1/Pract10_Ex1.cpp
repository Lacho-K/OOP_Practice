#include <iostream>
#include "StudentArray.h"

int main()
{
	Student st("Gosheto", "Injenera", 2312);

	Student st2(st);

	Student st3 = std::move(st2);

	st3.setName("Newname");
	st3.setName("Pesho");
	st3.setSpeciality("Cook");
	st3.setSpeciality("Cook2");
	st3.setFn(1122);

	std::cout << st3.getName() << std::endl;
	std::cout << st3.getSpeciality();

	StudentArray sArr;

	// this throws an error
	sArr.pushBack(st3);
	sArr.pushBack(st);

	Student front = sArr.getFront();
	Student back = sArr.getBack();
}