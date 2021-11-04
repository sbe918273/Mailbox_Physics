#pragma once
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "GL/glew.h"

const unsigned int primitiveCount = 2;
const unsigned int maxVertexCount = 5000;
const unsigned int maxIndicesCount = 5000;

enum PrimitiveType
{
	//POINTS,
	LINES,
	//LINE_STRIP,
	//LINE_LOOP,
	TRIANGLES,
	//TRIANGLE_STRIP,
	//TRIANGLE_FAN,
	//QUADS,
	//QUAD_STRIP,
	//POLYGON
};


struct PrimitiveData
{
	VertexBuffer vb;
	IndexBuffer ib;
	VertexArray va;

	unsigned int vertexCount;
	unsigned int indexCount;

	PrimitiveData();
};
