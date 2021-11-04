#include "EntityLine.h"

EntityLine::EntityLine(Vec2 p_start, Vec2 p_end, bool solid)
	: direction(p_end - p_start), solid(solid)
{
	start = p_start;
	end = p_end;
}