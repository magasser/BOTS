#include "botspch.h"
#include "TestClearColor.h"

#include <imgui.h>

TestClearColor::TestClearColor()
	: m_ClearColor({ 0.2f, 0.7f, 0.1f, 1.0f}), m_Renderer(MakeShared<Renderer2D>())
{
}

TestClearColor::~TestClearColor()
{
}

void TestClearColor::OnUpdate(float deltaTime)
{
}

void TestClearColor::OnRender()
{
	m_Renderer->Clear(m_ClearColor);
}

void TestClearColor::OnUIRender()
{
	ImGui::ColorEdit4("Clear color", &m_ClearColor);
}
