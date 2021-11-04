#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Renderer.h"
#include "Test.h"
#include "TestCloth.h"
#include "WindowData.h"

static void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{

    Test* currentTestPtr = static_cast<WindowData*>(glfwGetWindowUserPointer(window))->testControlPtr->m_CurrentTest;

    if (currentTestPtr == nullptr)
        return;

    if (button == GLFW_MOUSE_BUTTON_RIGHT)
    {
        if (action == GLFW_PRESS)
            currentTestPtr->OnRightClick(window);
        else
            currentTestPtr->OnRightRelease(window);
    }
     
    if (button == GLFW_MOUSE_BUTTON_LEFT)
    {
        if (action == GLFW_PRESS)
            currentTestPtr->OnLeftClick(window);
        else
            currentTestPtr->OnLeftRelease(window);
    }
}

static void cursorPosCallback(GLFWwindow* window, double posx, double posy)
{
    Test* currentTestPtr = static_cast<WindowData*>(glfwGetWindowUserPointer(window))->testControlPtr->m_CurrentTest;
     
    if (currentTestPtr == nullptr)
        return;

    currentTestPtr->OnCursorPos(window, posx, posy);
}

int main(void)
{
    GLFWwindow* window;

    if (!glfwInit())
        return -1;

    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(1440, 810, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    glfwSwapInterval(1);

    glewInit();

    {
        GLCall(glEnable(GL_BLEND));
        GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO(); (void)io;
        ImGui::StyleColorsDark();
        ImGui_ImplGlfw_InitForOpenGL(window, true);
        ImGui_ImplOpenGL3_Init((char*)glGetString(GL_NUM_SHADING_LANGUAGE_VERSIONS));
    }

    Renderer renderer;

    TestControl testControl = {renderer};
    testControl.RegisterTest<TestCloth>("Cloth");

    WindowData userData = { &testControl, nullptr };

    glfwSetWindowUserPointer(window, &userData);
    glfwSetMouseButtonCallback(window, mouseButtonCallback);

    glfwSetCursorPosCallback(window, cursorPosCallback);

     while (!glfwWindowShouldClose(window))
    {
        renderer.Clear();
        testControl.OnRender();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    return 0;
}