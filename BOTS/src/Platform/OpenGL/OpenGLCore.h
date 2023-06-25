#pragma once

#include <glad/glad.h>

#include "Core.h"

#ifdef BOTS_DEBUG
#define GLCall(func) GLClearError();\
	func;\
	BOTS_ASSERT(GLLogError(#func, __FILE__, __LINE__), "OpenGL Error")

static void GLClearError()
{
	while (glGetError() != GL_NO_ERROR);
}

static std::string GetName(uint32_t error)
{
	switch (error)
	{
	case GL_INVALID_ENUM: return BOTS_STRINGIFY(GL_INVALID_ENUM);
	case GL_INVALID_VALUE: return BOTS_STRINGIFY(GL_INVALID_VALUE);
	case GL_INVALID_OPERATION: return BOTS_STRINGIFY(GL_INVALID_OPERATION);
	case GL_INVALID_FRAMEBUFFER_OPERATION: return BOTS_STRINGIFY(GL_INVALID_FRAMEBUFFER_OPERATION);
	case GL_OUT_OF_MEMORY: return BOTS_STRINGIFY(GL_OUT_OF_MEMORY);
	case GL_STACK_UNDERFLOW: return BOTS_STRINGIFY(GL_STACK_UNDERFLOW);
	case GL_STACK_OVERFLOW: return BOTS_STRINGIFY(GL_STACK_OVERFLOW);
	default: return "UNKOWN";
	}
}

static bool GLLogError(const char* function, const char* file, int32_t line)
{
	while (uint32_t error = glGetError())
	{
		std::string name = GetName(error);
		BOTS_LOG_ERROR("[OpenGL Error] '{0} ({1})' in '{2}' at {3}:{4}.", name, error, function, file, line);
		return false;
	}

	return true;
}
#else
#define GLCall(func) (func)
#endif
