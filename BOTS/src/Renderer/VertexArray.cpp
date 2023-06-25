#include "botspch.h"
#include "VertexArray.h"

#include "RendererAPI.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"

Shared<VertexArray> VertexArray::Create()
{
	switch (RendererAPI::GetAPI())
	{
	case RendererAPI::API::OpenGL: return MakeShared<OpenGLVertexArray>();
	}

	BOTS_ASSERT(false, "No supported renderer API.");
	return nullptr;
}
