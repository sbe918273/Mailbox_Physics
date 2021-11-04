#include "PrimitiveLine.h"

PrimitiveLine::PrimitiveLine(Vec2 p_start, Vec2 p_end, Vec4 color)
	: color(color)
{
	start = p_start;
	end = p_end;
}
