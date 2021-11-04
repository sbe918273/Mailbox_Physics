#pragma once
#include "BaseCircle.h"
#include "vector.h"

class PrimitiveCircle : public BaseCircle
{
public:
	PrimitiveCircle(Vec2 pos, float radius, Vec4 color);
	Vec4 color;
};