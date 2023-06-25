#include "botspch.h"
#include "OpenGLBuffer.h"

#include "OpenGLCore.h"

OpenGLIndexBuffer::OpenGLIndexBuffer(const uint32_t* data, uint32_t count)
	: IndexBuffer(data, count)
{
	GLCall(glGenBuffers(1, &m_RendererId));
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_RendererId));
	GLCall(glBufferData(GL_ARRAY_BUFFER, m_Count * sizeof(uint32_t), data, GL_STATIC_DRAW));
}

OpenGLIndexBuffer::~OpenGLIndexBuffer()
{
	GLCall(glDeleteBuffers(1, &m_RendererId));
}

void OpenGLIndexBuffer::Bind() const
{
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererId));
}

void OpenGLIndexBuffer::Unbind() const
{
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}

OpenGLVertexBuffer::OpenGLVertexBuffer(uint32_t size)
{
	GLCall(glGenBuffers(1, &m_RendererId));
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_RendererId));
	GLCall(glBufferData(GL_ARRAY_BUFFER, size, nullptr, GL_DYNAMIC_DRAW));
}

OpenGLVertexBuffer::OpenGLVertexBuffer(const void* data, uint32_t size)
{
	GLCall(glGenBuffers(1, &m_RendererId));
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_RendererId));
	GLCall(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
}

OpenGLVertexBuffer::~OpenGLVertexBuffer()
{
	GLCall(glDeleteBuffers(1, &m_RendererId));
}

void OpenGLVertexBuffer::Bind() const
{
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_RendererId));
}

void OpenGLVertexBuffer::Unbind() const
{
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
}