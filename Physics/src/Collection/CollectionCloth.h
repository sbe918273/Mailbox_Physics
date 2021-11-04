#pragma once
#include "EntityCircle.h"
#include "EntitySpring.h"
#include <vector>

class CollectionCloth 
{
public:
	CollectionCloth(Vec2 pos, unsigned int xDim, unsigned int yDim, float naturalLength, float modElasticity, float radius);

	std::vector<EntityCircle> m_Circles;
	std::vector<EntitySpring> m_Springs;
};