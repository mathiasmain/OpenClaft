#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>
#include <cassert>
#include <fstream>
#include <sstream>
#include <cstdint>
#include "./Data/Renderer.h"
#include "./Data/VertexBuffer.h"
#include "./Data/IndexBuffer.h"
#include "./Data/VertexArray.h"
#include "./Data/Shader.h"
#include "./Data/Engine.h"
#include "./Data/Texture.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"



int main(void)
{
    //ASSERTING(sizeof(uint32_t) == sizeof(GLuint));
    assert(sizeof(uint32_t) == sizeof(GLuint) &&"Your plataform is not a 32 or 64 bits one, which is a requirement for this game. I'm sorry.\n");

    
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "OpenClaft", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    
    // Somente após criar um contexto, que se pode iniciar GLEW.
    if (glewInit() != GLEW_OK) {
        std::cout << "Erro ao tentar carregar GLEW!\n";
    }
    
    std::cout << glGetString(GL_VERSION) << "\n";

    {
        float Triangle[] = {
            -0.5f,-0.5f, 0.0f, 0.0f, // 0
            0.5f, -0.5f, 1.0f, 0.0f, // 1
            0.5f, 0.5f, 1.0f, 1.0f, // 2
            -0.5f, 0.5f,  0.0f, 1.0f// 3
        };

        uint32_t cube[] = {
            0,1,2,
            2,3,0
        };

        GLCall(glEnable(GL_BLEND));
        GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

        // Desenhar blocos. 
        // Criar uma câmera + controles.
        // Aplicar texturas
        // Iluminação.
        // Aplicar física.
        // 

        //uint32_t VertexArrayObject;
        //GLCall(glGenVertexArrays(1, &VertexArrayObject));
        //GLCall(glBindVertexArray(VertexArrayObject));
        //assert(VertexArrayObject != 0 && "A criação do VertexArrayObject não foi bem sucedida.\n");

        VertexArray vertexA;
        VertexBuffer vertexB(Triangle, 4 * 4 * sizeof(float)); // 4 floats per vertexGera e binda o vertex buffer.
        
        vertexA.AddLayout<float>(2);
        vertexA.AddLayout<float>(2);
        vertexA.AddBufferAftervbBind(vertexB);


        
        

        IndexBuffer indexB(cube, 6);                         // Gera e binda o vertex buffer.
    
        glm::mat4 proj = glm::ortho(-2.0f, 2.0f, -1.5f,1.5f, -1.0f, 1.0f);

        Shader shader;
        shader.Bind();
        shader.SetUniform4f("u_Color", 0.8f, 0.3f, 0.8f, 1.0f);
        shader.SetUniformMat4f("u_MVP", proj);
        Texture texture("./src/resources/textures/Grass2.png"); // Relativo
        texture.Bind();
        shader.SetUniform1i("u_Texture",0);// 0 -> 31

        

        // o Profile de Compatibilidade do OpennGL criará um vertexArrayObject para nós.
       
        vertexA.Unbind();
        shader.Unbind();
        vertexB.Unbind();
        indexB.Unbind();

        Engine engine;

        float r = 0.0f;
        float increment = 0.05f;

        /* Loop until the user closes the window */
        while (!glfwWindowShouldClose(window))
        {
            // ...Agora : Bind o shader, o VertexArray, o indexBufer e faz a DrawCall.
            /* Render here */
            engine.Clear();

            

            shader.Bind();
            shader.SetUniform4f("u_Color", r, 0.3f, 0.8f, 1.0f);

            engine.Draw(vertexA, indexB, shader);

            if (r > 1.0f)
                increment = -0.05f;
            else if (r < 0.0f)
            {
                increment = 0.05f;
            }

            r += increment;
            /* Swap front and back buffers */
            glfwSwapBuffers(window);

            /* Poll for and process events */
            glfwPollEvents();
        }
       
    }
    glfwTerminate();
    return 0;
};