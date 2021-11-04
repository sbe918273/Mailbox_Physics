#include "CollisionCircle.h"

void GroupAndResolveCollisions(std::vector<EntityCircle>& circles, unsigned int xDim, unsigned int yDim, float w, float h, float xOrigin, float yOrigin, float coef)
{
	const unsigned int circleCount = circles.size();
	unsigned int squaresCount = xDim * yDim;

	const float xGrid = w / xDim;
	const float yGrid = h / yDim;

	std::unique_ptr<std::vector<unsigned int>[]> gridSquares = std::make_unique<std::vector<unsigned int>[]>(squaresCount);

	for (int i = 0; i < circleCount; i++)
	{
		float codedRadius = circles[i].radius / xGrid;

		float codedX = (circles[i].pos.x - xOrigin) / xGrid;
		unsigned int lowerX = std::max(0, (int)floorf(codedX - codedRadius));
		unsigned int upperX = std::min(xDim, (unsigned int)ceilf(codedX + codedRadius));

		float codedY = (circles[i].pos.y - yOrigin) / yGrid;
		unsigned int lowerY = std::max(0, (int)floorf(codedY - codedRadius));
		unsigned int upperY = std::min(yDim, (unsigned int)ceilf(codedY + codedRadius));

		for (int y = lowerY; y < upperY; y++)
		{
			unsigned int squareIndex = y * xDim + lowerX;
			for (int x = lowerX; x < upperX; x++)
			{
				for (unsigned int j : gridSquares[squareIndex])
				{
					circles[i].CollideCircle(circles[j], coef);
				}

				gridSquares[squareIndex].push_back(i);
				squareIndex++;
			}
		}
	}
}
