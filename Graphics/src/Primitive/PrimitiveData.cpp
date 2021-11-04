#include "PrimitiveData.h"

PrimitiveData::PrimitiveData()
	: vb(VertexBuffer(nullptr, 6 * sizeof(float) * maxVertexCount, GL_DYNAMIC_DRAW)),
	  ib(IndexBuffer(nullptr, maxIndicesCount, GL_DYNAMIC_DRAW)),
	  va({}),
	  vertexCount(maxVertexCount), 
	  indexCount(maxIndicesCount) {}