#pragma once

#include <GL/glew.h>
#include <iostream>
#include <cstdint>


// Insere GLClearError (que acha um erro) antes da função sendo analisada e chama GLLogCall (que apresenta o erro, função, pasta e linha) depois.
// #x é a função x.str(). __FILE__ é o arquivo que esta função está e __LINE__ a linha exata da função.

#define ASSERTING(x) if (!(x)) __debugbreak();
#define GLCall(x) GLClearError();\
    x;\
    ASSERTING(GLLogCall(#x, __FILE__, __LINE__))

void GLClearError();
bool GLLogCall(const char* function, const char* file, uint32_t line);

//  O renderer será responsável por desenhar qualquer coisa, quando darmos tudo que ele precisa.

//class Renderer
//{
//private:

//public:
// void Draw(const VertexArray & va, const IndexBuffer & ib, const Shader & sd) const;
//};