#include <Shader.h>


Shader::Shader(const GLchar* vertexShaderPath, const GLchar* fragmentShaderPath)
{
    std::string vertexCode;
    std::string fragmentCode;
    std::ifstream vertexShaderFile;
    std::ifstream fragmentShaderFile;

    vertexShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    fragmentShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

    try {
        vertexShaderFile.open(vertexShaderPath);
        fragmentShaderFile.open(fragmentShaderPath);
        std::stringstream vertexShaderStream, fragmentShaderStream;

        vertexShaderStream << vertexShaderFile.rdbuf();
        fragmentShaderStream << fragmentShaderFile.rdbuf();

        vertexShaderFile.close();
        fragmentShaderFile.close();

        vertexCode = vertexShaderStream.str();
        fragmentCode = fragmentShaderStream.str();
    }
    catch(const std::ifstream::failure& e) {
        std::cerr << "Error: " << e.what() << "\n";
    }

    const GLchar* vertexShaderCode = vertexCode.c_str();
    const GLchar* fragmentShaderCode = fragmentCode.c_str();

    GLuint vertex, fragment;
    GLint success;
    GLchar infoLog[512];

    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vertexShaderCode, NULL);
    glCompileShader(vertex);

    glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
    if(!success) {
        glGetShaderInfoLog(vertex, 512, NULL, infoLog);
        std::cerr << "Vertex shader compilation failed\n" << infoLog << "\n";
    }

    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fragmentShaderCode, NULL);
    glCompileShader(fragment);

    glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
    if(!success) {
        glGetShaderInfoLog(fragment, 512, NULL, infoLog);
        std::cerr << "Fragment shader compilation failed\n" << infoLog << "\n";
    }

    this->__ID = glCreateProgram();
    glAttachShader(this->__ID, vertex);
    glAttachShader(this->__ID, fragment);
    glLinkProgram(this->__ID);

    glGetProgramiv(this->__ID, GL_LINK_STATUS, &success);
    if(!success) {
        glGetProgramInfoLog(this->__ID, 512, NULL, infoLog);
        std::cout << "Shader program linking failed\n" << infoLog << "\n";
    }

    glDeleteShader(vertex);
    glDeleteShader(fragment);
}

Shader::~Shader()
{

}

void Shader::use()
{
    glUseProgram(this->__ID);
}

GLuint Shader::ID()
{
    return this->__ID;
}
