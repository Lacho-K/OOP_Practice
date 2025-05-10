#pragma once
#include "Set.h"
class EmtySet: public Set
{
public:
	bool member(int x) const override;
	Set* copy() override;
};
