#include "CollectionCloth.h"

CollectionCloth::CollectionCloth(Vec2 pos, unsigned int xDim, unsigned int yDim, float naturalLength, float modElasticity, float radius)
	: m_Circles(), m_Springs()
{
	m_Circles.reserve(xDim * yDim);
	m_Springs.reserve(2 * xDim * yDim - xDim - yDim);

	unsigned int index = 0;

	for (int i = 0; i < yDim; i++)
	{
		Vec2 circlePos = pos - i * naturalLength * Vec2(0, 1);

		for (int j = 0; j < xDim; j++)
		{
			circlePos += naturalLength * Vec2(1, 0);
			
			m_Circles.emplace_back(
				circlePos,
				radius,
				Vec2{ 0.0f, 0.0f },
				Vec2{ 0.0f, 0.0f },
				1.0f,
				false
			);

			if (j != 0)
				m_Springs.emplace_back(naturalLength, modElasticity, m_Circles[index - 1], m_Circles[index]);

			if (i != 0)
				m_Springs.emplace_back(naturalLength, modElasticity, m_Circles[index - xDim], m_Circles[index]);

			index++;
		}
	}
}