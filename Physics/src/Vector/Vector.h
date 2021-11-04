#pragma once
#include <math.h>

class Vec2
{
public:
	float x, y;

	Vec2();
	Vec2(float x, float y);
	float abs() const;
};

class Vec4
{
public:
	float x, y, z, w;

	Vec4();
	Vec4(float x, float y, float z, float w);
};

Vec2 operator+(const Vec2& v1, const Vec2& v2);
void operator+=(Vec2& v1, const Vec2& v2);

Vec2 operator-(const Vec2& v1, const Vec2& v2);
void operator-=(Vec2& v1, const Vec2& v2);

Vec2 operator*(const float s, const Vec2& v);
Vec2 operator*(const Vec2& v, const float s);
void operator*=(Vec2& v, const float s);

Vec2 operator/(const Vec2& v, const float s);
void operator/=(Vec2& v, const float s);

bool operator==(const Vec2& v1, const Vec2& v2);
bool operator!=(const Vec2& v1, const Vec2& v2);

float Dot(const Vec2& v1, const Vec2& v2);


