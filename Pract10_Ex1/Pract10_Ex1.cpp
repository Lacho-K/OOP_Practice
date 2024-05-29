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

	Student st4("Gosheto", "Injenera", 2312);

	StudentArray sArr;

	sArr.pushBack(st3);
	sArr.pushBack(st3);
	sArr.pushFront(std::move(st));
	sArr.pushFront(st4);

	Student front = sArr.getFront();
	//Student back = sArr.getBack();

	Student at = sArr.at(0);
	Student at1 = sArr.at(1);
	Student at2 = sArr.at(2);
	Student at3 = sArr.at(3);
}