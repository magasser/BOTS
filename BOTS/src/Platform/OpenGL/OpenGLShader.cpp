#include "botspch.h"
#include "OpenGLShader.h"

#include "OpenGLCore.h"

struct ShaderProgramSource
{
	std::string VertexSource;
	std::string FragmentSource;
};

static ShaderProgramSource ParseShader(const std::filesystem::path& file)
{
	enum class ShaderType
	{
		None = -1,
		Vertex = 0,
		Fragment = 1
	};

	std::ifstream stream(file);

	std::string line;
	std::stringstream ss[2];

	ShaderType type = ShaderType::None;

	while (getline(stream, line))
	{
		if (line.find("#shader") != std::string::npos)
		{
			if (line.find("vertex") != std::string::npos)
			{
				type = ShaderType::Vertex;
			}
			else if (line.find("fragment") != std::string::npos)
			{
				type = ShaderType::Fragment;
			}

			continue;
		}

		ss[(int32_t)type] << line << '\n';
	}


	return {ss[(int32_t)ShaderType::Vertex].str(), ss[(int32_t)ShaderType::Fragment].str()};
}

static uint32_t CompileShader(uint32_t type, const std::string& source)
{
	const char* src = source.c_str();

	GLCall(uint32_t id = glCreateShader(type));
	GLCall(glShaderSource(id, 1, &src, nullptr));
	GLCall(glCompileShader(id));

	int32_t status;
	GLCall(glGetShaderiv(id, GL_COMPILE_STATUS, &status));

	if (status != GL_TRUE)
	{
		int32_t logLength;
		char message[1024];
		GLCall(glGetShaderInfoLog(id, 1024, &logLength, message));

		BOTS_ASSERT(false, "Failed to compile shader with message.");

		GLCall(glDeleteShader(id));
		return 0;
	}

	return id;
}

static uint32_t CreateShader(const std::string& vertexShader, const std::string& fragmentShader)
{
	GLCall(uint32_t programId = glCreateProgram());

	uint32_t vsId = CompileShader(GL_VERTEX_SHADER, vertexShader);
	uint32_t fsId = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

	GLCall(glAttachShader(programId, vsId));
	GLCall(glAttachShader(programId, fsId));
	GLCall(glLinkProgram(programId));
	GLCall(glValidateProgram(programId));

	GLCall(glDeleteShader(vsId));
	GLCall(glDeleteShader(fsId));

	return programId;
}

OpenGLShader::OpenGLShader(const std::filesystem::path& file)
{
	ShaderProgramSource source = ParseShader(file);

	m_RendererId = CreateShader(source.VertexSource, source.FragmentSource);
}

OpenGLShader::OpenGLShader(const std::string& vertexSource, const std::string& fragmentSource)
{
	m_RendererId = CreateShader(vertexSource, fragmentSource);
}

OpenGLShader::~OpenGLShader()
{
	GLCall(glDeleteProgram(m_RendererId));
}

void OpenGLShader::Bind() const
{
	GLCall(glUseProgram(m_RendererId));
}

void OpenGLShader::Unbind() const
{
	GLCall(glUseProgram(0));
}

void OpenGLShader::SetFloat4(const std::string& name, const glm::vec4& value)
{
	int32_t location = GetUniformLocation(name);

	if (location == -1)
	{
		BOTS_LOG_WARN("Tried to set uniform '{0}' which is not present in shader.", name);
		return;
	}

	GLCall(glUniform4f(location, value.x, value.y, value.z, value.w));
}

int32_t OpenGLShader::GetUniformLocation(const std::string& name)
{
	if (m_UniformLocationCache.find(name) != m_UniformLocationCache.end())
		return m_UniformLocationCache[name];

	GLCall(int32_t location = glGetUniformLocation(m_RendererId, name.c_str()));
	m_UniformLocationCache[name] = location;
	return location;

}
