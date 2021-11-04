#pragma once
#include <array>
#include "PrimitiveCircle.h"
#include "PrimitiveLine.h"
#include "PrimitiveData.h"
#include "VertexBufferLayout.h"
#include "UtilityGL.h"
#include "UtilityCircle.h"
#include "UtilityLine.h"
#include "Shader.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

class Renderer
{
private:
    //std::array<PrimitiveData, 10> 
    PrimitiveData m_PrimitiveData[2];
    Shader m_Shader;

public:

    Renderer();
    ~Renderer();

    void CheckEnd(PrimitiveType);

    void AddCircle(const PrimitiveCircle& circle);
    void AddLine(const PrimitiveLine& line);

    void Batch(PrimitiveType type);
    void Reset(PrimitiveType type);
    void Clear();
};