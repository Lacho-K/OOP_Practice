#pragma once
#include "Set.h"
class Singleton: public Set
{
	int element = 0;
public:

	Singleton() = default;
	Singleton(int elem);
	bool member(int x) const override;
	Set* copy(const Set)

};