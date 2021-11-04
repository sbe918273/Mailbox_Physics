#pragma once
#include "PrimitiveCircle.h"
#include <vector>

void EmplaceCircleVertices(float* const outVertex, const PrimitiveCircle& circle, const unsigned int countVertex);
void EmplaceCircleIndices(unsigned int* outIndex, int indexOffset, int countVertex);