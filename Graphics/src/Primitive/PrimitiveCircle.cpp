#include "PrimitiveCircle.h"

PrimitiveCircle::PrimitiveCircle(Vec2 p_pos, float p_radius, Vec4 color)
	: color(color)
{
	pos = p_pos;
	radius = p_radius;
}
