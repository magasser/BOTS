#pragma once

#include "Test.h"
#include "Renderer/Renderer2D.h"

class TestClearColor : public Test
{
public:
	TestClearColor();
	~TestClearColor() override;

	void OnUpdate(float deltaTime) override;
	void OnRender() override;
	void OnUIRender() override;

private:
	Shared<Renderer2D> m_Renderer;
	glm::vec4 m_ClearColor;
};
