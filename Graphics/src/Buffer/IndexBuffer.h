#pragma once

class IndexBuffer
{
public:
    IndexBuffer(const unsigned int* indices, unsigned int count, int mode);
    ~IndexBuffer();

    void Bind() const;
    void Unbind() const;

    inline unsigned int GetCount() const { return m_Count; }
    void SubData(const void* data, int offset, unsigned int count) const;
    void ClearData() const;

private:
    unsigned int m_RendererID;
    unsigned int m_Count;
};