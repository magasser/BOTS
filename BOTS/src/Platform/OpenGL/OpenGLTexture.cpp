#include "botspch.h"
#include "OpenGLTexture.h"

#include "OpenGLCore.h"

#include "Renderer/Image.h"

OpenGLTexture2D::OpenGLTexture2D(const std::filesystem::path& path)
	: m_Path(path), m_RendererId(0), m_Width(0), m_Height(0)
{
	Image::FlipVerticallyOnLoad(true);

	uint32_t channels;
	void* data = Image::Load(m_Path.string().c_str(), &m_Width, &m_Height, &channels, 4);

	GLCall(glGenTextures(1, &m_RendererId));
	GLCall(glBindTexture(GL_TEXTURE_2D, m_RendererId));

	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));

	GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data));
	GLCall(glBindTexture(GL_TEXTURE_2D, 0));

	if (data)
		Image::Free(data);

}

OpenGLTexture2D::~OpenGLTexture2D()
{
	GLCall(glDeleteTextures(1, &m_RendererId));
}

void OpenGLTexture2D::SetData(void* data, uint32_t size) {}

void OpenGLTexture2D::Bind(uint32_t slot) const
{
	GLCall(glActiveTexture(GL_TEXTURE0 + slot));
	GLCall(glBindTexture(GL_TEXTURE_2D, m_RendererId));
}

void OpenGLTexture2D::Unbind() const
{
	GLCall(glBindTexture(GL_TEXTURE_2D, 0));
}
