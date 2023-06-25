#include "botspch.h"
#include "Shader.h"

#include "RendererAPI.h"
#include "Platform/OpenGL/OpenGLShader.h"

Shared<Shader> Shader::Create(const std::filesystem::path& file)
{
	BOTS_ASSERT(std::filesystem::exists(file), "Shader source file does not exists.");

	switch (RendererAPI::GetAPI())
	{
	case RendererAPI::API::OpenGL: return MakeShared<OpenGLShader>(file);
	}

	BOTS_ASSERT(false, "No supported renderer API.");
	return nullptr;
}

Shared<Shader> Shader::Create(const std::string& vertexSource, const std::string& fragmentSource)
{
	BOTS_ASSERT(vertexSource.empty(), "Vertex shader source is empty.");
	BOTS_ASSERT(fragmentSource.empty(), "Fragment shader source is empty.");

	switch (RendererAPI::GetAPI())
	{
	case RendererAPI::API::OpenGL: return MakeShared<OpenGLShader>(vertexSource, fragmentSource);
	}

	BOTS_ASSERT(false, "No supported renderer API.");
	return nullptr;
}
