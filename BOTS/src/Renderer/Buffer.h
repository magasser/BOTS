#pragma once

#include "Core.h"

enum class BufferDataType : uint32_t
{
	None = 0,
	Float = 1,
	Float2 = 2,
	Float3 = 3,
	Float4 = 4,
	Mat3 = 5,
	Mat4 = 6,
	Int = 7,
	Int2 = 8,
	Int3 = 9,
	Int4 = 10,
	UInt = 11,
	UInt2 = 12,
	UInt3 = 13,
	UInt4 = 14,
	Bool = 15
};

static uint32_t SizeOf(BufferDataType type)
{
	switch (type)
	{
	case BufferDataType::Float: return 4;
	case BufferDataType::Float2: return 2 * 4;
	case BufferDataType::Float3: return 3 * 4;
	case BufferDataType::Float4: return 4 * 4;
	case BufferDataType::Mat3: return 3 * 3 * 4;
	case BufferDataType::Mat4: return 4 * 3 * 4;
	case BufferDataType::Int: return 4;
	case BufferDataType::Int2: return 2 * 4;
	case BufferDataType::Int3: return 3 * 4;
	case BufferDataType::Int4: return 4 * 4;
	case BufferDataType::UInt: return 4;
	case BufferDataType::UInt2: return 2 * 4;
	case BufferDataType::UInt3: return 3 * 4;
	case BufferDataType::UInt4: return 4 * 4;
	case BufferDataType::Bool: return 1;
	}

	BOTS_ASSERT(false, "Unknown buffer data type.");
	return 0;
}

static uint32_t ComponentCountOf(BufferDataType type)
{
	switch (type)
	{
	case BufferDataType::Float: return 1;
	case BufferDataType::Float2: return 2;
	case BufferDataType::Float3: return 3;
	case BufferDataType::Float4: return 4;
	case BufferDataType::Mat3: return 3;
	case BufferDataType::Mat4: return 4;
	case BufferDataType::Int: return 1;
	case BufferDataType::Int2: return 2;
	case BufferDataType::Int3: return 3;
	case BufferDataType::Int4: return 4;
	case BufferDataType::UInt: return 1;
	case BufferDataType::UInt2: return 2;
	case BufferDataType::UInt3: return 3;
	case BufferDataType::UInt4: return 4;
	case BufferDataType::Bool: return 1;
	}

	BOTS_ASSERT(false, "Unknown buffer data type.");
	return 0;
}

struct BufferElement
{
	std::string Name;
	BufferDataType Type;
	uint32_t Size;
	uint32_t ComponentCount;
	size_t Offset;
	bool Normalized;

	BufferElement() = default;

	BufferElement(BufferDataType type, const std::string& name, bool normalized = false)
		: Type(type), Name(name), Size(SizeOf(type)), ComponentCount(ComponentCountOf(type)), Offset(0), Normalized(normalized) {}
};

class BufferLayout
{
public:
	BufferLayout() = default;

	BufferLayout(std::initializer_list<BufferElement> elements) : m_Elements(elements)
	{
		CalculateOffsetsAndStride();
	}

	inline uint32_t GetStride() const { return m_Stride; }

	inline const std::vector<BufferElement>& GetElements() const { return m_Elements; }

private:
	void CalculateOffsetsAndStride()
	{
		size_t offset = 0;
		m_Stride = 0;
		for (auto& element : m_Elements)
		{
			element.Offset = offset;
			offset += element.Size;
			m_Stride += element.Size;
		}
	}

protected:
	std::vector<BufferElement> m_Elements;
	uint32_t m_Stride;
};

class IndexBuffer
{
public:
	IndexBuffer(const uint32_t* data, uint32_t count) : m_Count(count) {}

	virtual ~IndexBuffer() = default;

	virtual void Bind() const = 0;
	virtual void Unbind() const = 0;

	inline uint32_t GetCount() const { return m_Count; }

	static Shared<IndexBuffer> Create(const uint32_t* data, uint32_t count);

protected:
	uint32_t m_Count;
};

class VertexBuffer
{
public:
	virtual ~VertexBuffer() = default;

	virtual const BufferLayout& GetLayout() const = 0;
	virtual void SetLayout(const BufferLayout& layout) = 0;

	virtual void Bind() const = 0;
	virtual void Unbind() const = 0;

	static Shared<VertexBuffer> Create(const void* data, uint32_t size);
};
