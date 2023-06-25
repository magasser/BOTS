#include "botspch.h"
#include "OpenGLVertexArray.h"

#include "OpenGLCore.h"

static GLenum BufferDataTypeToGLenum(BufferDataType type)
{
	switch (type)
	{
	case BufferDataType::Float: return GL_FLOAT;
	case BufferDataType::Float2: return GL_FLOAT;
	case BufferDataType::Float3: return GL_FLOAT;
	case BufferDataType::Float4: return GL_FLOAT;
	case BufferDataType::Mat3: return GL_FLOAT;
	case BufferDataType::Mat4: return GL_FLOAT;
	case BufferDataType::Int: return GL_INT;
	case BufferDataType::Int2: return GL_INT;
	case BufferDataType::Int3: return GL_INT;
	case BufferDataType::Int4: return GL_INT;
	case BufferDataType::UInt: return GL_UNSIGNED_INT;
	case BufferDataType::UInt2: return GL_UNSIGNED_INT;
	case BufferDataType::UInt3: return GL_UNSIGNED_INT;
	case BufferDataType::UInt4: return GL_UNSIGNED_INT;
	case BufferDataType::Bool: return GL_BOOL;
	}

	BOTS_ASSERT(false, "Unkown buffer data type.");
	return 0;
}

OpenGLVertexArray::OpenGLVertexArray()
	: m_VertexBufferIndex(0)
{
	GLCall(glGenVertexArrays(1, &m_RendererId));
}

OpenGLVertexArray::~OpenGLVertexArray()
{
	GLCall(glDeleteVertexArrays(1, &m_RendererId));
}

void OpenGLVertexArray::Bind() const
{
	GLCall(glBindVertexArray(m_RendererId));
}

void OpenGLVertexArray::Unbind() const
{
	GLCall(glBindVertexArray(0));
}

void OpenGLVertexArray::AddVertexBuffer(const Shared<VertexBuffer>& buffer)
{
	BOTS_ASSERT(buffer->GetLayout().GetElements().size(), "Vertex buffer layout is empty.");

	Bind();
	buffer->Bind();

	const BufferLayout& layout = buffer->GetLayout();
	for (const auto& element : layout.GetElements())
	{
		switch (element.Type)
		{
		case BufferDataType::Float:
		case BufferDataType::Float2:
		case BufferDataType::Float3:
		case BufferDataType::Float4:
		{
			GLCall(glEnableVertexAttribArray(m_VertexBufferIndex));
			GLCall(glVertexAttribPointer(
				m_VertexBufferIndex,
				element.ComponentCount,
				BufferDataTypeToGLenum(element.Type),
				element.Normalized ? GL_TRUE : GL_FALSE,
				layout.GetStride(),
				(const void*)element.Offset));

			++m_VertexBufferIndex;
			break;
		}
		case BufferDataType::Mat3:
		case BufferDataType::Mat4:
		{
			uint8_t count = element.ComponentCount;
			for (uint8_t i = 0; i < count; ++i)
			{
				GLCall(glEnableVertexAttribArray(m_VertexBufferIndex));
				GLCall(glVertexAttribPointer(m_VertexBufferIndex,
					count,
					BufferDataTypeToGLenum(element.Type),
					element.Normalized ? GL_TRUE : GL_FALSE,
					layout.GetStride(),
					(const void*)(element.Offset + sizeof(float) * count * i)));

				GLCall(glVertexAttribDivisor(m_VertexBufferIndex, 1));

				++m_VertexBufferIndex;
			}
			break;
		}
		case BufferDataType::Int:
		case BufferDataType::Int2:
		case BufferDataType::Int3:
		case BufferDataType::Int4:
		case BufferDataType::UInt:
		case BufferDataType::UInt2:
		case BufferDataType::UInt3:
		case BufferDataType::UInt4:
		case BufferDataType::Bool:
		{
			GLCall(glEnableVertexAttribArray(m_VertexBufferIndex));
			GLCall(glVertexAttribIPointer(
				m_VertexBufferIndex,
				element.ComponentCount,
				BufferDataTypeToGLenum(element.Type),
				layout.GetStride(),
				(const void*)element.Offset));

			m_VertexBufferIndex++;
			break;
		}
		default:
		{
			BOTS_ASSERT(false, "Unknown buffer data type.");
			break;
		}
		}
	}

	m_VertexBuffers.push_back(buffer);
}

void OpenGLVertexArray::SetIndexBuffer(const Shared<IndexBuffer>& buffer)
{
	GLCall(glBindVertexArray(m_RendererId));

	buffer->Bind();

	m_IndexBuffer = buffer;
}
