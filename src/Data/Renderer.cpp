#include "Renderer.h"

void GLClearError()
{
    while (glGetError() != GL_NO_ERROR); // Mesma coisa que !glGetError()
}

bool GLLogCall(const char* function, const char* file, uint32_t line)
{
    while (GLenum error = glGetError())
    {
        std::cout << "[OpenGL Error] ( " << error << " )\n" << "Function: " << function << "\nFile: " << file << "\nLine: " << line << "\n";
        return false;
    }
    return true;
}

//void Renderer::Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& sd) const
//{

//}
