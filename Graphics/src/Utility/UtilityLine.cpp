#include "UtilityLine.h"
#include <string.h>

void EmplaceLineIndices(unsigned int* const outIndex, const unsigned int offsetIndex)
{
	outIndex[0] = offsetIndex;
	outIndex[1] = offsetIndex + 1;
}

void EmplaceLineVertices(float* const outVertex, const PrimitiveLine& line)
{
	memcpy(outVertex, &line.start, 2 * sizeof(float));
	memcpy(outVertex + 2, &line.color, 4 * sizeof(float));
	memcpy(outVertex + 6, &line.end, 2 * sizeof(float));
	memcpy(outVertex + 8, &line.color, 4 * sizeof(float));
}