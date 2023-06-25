#pragma once

#include "Renderer/Buffer.h"

class OpenGLIndexBuffer : public IndexBuffer
{
public:
	OpenGLIndexBuffer(const uint32_t* data, uint32_t count);
	~OpenGLIndexBuffer() override;

	void Bind() const override;
	void Unbind() const override;

private:
	uint32_t m_RendererId;
};

class OpenGLVertexBuffer : public VertexBuffer
{
public:
	OpenGLVertexBuffer(uint32_t size);
	OpenGLVertexBuffer(const void* data, uint32_t size);
	~OpenGLVertexBuffer() override;

	const BufferLayout& GetLayout() const override { return m_Layout; }
	void SetLayout(const BufferLayout& layout) override { m_Layout = layout; }

	void Bind() const override;
	void Unbind() const override;

private:
	uint32_t m_RendererId;
	BufferLayout m_Layout;
};
