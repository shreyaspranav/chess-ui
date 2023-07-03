#include "Renderer.h"

#include <string>
#include <iostream>

#include "glad/gl.h"
#include <vector>

uint32_t vertexBufferID;
uint32_t indexBufferID;
uint32_t vertexArrayID;
uint32_t shaderProgramID;

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

const char* vs = R"(
    #version 330 core

    layout(location = 0)in vec3 aQuadVertex;
    layout(location = 1)in vec4 aQuadColor;

    out vec4 quadColor;

    uniform mat4 u_ProjectionMat;

    void main()
    {
        gl_Position = u_ProjectionMat * vec4(aQuadVertex, 1.0);
        quadColor = aQuadColor;
    }
)";

const char* fs = R"(
    #version 330 core

    in vec4 quadColor;
    out vec4 fragColor;

    void main()
    {
        fragColor = quadColor;
    }
)";

uint32_t default_ind[6] = { 0, 1, 2, 0, 2, 3 };

glm::vec3 default_vertices[4] = {
    glm::vec3( 0.5f,  0.5f, 0.0f),
    glm::vec3(-0.5f,  0.5f, 0.0f),
    glm::vec3(-0.5f, -0.5f, 0.0f),
    glm::vec3( 0.5f, -0.5f, 0.0f)
};

std::vector<float> vertex_data;
std::vector<uint32_t> index_data;

uint32_t vertex_index = 0;
uint32_t index_count = 0;

uint32_t windowWidth = 0;
uint32_t windowHeight = 0;

glm::mat4 projectionMatrix;

void Renderer::Init()
{   
    //vertex_data.reserve(7000);
    //index_data.reserve(6000);

    for (int i = 0; i < 7000; i++)
        vertex_data.push_back(0.0f);
    for (int i = 0; i < 6000; i++)
        index_data.push_back(0.0f);

    glCreateVertexArrays(1, &vertexArrayID);
    glBindVertexArray(vertexArrayID);

    glCreateBuffers(1, &vertexBufferID);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID);
    glBufferData(GL_ARRAY_BUFFER, 7000 * sizeof(float), nullptr, GL_DYNAMIC_DRAW);

    glCreateBuffers(1, &indexBufferID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6000 * sizeof(int), nullptr, GL_DYNAMIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (const void*)0);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (const void*)(3 * sizeof(float)));

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    uint32_t vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShaderID, 1, &vs, nullptr);    
    glCompileShader(vertexShaderID);

    int  success;
    char infoLog[512];
    glGetShaderiv(vertexShaderID, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(vertexShaderID, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    uint32_t fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShaderID, 1, &fs, nullptr);    
    glCompileShader(fragmentShaderID);

    glGetShaderiv(fragmentShaderID, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(fragmentShaderID, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    shaderProgramID = glCreateProgram();
    glAttachShader(shaderProgramID, vertexShaderID);
    glAttachShader(shaderProgramID, fragmentShaderID);
    glLinkProgram(shaderProgramID);
    glUseProgram(shaderProgramID);


    projectionMatrix = glm::ortho(-1, 1, -1, 1);
}

void Renderer::Begin(uint32_t window_width, uint32_t window_height)
{
    vertex_index = 0;
    index_count = 0;

    if(window_width != windowWidth || window_height != windowHeight)
    {
        windowWidth = window_width;
        windowHeight = window_height;

        float aspectRatio = (float)windowWidth / (float)windowHeight;
        projectionMatrix = glm::ortho(-aspectRatio, aspectRatio, -1.0f, 1.0f);

        glViewport(0, 0, window_width, window_height);
    }
}

void Renderer::End()
{
}

void Renderer::RenderFrame()
{
    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID);
    glBufferSubData(GL_ARRAY_BUFFER, 0, vertex_index * 7 * sizeof(float), vertex_data.data());

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferID);
    glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, index_count * sizeof(uint32_t), index_data.data());

    glUniformMatrix4fv(glGetUniformLocation(shaderProgramID, "u_ProjectionMat"), 1, GL_TRUE, glm::value_ptr(projectionMatrix));

    glDrawElements(GL_TRIANGLES, index_count, GL_UNSIGNED_INT, 0);
}

void Renderer::DrawQuad(const glm::vec3 &pos, float rotation, const glm::vec2 &scale, const glm::vec4 &color)
{
    for(int i = 0; i < 6; i++)
        index_data[index_count++] = default_ind[i] + vertex_index;

    for(int i = 0; i < 4; i++)
    {
        vertex_data[(vertex_index * 7) + 0] = default_vertices[i].x * scale.x + pos.x;
        vertex_data[(vertex_index * 7) + 1] = default_vertices[i].y * scale.y + pos.y;
        vertex_data[(vertex_index * 7) + 2] = default_vertices[i].z + pos.z;

        vertex_data[(vertex_index * 7) + 3] = color.r;
        vertex_data[(vertex_index * 7) + 4] = color.g;
        vertex_data[(vertex_index * 7) + 5] = color.b;
        vertex_data[(vertex_index * 7) + 6] = color.a;

        vertex_index++;
    }

#if 0
    for(int i = 0; i < 4; i++) {
        for(int j = 0; j < 7; j++)
            std::cout << vertex_data[i * 7 + j] << "\t";
        std::cout << std::endl;
    }

    for(int i = 0; i < 6; i++)
        std::cout << index_data[i] << "\t" << vertex_index;
    std::cout << "\n";
#endif
}
