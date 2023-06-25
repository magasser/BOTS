#pragma once

#include "Renderer/Texture.h"

class OpenGLTexture2D : public Texture2D
{
public:
	OpenGLTexture2D(const std::filesystem::path& path);
	~OpenGLTexture2D() override;

	inline uint32_t GetWidth() const override { return m_Width; }
	inline uint32_t GetHeight() const override { return m_Height; }
	inline uint32_t GetRendererId() const override { return m_RendererId; }
	inline const std::filesystem::path& GetPath() const override { return m_Path; }

	void SetData(void* data, uint32_t size) override;

	void Bind(uint32_t slot) const override;
	void Unbind() const override;

private:
	std::filesystem::path m_Path;
	uint32_t m_RendererId;
	uint32_t m_Width, m_Height;	
};
