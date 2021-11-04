#include "IndexBuffer.h"
#include "UtilityGL.h"

IndexBuffer::IndexBuffer(const unsigned int* indices, unsigned int count, int mode)
    :
    m_Count(count)
{
    ASSERT(sizeof(unsigned int) == sizeof(GLuint));

    GLCall(glGenBuffers(1, &m_RendererID));
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID));
    GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), indices, mode));
}

IndexBuffer::~IndexBuffer()
{
    GLCall(glDeleteBuffers(1, &m_RendererID));
}

void IndexBuffer::Bind() const
{
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID));
}

void IndexBuffer::Unbind() const
{
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}

void IndexBuffer::SubData(const void* data, int offset, unsigned int size) const
{
    Bind();
    GLCall(glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, offset, size, data));
}

void IndexBuffer::ClearData() const
{
    Bind();
    GLCall(glClearBufferData(GL_ELEMENT_ARRAY_BUFFER, GL_R32UI, GL_RED, GL_UNSIGNED_INT, nullptr));
}
