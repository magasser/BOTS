#pragma once

#include "Core.h"

class Texture
{
public:
	virtual ~Texture() = default;

	virtual uint32_t GetWidth() const = 0;
	virtual uint32_t GetHeight() const = 0;
	virtual uint32_t GetRendererId() const = 0;
	virtual const std::filesystem::path& GetPath() const = 0;

	virtual void SetData(void* data, uint32_t size) = 0;

	virtual void Bind(uint32_t slot) const = 0;
	virtual void Unbind() const = 0;
};

class Texture2D : public Texture
{
public:
	static Shared<Texture2D> Create(const std::filesystem::path& path);
};
