#include "UtilityCircle.h"

void EmplaceCircleVertices(float* const outVertex, const PrimitiveCircle& circle, const unsigned int countVertex)
{
	memcpy(outVertex, &circle.pos, 2 * sizeof(float));
	memcpy(outVertex + 2, &circle.color, 4 * sizeof(float));

	float x = circle.pos.x;
	float y = circle.pos.y;
	float radius = circle.radius;

	const float inc = 6.28 / countVertex;
	float t = 0.0f;

	unsigned int index = 6;

	for (int i = 0; i < countVertex; i++)
	{
		outVertex[index] = x + cosf(t) * radius;
		outVertex[index + 1] = y + sinf(t) * radius;
		memcpy(outVertex + index + 2, &circle.color, 4 * sizeof(float));

		t += inc;
		index += 6;
	}
}

void EmplaceCircleIndices(unsigned int* outIndex, int indexOffset, int countVertex)
{
	int bufferIndex = 0;
	int index = indexOffset + 1;

	for (int i = 0; i < countVertex; i++)
	{
		outIndex[bufferIndex] = index;
		outIndex[bufferIndex + 1] = indexOffset;
		outIndex[bufferIndex + 2] = (i == countVertex - 1) ? 1 + indexOffset : index + 1;

		bufferIndex += 3;
		index++;
	}
}