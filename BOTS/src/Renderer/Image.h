#pragma once

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

class Image
{
public:
	static void FlipVerticallyOnLoad(bool enabled)
	{
		stbi_set_flip_vertically_on_load(enabled ? 1 : 0);
	}

	static void* Load(const char* path, uint32_t* width, uint32_t* height, uint32_t* channels, uint32_t desiredChannels)
	{
		return stbi_load(path, (int*)width, (int*)height, (int*)channels, desiredChannels);
	}

	static void Free(void* data)
	{
		stbi_image_free(data);
	}
};
