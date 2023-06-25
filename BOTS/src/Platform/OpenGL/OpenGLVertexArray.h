#pragma once

#include "Renderer/VertexArray.h"

class OpenGLVertexArray : public VertexArray
{
public:
	OpenGLVertexArray();
	~OpenGLVertexArray() override;

	void Bind() const override;
	void Unbind() const override;

	void AddVertexBuffer(const Shared<VertexBuffer>& buffer) override;
	void SetIndexBuffer(const Shared<IndexBuffer>& buffer) override;

	const std::vector<Shared<VertexBuffer>>& GetVertexBuffers() const override { return m_VertexBuffers; }

	const Shared<IndexBuffer>& GetIndexBuffer() const override { return m_IndexBuffer; }

private:
	uint32_t m_RendererId;
	uint32_t m_VertexBufferIndex;
	std::vector<Shared<VertexBuffer>> m_VertexBuffers;
	Shared<IndexBuffer> m_IndexBuffer;
};
