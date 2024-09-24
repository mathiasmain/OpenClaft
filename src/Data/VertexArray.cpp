#include "VertexArray.h"
#include <cassert>

VertexArray::VertexArray()
{
	this->m_Stride = 0;
	GLCall(glGenVertexArrays(1, &m_RendererID));
	assert(m_RendererID != 0 && "A cria��o do VertexArrayObject n�o foi bem sucedida.\n");
}

VertexArray::~VertexArray()
{
	GLCall(glDeleteVertexArrays(1, &m_RendererID));
}

void VertexArray::Bind() const
{
	GLCall(glBindVertexArray(m_RendererID));

}

void VertexArray::Unbind() const
{
	GLCall(glBindVertexArray(0));

}

void VertexArray::AddBufferAftervbBind(const VertexBuffer& vb)
{
	Bind();
	vb.Bind();
	uint32_t offset = 0;
	for (size_t i = 0; i < m_Elements.size(); i++)
	{
		GLCall(glEnableVertexAttribArray(i));
		GLCall(glVertexAttribPointer(i, m_Elements[i].count, m_Elements[i].type, m_Elements[i].normalized, m_Stride, (const void*)offset));
		offset += m_Elements[i].count * VertexBufferElement::GetSizeOfType(m_Elements[i].type);

	}
	// O primeiro atributo est� no index 0.
		// Tamanho: quantos floats representam um v�rtice? 2!. 2 para cada ponto.
		// Tipo, se quer que seja normalizado e n�mero de bytes entre cada v�rtice.
		// Offset para o pr�ximo atributo (antes do pr�ximo v�rtice). ex: 2 floats - (const void*) 8
		//glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);
}
