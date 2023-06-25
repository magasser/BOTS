#include "botspch.h"
#include "OpenGLRenderer2D.h"

#include "OpenGLCore.h"

void OpenGLRenderer2D::Draw(const Shared<VertexArray>& va, const Shared<IndexBuffer>& ib, const Shared<Shader>& shader) const
{
	shader->Bind();
	va->Bind();
	ib->Bind();

	GLCall(glDrawElements(GL_TRIANGLES, ib->GetCount(), GL_UNSIGNED_INT, nullptr));
}

void OpenGLRenderer2D::Clear(const glm::vec4& color) const
{
	GLCall(glClearColor(color.r, color.g, color.b, color.a));
	GLCall(glClear(GL_COLOR_BUFFER_BIT));
}
