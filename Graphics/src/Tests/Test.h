#pragma once
#include "functional"
#include <vector>
#include <string>
#include <iostream>
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"
#include "Renderer.h"
#include <GLFW/glfw3.h>

class Test
{
public:
	Test(Renderer& renderer);
	virtual ~Test() {}

	virtual void OnUpdate(float deltaTime) {};
	virtual void OnRender() {};
	virtual void OnImGuiRender() {};

	virtual void OnRightClick(GLFWwindow* window) {};
	virtual void OnLeftClick(GLFWwindow* window) {};
	virtual void OnRightRelease(GLFWwindow* window) {};
	virtual void OnLeftRelease(GLFWwindow* window) {}

	virtual void OnCursorPos(GLFWwindow* window, double xpos, double ypos) {};

protected:
	Renderer& m_Renderer;
};

class TestControl : public Test
{
public:
	TestControl(Renderer& renderer);

	void OnRender() override;

	template<typename T>
	void RegisterTest(const std::string& name)
	{
		std::cout << "Registering test " << name << std::endl;
		m_Tests.push_back(std::make_pair(name, [this]() { return new T(m_Renderer); }));
	}

	Test* m_CurrentTest;

private:
	std::vector<std::pair<std::string, std::function<Test* ()>>> m_Tests;
};
