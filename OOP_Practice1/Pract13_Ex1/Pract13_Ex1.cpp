// Pract13_Ex1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "Sorted.hpp"



int main()
{
    Sorted<int, 8> sorted1;
    sorted1.add(2);
    sorted1.add(1);
    sorted1.add(0);
    sorted1.print();

    Sorted<char, 10> sorted2;

    sorted2.add('a');
    sorted2.add('c');
    sorted2.add('b');
    sorted2.print();

}
