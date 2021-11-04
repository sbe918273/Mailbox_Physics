#include "Test.h"

Test::Test(Renderer& renderer)
	: m_Renderer(renderer)
{}

TestControl::TestControl(Renderer& renderer)
	: Test(renderer), m_CurrentTest(nullptr)
{}

void TestControl::OnRender()
{

	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
	ImGui::Begin("Test");

	if (m_CurrentTest)
	{
		m_CurrentTest->OnUpdate(0.166f);
		m_CurrentTest->OnRender();
		m_CurrentTest->OnImGuiRender();

		if (ImGui::Button("<-"))
		{
			delete m_CurrentTest;
			m_CurrentTest = nullptr;
		}
	}

	else 
	{
		for (auto& test : m_Tests)
		{
			if (ImGui::Button(test.first.c_str()))
				m_CurrentTest = test.second();
		}
	}

	ImGui::End();
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

