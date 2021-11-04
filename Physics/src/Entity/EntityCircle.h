#pragma once
#include "BaseCircle.h"
#include "EntityLine.h"

class EntityCircle : public BaseCircle
{
public:
	Vec2 vel;
	Vec2 acc;
	float mass;
	bool fixed;

	EntityCircle();
	EntityCircle(Vec2 pos, float radius, Vec2 vel, Vec2 acc, float mass, bool fixed);
	bool CollideCircle(EntityCircle& otherCircle, float coef);
	bool CollideLine(EntityLine& line, float coef);

private:
	static float ParaVelCircle(float m1, float v1, float m2, float v2, float coef);
	void PositionCircle(EntityCircle& otherCircle);
	bool CheckCircle(EntityCircle& otherCircle) const;

	void PositionLine(EntityLine& line, float coef);
};
