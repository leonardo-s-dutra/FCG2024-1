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

    void init(GLuint texID, GLuint no_of_animations=1, GLuint no_of_frames=1, glm::vec3 position=glm::vec3(0), glm::vec3 scale=glm::vec3(1), float angle=0.0, glm::vec3 color=glm::vec3(0.0, 0.0, 0.0));
    void update();
    void draw();
    void finalize();

    void setShader(Shader *shader);
    void setAngle(const float& angle);
    void incPosX(const GLuint pos);
    void decPosX(const GLuint pos);

    glm::vec3 position() const;
    glm::vec3 scale() const;

private:
    GLuint __VAO;
    GLuint __texID;
    glm::vec3 __position;
    glm::vec3 __scale;
    float __angle;
    Shader* __shader;
    GLuint __no_of_animations;
    GLuint __no_of_frames;
    GLuint __animation_index;
    GLuint __frame_index;
    glm::vec2 __texture_offset;
};
