#pragma once

#include "Renderer/Renderer2D.h"

class OpenGLRenderer2D : public Renderer2D
{
public:
	void Draw(const Shared<VertexArray>& va, const Shared<IndexBuffer>& ib, const Shared<Shader>& shader) const override;

	void Clear() const override;
};
