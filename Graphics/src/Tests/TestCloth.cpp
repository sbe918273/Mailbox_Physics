#include "TestCloth.h"
#include "CollisionCircle.h"
#include <iostream>

static unsigned int xDim = 15;
static unsigned int yDim = 15;

static WindowData* getWindowData(GLFWwindow* window)
{
    return static_cast<WindowData*>(glfwGetWindowUserPointer(window));
}

static void scaleMousePos(GLFWwindow* window, Vec2& mousePos)
{
    int width, height;
    glfwGetWindowSize(window, &width, &height);

    mousePos.x = -2.0f + 4.0f * mousePos.x / width;
    mousePos.y = 1.0f - 2.0f * mousePos.y / height;
}

static Vec2 getMousePos(GLFWwindow* window)
{
    double xMouse, yMouse;
    glfwGetCursorPos(window, &xMouse, &yMouse);
    Vec2 mousePos(xMouse, yMouse);
    scaleMousePos(window, mousePos);

    return mousePos;
}

static EntityCircle* getClickedCircle(GLFWwindow* window, std::vector<EntityCircle>& circles)
{

    Vec2 mousePos = getMousePos(window);

    for (EntityCircle& circle : circles)
    {
        if ((mousePos - circle.pos).abs() < circle.radius)
            return &circle;
    }

    return nullptr;
}

TestCloth::TestCloth(Renderer& renderer)
    : Test(renderer), m_Cloth(Vec2(-1.0f, 0.9f), yDim, xDim, 0.12f, 1.0f, 0.012f), m_Coef(0.2f), m_Damp(0.95f), topPos(-1.0f, 0.7f)
{
    m_Cloth.m_Circles[0].fixed = true;
    m_Cloth.m_Circles[xDim - 1].fixed = true;
}

TestCloth::~TestCloth() {}

void TestCloth::OnUpdate(float deltaTime) 
{

    std::vector<EntityCircle>& circles = m_Cloth.m_Circles;
    std::vector<EntitySpring>& springs = m_Cloth.m_Springs;

    for (EntityCircle& circle : circles)
    {
        circle.acc = Vec2(0.0f, -0.01f);
    }

    for (EntitySpring& spring : springs)
    {
        spring.UpdatePointAccs();
    }

    static EntityLine bottom(Vec2(-2.0f, -1.0f), Vec2(2.0f, -1.0f), true);
    static EntityLine top(Vec2(-2.0f, 1.0f), Vec2(2.0f, 1.0f), true);
    static EntityLine right(Vec2(2.0f, -1.0f), Vec2(2.0f, 1.0f), true);
    static EntityLine left(Vec2(-2.0f, -1.0f), Vec2(-2.0f, 1.0f), true);

    for (EntityCircle& circle : circles)
    {

        if (!circle.fixed)
        {
            circle.vel += circle.acc * deltaTime;
            circle.pos += circle.vel * deltaTime;


            circle.vel *= m_Damp;

            //circle.CollideLine(bottom, 1.0f);
            circle.CollideLine(top, 1.0f);
            circle.CollideLine(right, 1.0f);
            circle.CollideLine(left, 1.0f);
        }

        /*
        for (EntitySpring& spring : springs)
        {
            if (spring.m_Start.pos != circle.pos && spring.m_End.pos != circle.pos)
            {
                EntityLine springLine(spring.m_Start.pos, spring.m_End.pos, true);
                circle.CollideLine(springLine, m_Coef);
            }
        }
        */
    }

    //GroupAndResolveCollisions(m_Cloth.m_Circles, 5, 5, 4.0f, 2.0f, -2.0f, -1.0f, m_Coef);
}

void TestCloth::OnRender()
{

    std::vector<EntityCircle>& circles = m_Cloth.m_Circles;
    std::vector<EntitySpring>& springs = m_Cloth.m_Springs;

    unsigned int countCircles = circles.size();
    for (unsigned int i = 0; i < countCircles; i++)
    {
        m_Renderer.AddCircle(PrimitiveCircle(circles[i].pos, circles[i].radius, Vec4(1.0f, 1.0f, 1.0f, 1.0f)));
    }

    for (EntitySpring& spring : springs)
    {
        m_Renderer.AddLine(PrimitiveLine(spring.m_Start.pos, spring.m_End.pos, Vec4(1.0f, 1.0f, 1.0f, 1.0f)));
    }

    m_Renderer.Batch(PrimitiveType::TRIANGLES);
    m_Renderer.Batch(PrimitiveType::LINES);
    
}

void TestCloth::OnImGuiRender() 
{
    std::vector<EntityCircle>& circles = m_Cloth.m_Circles;

    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
    ImGui::SliderFloat("Coef", &m_Coef, 0.0f, 1.0f);
    ImGui::SliderFloat("Damp", &m_Damp, 0.0f, 1.0f);

    ImGui::SliderFloat2("Top Left", (float*)&circles[0].pos, -2.0f, 2.0f);
    if (ImGui::Button("Top Left Fixed")) { circles[0].fixed = !circles[0].fixed; }

    ImGui::SliderFloat2("Top Right", (float*)&circles[xDim - 1].pos, -2.0f, 2.0f);
    if (ImGui::Button("Top Right Fixed")) { circles[xDim - 1].fixed = !circles[xDim - 1].fixed; }

    ImGui::SliderFloat2("Bottom Left", (float*)&circles[yDim * (xDim - 1)].pos, -2.0f, 2.0f);
    if (ImGui::Button("Bottom Left Fixed")) { circles[yDim * (xDim - 1)].fixed = !circles[yDim * (xDim - 1)].fixed; }

    ImGui::SliderFloat2("Bottom Right", (float*)&circles[xDim * yDim - 1].pos, -2.0f, 2.0f);
    if (ImGui::Button("Bottom Right Fixed")) { circles[xDim * yDim - 1].fixed = !circles[xDim * yDim - 1].fixed; }
}

void TestCloth::OnRightClick(GLFWwindow* window)
{
    WindowData* dataPtr = getWindowData(window);
    EntityCircle* circlePtr = dataPtr->clickedCirclePtr;

    if (circlePtr != nullptr)
        dataPtr->clickedCircleFixed = !dataPtr->clickedCircleFixed;

    else
    {
        circlePtr = getClickedCircle(window, m_Cloth.m_Circles);
        if (circlePtr != nullptr)
            circlePtr->fixed = !(circlePtr->fixed);
    }
}

void TestCloth::OnRightRelease(GLFWwindow* window)
{}

void TestCloth::OnLeftClick(GLFWwindow* window)
{
    
    EntityCircle* circlePtr = getClickedCircle(window, m_Cloth.m_Circles);

    if (circlePtr != nullptr)
    {
        WindowData* dataPtr = getWindowData(window);
        dataPtr->clickedCirclePtr = circlePtr;
        dataPtr->clickedCircleFixed = circlePtr->fixed;
        circlePtr->fixed = true;
    }
}

void TestCloth::OnLeftRelease(GLFWwindow* window)
{
    WindowData* dataPtr = getWindowData(window);
    EntityCircle*& circlePtr = dataPtr->clickedCirclePtr;

    if (circlePtr != nullptr)
    {
        circlePtr->fixed = dataPtr->clickedCircleFixed;
        circlePtr = nullptr;
    }
}

void TestCloth::OnCursorPos(GLFWwindow* window, double xpos, double ypos)
{
    EntityCircle* circlePtr = getWindowData(window)->clickedCirclePtr;
    if (circlePtr != nullptr)
        circlePtr->pos = getMousePos(window);
}
