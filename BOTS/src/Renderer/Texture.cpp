#include "botspch.h"
#include "Texture.h"

#include "RendererAPI.h"
#include "Platform/OpenGL/OpenGLTexture.h"

Shared<Texture2D> Texture2D::Create(const std::filesystem::path& path)
{
	switch (RendererAPI::GetAPI())
	{
	case RendererAPI::API::OpenGL: return MakeShared<OpenGLTexture2D>(path);
	}

	BOTS_ASSERT(false, "No supported renderer API.");
	return nullptr;
}
