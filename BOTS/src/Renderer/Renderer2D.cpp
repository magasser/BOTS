#include "botspch.h"
#include "Renderer2D.h"

#include "RendererAPI.h"
#include "Platform/OpenGL/OpenGLRenderer2D.h"

Shared<Renderer2D> Renderer2D::Create()
{
	switch (RendererAPI::GetAPI())
	{
	case RendererAPI::API::OpenGL: return MakeShared<OpenGLRenderer2D>();
	}

	BOTS_ASSERT(false, "No supported renderer API.");
	return nullptr;
}
