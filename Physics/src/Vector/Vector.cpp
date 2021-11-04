 #include "Vector.h"
#include <iostream>

Vec2::Vec2()
	:x(0.0f), y(0.0f)
{}

Vec2::Vec2(float x, float y)
	: x(x), y(y)
{}

float Vec2::abs() const
{
	return sqrtf(powf(x, 2) + powf(y, 2));
}

Vec2 operator+(const Vec2& v1, const Vec2& v2)
{
	return (Vec2(v1.x + v2.x, v1.y + v2.y));
}

void operator+=(Vec2& v1, const Vec2& v2)
{
	v1 = v1 + v2;
}

Vec2 operator-(const Vec2& v1, const Vec2& v2)
{
	return (Vec2(v1.x - v2.x, v1.y - v2.y));
}

void operator-=(Vec2& v1, const Vec2& v2)
{
	v1 = v1 - v2;
}

Vec2 operator*(const float s, const Vec2& v)
{
	return (Vec2(v.x * s, v.y * s));
}

Vec2 operator*(const Vec2& v, const float s)
{
	return s * v;
}

void operator*=(Vec2& v, const float s)
{
	v = v * s;
}

Vec2 operator/(const Vec2& v, const float s)
{
	return (Vec2(v.x / s, v.y / s));
}

void operator/=(Vec2& v, const float s)
{
	v = v / s;
}

bool operator==(const Vec2& v1, const Vec2& v2)
{
	return (v1.x == v2.x && v2.y == v2.y);
}

bool operator!=(const Vec2& v1, const Vec2& v2)
{
	return (v1.x != v2.x || v1.y != v2.y);
}

float Dot(const Vec2& v1, const Vec2& v2)
{
	return (v1.x * v2.x + v1.y * v2.y);
}

Vec4::Vec4()
	: x(0.0f), y(0.0f), z(0.0f), w(0.0f)
{}

Vec4::Vec4(float x, float y, float z, float w)
	: x(x), y(y), z(z), w(w)
{}