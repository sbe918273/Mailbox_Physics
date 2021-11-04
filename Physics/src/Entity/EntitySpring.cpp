#pragma once
#include "EntitySpring.h"

EntitySpring::EntitySpring(float naturalLength, float elasticMod, EntityCircle& start, EntityCircle& end)
	: naturalLength(naturalLength), elasticMod(elasticMod), m_Start(start), m_End(end)
{}

void EntitySpring::UpdatePointAccs()
{
	Vec2 springLine = m_End.pos - m_Start.pos;
	float length = springLine.abs();
	float extension = springLine.abs() - naturalLength;

	Vec2 tension = (springLine * elasticMod * extension) / (naturalLength * length);

	if (!m_Start.fixed)
		m_Start.acc += tension / m_Start.mass;

	if (!m_End.fixed)

		m_End.acc -= tension / m_End.mass;
}