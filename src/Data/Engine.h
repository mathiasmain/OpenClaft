#pragma once
#include "Renderer.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "Shader.h"

class Engine
{
private:

public:


	void Bind() const;
	void Unbind() const;

	void CookAddBuffer();
	void CookShader();


	void Clear() const;
	void Draw(const VertexArray & vertA, const IndexBuffer &indexB, const Shader &shader) const;


	 

};