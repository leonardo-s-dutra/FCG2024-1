#pragma once

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Shader
{
public:
    Shader(const GLchar* vertexShaderPath, const GLchar* fragmentShaderPath);
    ~Shader();

    void use();
    
    GLuint ID();

private:
   	GLuint __ID;
};
