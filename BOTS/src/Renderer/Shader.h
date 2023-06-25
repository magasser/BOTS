#pragma once

#include "Core.h"

class Shader
{
public:
	virtual ~Shader() = default;

	virtual void Bind() const = 0;
	virtual void Unbind() const = 0;

	virtual void SetFloat4(const std::string& name, const glm::vec4& value) = 0;

	static Shared<Shader> Create(const std::filesystem::path& file);
	static Shared<Shader> Create(const std::string& vertexSource, const std::string& fragmentSource);
};
