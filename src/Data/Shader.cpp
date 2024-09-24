#include "Shader.h"


Shader::Shader()
    : m_RendererID(0)
{// Se o programa final for executado fora do VS, o caminho relativo é relativo ao executável. Mas quando estamos no modo debug do VS, o caminho é relativo à solução.
    ShaderProgramSource source = ParseShader("./src/resources/shaders/Cube.shader");
    m_RendererID = CreateShader(source.VertexSource, source.FragmentSource);
     
}

Shader::~Shader()
{
    GLCall(glDeleteProgram(m_RendererID));
}

void Shader::Bind() const
{
    GLCall(glUseProgram(m_RendererID));
}

void Shader::Unbind() const
{
    GLCall(glUseProgram(0));
}
void Shader::SetUniformMat4f(const std::string& name, glm::mat4 &matrix)
{
    GLCall(glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, &matrix[0][0]));
}

void Shader::SetUniform1i(const std::string& name, uint32_t v)
{
    assert(v == 0 &&"O valor de v não é 0!\n");
    assert(!name.empty() &&"Deveria ser u_Texture, mas está vazio");

    GLCall(glUniform1i(GetUniformLocation(name), v));
}

void Shader::SetUniform1f(const std::string& name, float v)
{
    assert(v == 0 && "O valor de v não é 0!\n");
    assert(!name.empty() && "Deveria ser u_Texture, mas está vazio");

    GLCall(glUniform1f(GetUniformLocation(name), v));
}

void Shader::SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3)
{
    GLCall(glUniform4f(GetUniformLocation(name), v0, v1, v2, v3));
}

int32_t Shader::GetUniformLocation(const std::string& name)
{
    if (m_UniformLocationCached.find(name) != m_UniformLocationCached.end())
    {
        return m_UniformLocationCached[name];
    }
    assert(m_RendererID != 0);

    GLCall(int32_t location = glGetUniformLocation(m_RendererID, name.c_str()));
    //assert(location != -1);
    m_UniformLocationCached[name] = location;
    return location;
}

ShaderProgramSource Shader::ParseShader(const std::string& filepath)
{
    enum class ShaderType {
        NONE = -1, VERTEX = 0, FRAGMENT = 1
    };

    // TODO: Usar stdio para acessar pastas, pois é mais rápido que o fstream do C++.
    std::ifstream stream(filepath); // Abre o arquivo.

    std::string line;
    std::stringstream ss[2];
    ShaderType type = ShaderType::NONE;
    while (getline(stream, line))
    {
        if (line.find("#shader") != std::string::npos)
        {
            if (line.find("vertex") != std::string::npos)
            {
                type = ShaderType::VERTEX;
            }
            else if (line.find("fragment") != std::string::npos)
            {
                type = ShaderType::FRAGMENT;
            }
        }
        else// if (type != ShaderType::NONE)
        {
            ss[(int)type] << line << '\n';
        }
    }
    return { ss[0].str(), ss[1].str() };
}

uint32_t Shader::CompileShader(uint32_t type, const std::string& source)
{
    // TODO: Assert source is not NULL, blob or "".
    uint32_t id = glCreateShader(type);
    const char* src = &source[0];

    // id do shader, count source codes, início do array?, e comprimento.
    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);

    // TODO: Error handling
    int32_t result;
    GLCall(glGetShaderiv(id, GL_COMPILE_STATUS, &result));
    if (!result)
    {
        int32_t length;
        GLCall(glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length));
        char* message = (char*)alloca(length * sizeof(char));
        GLCall(glGetShaderInfoLog(id, length, &length, message));

        std::cout << "Failed to compile " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << " shader!\n";
        std::cout << message << "\n";

        GLCall(glDeleteShader(id));
        return 0;
    }

    return id;
}

uint32_t Shader::CreateShader(const std::string& vertexShader, const std::string& fragmentShader)
{
    GLCall(uint32_t program = glCreateProgram());
    GLCall(uint32_t vertex = CompileShader(GL_VERTEX_SHADER, vertexShader));
    GLCall(uint32_t fragment = CompileShader(GL_FRAGMENT_SHADER, fragmentShader));

    //assert(vertex > 0 && "Whoops, we failed to create the vertex shader!");
    //assert(fragment > 0 && "Whoops, we failed to create the fragment shader!");

    GLCall(glAttachShader(program, vertex));
    GLCall(glAttachShader(program, fragment));
    GLCall(glLinkProgram(program));
    GLCall(glValidateProgram(program));

    GLCall(glDeleteShader(vertex));
    GLCall(glDeleteShader(fragment));

    return program;
}

