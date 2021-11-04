#include "EntityCircle.h"

EntityCircle::EntityCircle()
	: vel(Vec2(0.0f, 0.0f)), acc(Vec2(0.0f, 0.0f)), mass(0.0f), fixed(true)
{
	pos = Vec2(0.0f, 0.0f);
	radius = 0.0f;
}

EntityCircle::EntityCircle(Vec2 p_pos, float p_radius, Vec2 vel, Vec2 acc, float mass, bool fixed)
	: vel(vel), acc(acc), mass(mass), fixed(fixed)
{
	pos = p_pos;
	radius = p_radius;
}

bool EntityCircle::CollideCircle(EntityCircle& otherCircle, float coef)
{
	Vec2 l = otherCircle.pos - pos;

	if (l.abs() > radius + otherCircle.radius)
		return false;

	PositionCircle(otherCircle);

	Vec2 n(-1 * l.y, l.x);

	Vec2 w1 = Vec2(Dot(vel, l), Dot(vel, n));
	Vec2 w2 = Vec2(Dot(otherCircle.vel, l), Dot(otherCircle.vel, n));

	l /= Dot(l, l);
	n /= Dot(n, n);

	if (!fixed)
	vel = ParaVelCircle(mass, w1.x, otherCircle.mass, w2.x, coef) * l + w1.y * n;

	if (!otherCircle.fixed)
		otherCircle.vel = ParaVelCircle(otherCircle.mass, w2.x, mass, w1.x, coef) * l + w2.y * n;

	return true;
}

float EntityCircle::ParaVelCircle(float m1, float v1, float m2, float v2, float coef)
{
	return ((m1 * v1 + m2 * v2 + coef * m1 * (v2 - v1)) / (m1 + m2));
}

void EntityCircle::PositionCircle(EntityCircle& otherCircle)
{
	Vec2 l = otherCircle.pos - pos;
	float lAbs = l.abs();
	l /= lAbs;

	float overlap = radius + otherCircle.radius - lAbs;

	if (fixed)
	{
		otherCircle.pos += overlap * l;
		return;
	}

	else if (otherCircle.fixed)
	{
		pos -= overlap * l;
		return;
	}

	pos -= 0.5f * overlap * l;
	otherCircle.pos += 0.5f * overlap * l;
}

bool EntityCircle::CheckCircle(EntityCircle& otherCircle) const
{
	return (pos - otherCircle.pos).abs() < radius + otherCircle.radius;
}

bool EntityCircle::CollideLine(EntityLine& line, float coef)
{
	Vec2 originLine = pos - line.start;
	Vec2 direction = line.end - line.start;

	float a = Dot(direction, direction);
	float half_b = Dot(originLine, direction);
	float c = Dot(originLine, originLine) - radius * radius;

	float discriminant = half_b * half_b - a * c;
	if (discriminant < 0)
		return false;

	float t = (half_b + sqrt(discriminant)) / a;
	if (t > 1)
	{
		t = (half_b - sqrt(discriminant)) / a;
		if (t > 1 || t < 0)
			return false;
	}

	else if (t < 0)
		return false;

	Vec2 contact = line.start + direction * (half_b / a);
	Vec2 n = pos - contact;
	float nLength = n.abs();
	float overlap = radius - nLength;

	pos += (overlap * n) / nLength;

	direction /= Dot(direction, direction);
	n /= Dot(n, n);

	vel = (-1 * n * (Dot(vel, n)) / Dot(n, n)) + direction * ((coef * Dot(vel, direction)) / Dot(direction, direction));

	return true;
}

void EntityCircle::PositionLine(EntityLine& line, float coef)
{
}