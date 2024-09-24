#pragma once

#include <GL/glew.h>
#include <iostream>
#include <cstdint>


// Insere GLClearError (que acha um erro) antes da fun��o sendo analisada e chama GLLogCall (que apresenta o erro, fun��o, pasta e linha) depois.
// #x � a fun��o x.str(). __FILE__ � o arquivo que esta fun��o est� e __LINE__ a linha exata da fun��o.

#define ASSERTING(x) if (!(x)) __debugbreak();
#define GLCall(x) GLClearError();\
    x;\
    ASSERTING(GLLogCall(#x, __FILE__, __LINE__))

void GLClearError();
bool GLLogCall(const char* function, const char* file, uint32_t line);

//  O renderer ser� respons�vel por desenhar qualquer coisa, quando darmos tudo que ele precisa.

//class Renderer
//{
//private:

//public:
// void Draw(const VertexArray & va, const IndexBuffer & ib, const Shader & sd) const;
//};