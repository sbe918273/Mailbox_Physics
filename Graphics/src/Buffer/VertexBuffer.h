#pragma once

class VertexBuffer
{
private:
	unsigned int m_RendererID;
public:
	VertexBuffer(const void* data, unsigned int size, int mode);
	~VertexBuffer();

	void SubData(const void* data, int offset, unsigned int size) const;

	void Bind() const;
	void Unbind() const;
};