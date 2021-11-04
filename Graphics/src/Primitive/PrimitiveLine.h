#pragma once
#include "BaseLine.h"
#include "vector.h"

class PrimitiveLine : public BaseLine
{
public:
	PrimitiveLine(Vec2 p_start, Vec2 p_end, Vec4 color);
	Vec4 color;
};