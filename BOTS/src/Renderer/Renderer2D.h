#pragma once

#include "Core.h"
#include "Shader.h"
#include "Buffer.h"
#include "VertexArray.h"

class Renderer2D
{
public:
	virtual void Clear(const glm::vec4& color) const = 0;

	virtual void Draw(const Shared<VertexArray>& va, const Shared<IndexBuffer>& ib, const Shared<Shader>& shader) const = 0;

	static Shared<Renderer2D> Create();
};
