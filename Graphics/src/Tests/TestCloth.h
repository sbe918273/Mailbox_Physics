#pragma once
#include "Test.h"
#include "Renderer.h"
#include "CollectionCloth.h"
#include <vector>
#include "WindowData.h"

class TestCloth : public Test
{
public:
	TestCloth(Renderer& renderer);
	~TestCloth();

	void OnUpdate(float deltaTime) override;
	void OnRender() override;
	void OnImGuiRender() override;

	void OnRightClick(GLFWwindow* window) override;
	void OnLeftClick(GLFWwindow* window) override;
	virtual void OnRightRelease(GLFWwindow* window) override;
	virtual void OnLeftRelease(GLFWwindow* window) override;
	void OnCursorPos(GLFWwindow* window, double xpos, double ypos) override;

private:
	CollectionCloth m_Cloth;
	float m_Coef;
	float m_Damp;
	Vec2 topPos;
};