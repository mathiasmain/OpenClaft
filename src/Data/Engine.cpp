
#include "Engine.h"

void Engine::Bind() const
{
}

void Engine::Unbind() const
{
}

void Engine::CookAddBuffer()
{
}

void Engine::CookShader()
{
}

void Engine::Clear() const
{
    glClear(GL_COLOR_BUFFER_BIT);
}
// Como já usamos usamos GL_ELEMENT_ARRAY_BUFFER para bound os índices (cubo), não colocar aqui.
void Engine::Draw(const VertexArray& vertexA, const IndexBuffer& indexB, const Shader& shader) const
{
    shader.Bind();
    vertexA.Bind();
    indexB.Bind();
    GLCall(glDrawElements(GL_TRIANGLES, indexB.GetCount(), GL_UNSIGNED_INT, nullptr));
}
