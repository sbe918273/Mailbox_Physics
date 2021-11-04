#pragma once
#include "BaseLine.h"

class EntityLine : public BaseLine
{
public:
	EntityLine(Vec2 start, Vec2 end, bool solid);
	Vec2 direction;
	bool solid;
};
