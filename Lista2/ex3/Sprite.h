#pragma once

#include <glm/glm.hpp> 
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Shader.h"


class Sprite
{
public:
    Sprite();
    ~Sprite();

    void init(glm::vec3 position=glm::vec3(0), glm::vec3 scale=glm::vec3(1), float angle=0.0, glm::vec3 color=glm::vec3(1.0, 1.0, 0.0));
    void update();
    void draw();
    void finalize();

    void setShader(Shader *shader);
    void setAngle(const float& angle);

private:
    GLuint __VAO;
    glm::vec3 __position;
    glm::vec3 __scale;
    float __angle;
    Shader* __shader;
};
