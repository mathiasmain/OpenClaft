#pragma once
#include "GL/glew.h"
#include <cstdint>
#include <vector>
#include "VertexBuffer.h"
#include "Renderer.h"

struct VertexBufferElement
{
	uint32_t type;
	uint32_t count;
	uint8_t normalized;

	static uint32_t GetSizeOfType(uint32_t type)
	{
		switch (type)
		{
		case GL_FLOAT: return 4;
		case GL_UNSIGNED_INT: return 4;
		case GL_UNSIGNED_BYTE: return 1;
		}
		ASSERTING(false);
		return 0;
	}
};


class VertexArray
{
private:
	uint32_t m_RendererID;
	std::vector<VertexBufferElement> m_Elements;
	uint32_t						 m_Stride;

public:
	VertexArray();
	~VertexArray();

	template<typename T>
	void AddLayout(uint32_t count)
	{
		static_assert(false); // Usado para quando alguma variável com tipo que não implementei é inserida.
	}
	template<>
	void AddLayout<float>(uint32_t count)
	{
		m_Elements.push_back({ GL_FLOAT, count, GL_FALSE });
		m_Stride += count * VertexBufferElement::GetSizeOfType(GL_FLOAT);
	}
	template<>
	void AddLayout<uint32_t>(uint32_t count)
	{
		m_Elements.push_back({ GL_UNSIGNED_INT, count, GL_FALSE });
		m_Stride += count * VertexBufferElement::GetSizeOfType(GL_UNSIGNED_INT);
	}
	template<>
	void AddLayout<uint8_t>(uint32_t count)
	{
		m_Elements.push_back({ GL_UNSIGNED_BYTE, count, GL_TRUE });
		m_Stride += count * VertexBufferElement::GetSizeOfType(GL_UNSIGNED_BYTE);
	}
	inline const std::vector<VertexBufferElement> GetElements() const& { return m_Elements; }
	

	void Bind() const;
	void Unbind() const;
	void AddBufferAftervbBind(const VertexBuffer &vb);
};