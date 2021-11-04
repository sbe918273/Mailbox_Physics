#pragma once
#include "EntityCircle.h"

class EntitySpring
{
public:
	float naturalLength;
	float elasticMod;

	EntityCircle& m_Start;
	EntityCircle& m_End;

	EntitySpring(float naturalLength, float elasticMod, EntityCircle& start, EntityCircle& end);
	void UpdatePointAccs();
};
