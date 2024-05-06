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
    void setBool(const std::string& name, bool value) const;
    void setInt(const std::string& name, int value) const;
    void setFloat(const std::string& name, float value) const;
    void setVec2(const std::string& name, float v1, float v2) const;
    void setVec3(const std::string& name, float v1, float v2, float v3) const;
    void setVec4(const std::string& name, float v1, float v2, float v3, float v4) const;
    void setMat4(const std::string& name, float *v) const;
    
    GLuint ID();

private:
   	GLuint __ID;
};
