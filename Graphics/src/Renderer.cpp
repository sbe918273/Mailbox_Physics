#include "Renderer.h"

Renderer::Renderer()
	: m_PrimitiveData {}, 
	m_Shader("src\\res\\shaders\\Batch.shader")
{
	m_Shader.Bind();
	m_Shader.SetUniformMat4f("u_MVP", glm::ortho(-2.0f, 2.0f, -1.0f, 1.0f, -1.0f, 1.0f));

	VertexBufferLayout layout;
	layout.Push<float>(2);
	layout.Push<float>(4);

	for (unsigned int i = 0; i < primitiveCount; i++)
	{
		PrimitiveData& data = m_PrimitiveData[i];
		data.va.AddBuffer(data.vb, layout);
	}

}

Renderer::~Renderer()
{
}

void Renderer::CheckEnd(PrimitiveType type)
{
	PrimitiveData& data = m_PrimitiveData[type];

	if (data.vertexCount >= maxVertexCount - 32 || data.indexCount >= maxIndicesCount - 96)
		Batch(type);
}

void Renderer::AddCircle(const PrimitiveCircle& circle)
{
	CheckEnd(PrimitiveType::TRIANGLES);
	PrimitiveData& triData = m_PrimitiveData[PrimitiveType::TRIANGLES];

	static const unsigned int verticesPerCircle = 32;

	static const unsigned int uintCount = 3 * verticesPerCircle;
	unsigned int indices[uintCount] = {};
	EmplaceCircleIndices(indices, triData.vertexCount, verticesPerCircle);
	triData.ib.SubData(indices, triData.indexCount * sizeof(unsigned int), uintCount * sizeof(unsigned int));
	triData.indexCount += uintCount;

	static const unsigned int floatCount = 6 * (verticesPerCircle + 1);
	float vertices[floatCount] = {};
	EmplaceCircleVertices(vertices, circle, verticesPerCircle);
	triData.vb.SubData(vertices, 6 * triData.vertexCount * sizeof(unsigned int), floatCount * sizeof(float));
	triData.vertexCount += verticesPerCircle + 1;
}

void Renderer::AddLine(const PrimitiveLine& line)
{
	CheckEnd(PrimitiveType::LINES);
	PrimitiveData& lineData = m_PrimitiveData[PrimitiveType::LINES];

	unsigned int indices[2] = {};
	EmplaceLineIndices(indices, lineData.indexCount);
	lineData.ib.SubData(indices, lineData.indexCount * sizeof(unsigned int), 2 * sizeof(unsigned int));
	lineData.indexCount += 2;

	float vertices[12] = {};
	EmplaceLineVertices(vertices, line);
	lineData.vb.SubData(vertices, 6 * lineData.vertexCount * sizeof(float), 6 * sizeof(float) * 2);
	lineData.vertexCount += 2;
}

void Renderer::Batch(PrimitiveType type)
{
	GLenum glType = GL_LINES;
	if (type == PrimitiveType::TRIANGLES)
		glType = GL_TRIANGLES;

	PrimitiveData& data = m_PrimitiveData[type];

	data.va.Bind();
	data.ib.Bind();
	
	GLCall(glDrawElements(glType, data.indexCount, GL_UNSIGNED_INT, nullptr));
	Reset(type);
}

void Renderer::Reset(PrimitiveType type)
{
	PrimitiveData& data = m_PrimitiveData[type];
	data.vertexCount = 0;
	data.indexCount = 0;
}

void Renderer::Clear()
{
	glClear(GL_COLOR_BUFFER_BIT);
}