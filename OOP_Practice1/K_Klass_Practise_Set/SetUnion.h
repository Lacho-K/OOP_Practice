#pragma once
#include "Set.h"
class SetUnion : public Set
{
	Set* sets[2];

public:
	SetUnion();
	SetUnion(Set* set1, Set* set2);
	bool member(int x) const override;

};