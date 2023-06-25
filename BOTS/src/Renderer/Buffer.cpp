#include "botspch.h"
#include "Buffer.h"

#include "RendererAPI.h"
#include "Platform/OpenGL/OpenGLBuffer.h"

Shared<IndexBuffer> IndexBuffer::Create(const uint32_t* data, uint32_t count)
{
	switch (RendererAPI::GetAPI())
	{
	case RendererAPI::API::OpenGL: return MakeShared<OpenGLIndexBuffer>(data, count);
	}

	BOTS_ASSERT(false, "No supported renderer API.");
	return nullptr;
}

Shared<VertexBuffer> VertexBuffer::Create(const void* data, uint32_t count)
{
	switch (RendererAPI::GetAPI())
	{
	case RendererAPI::API::OpenGL: return MakeShared<OpenGLVertexBuffer>(data, count);
	}

	BOTS_ASSERT(false, "No supported renderer API.");
	return nullptr;
}
