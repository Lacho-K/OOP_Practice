#pragma once
#include "Soldier.h"

class Sergeant :public Soldier
{
	char* platoonDesc = nullptr;
	Soldier* platoon = nullptr;

public:
	Sergeant() = default;
	Sergeant(const char* plattonDesc, Soldier* platoon);
	Sergeant(const Sergeant& other);
	Sergeant(Sergeant&& other);

	Sergeant& operator=(const Sergeant& other);
	Sergeant& operator=(Sergeant&& other);


};