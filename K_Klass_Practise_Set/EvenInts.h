#pragma once
#include "Set.h"
class EvenInts : public Set
{
	bool member(int x) const override;
	Set* copy() override;
};