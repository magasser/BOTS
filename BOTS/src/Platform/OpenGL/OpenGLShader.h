#pragma once

#include <unordered_map>

#include "Renderer/Shader.h"

class OpenGLShader : public Shader
{
public:
	OpenGLShader(const std::filesystem::path& file);
	OpenGLShader(const std::string& vertexSource, const std::string& fragmentSource);
	~OpenGLShader() override;

	void Bind() const override;
	void Unbind() const override;

	void SetFloat(const std::string& name, float value) override;
	void SetFloat4(const std::string& name, const glm::vec4& value) override;

	void SetMat4(const std::string& name, const glm::mat4& value) override;

	void SetInt(const std::string& name, uint32_t value) override;

private:
	int32_t GetUniformLocation(const std::string& name);

private:
	uint32_t m_RendererId;
	std::unordered_map<std::string, int32_t> m_UniformLocationCache;
};
