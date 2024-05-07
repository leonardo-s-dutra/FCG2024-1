#include "Sprite.h"


Sprite::Sprite()
{

}

Sprite::~Sprite()
{
    glDeleteVertexArrays(1, &this->__VAO);
}

void Sprite::init(GLuint texID, glm::vec3 position, glm::vec3 scale, float angle, glm::vec3 color)
{
    this->__position = position;
    this->__scale = scale;
    this->__angle = angle;
    this->__texID = texID;

    GLfloat vertices[] = {
	/*   x    y    z    r        g        b        s    t   */
		-0.5, 0.5, 0.0, color.r, color.g, color.b, 0.0, 1.0, /* Vertice 0 */
        -0.5,-0.5, 0.0, color.r, color.g, color.b, 0.0, 0.0, /* Vertice 1 */
         0.5, 0.5, 0.0, color.r, color.g, color.b, 1.0, 1.0, /* Vertice 2 */
        -0.5,-0.5, 0.0, color.r, color.g, color.b, 0.0, 0.0, /* Vertice 3 */
         0.5,-0.5, 0.0, color.r, color.g, color.b, 1.0, 0.0, /* Vertice 4 */
         0.5, 0.5, 0.0, color.r, color.g, color.b, 1.0, 1.0  /* Vertice 5 */
	};

	GLuint VBO;

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glGenVertexArrays(1, &this->__VAO);
	glBindVertexArray(this->__VAO);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3*sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6*sizeof(GLfloat)));
	glEnableVertexAttribArray(2);

	glBindBuffer(GL_ARRAY_BUFFER, 0); 

	glBindVertexArray(0);
}

void Sprite::update()
{
    glm::mat4 model = glm::mat4(1);
    model = glm::translate(model, this->__position);
	model = glm::rotate(model,glm::radians(this->__angle), glm::vec3(0.0, 0.0, 1.0));
    model = glm::scale(model, this->__scale);
    this->__shader->setMat4("model", glm::value_ptr(model));
}

void Sprite::draw()
{
    this->update();

	glBindTexture(GL_TEXTURE_2D, this->__texID);

    glBindVertexArray(this->__VAO);

	glDrawArrays(GL_TRIANGLES, 0, 6);

    glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Sprite::setShader(Shader *shader)
{
    this->__shader = shader;
}

void Sprite::setAngle(const float& angle)
{
    this->__angle = angle;
}

void Sprite::incPosX(const GLuint pos)
{
    this->__position.x += pos;
}

void Sprite::decPosX(const GLuint pos)
{
    this->__position.x -= pos;
}

glm::vec3 Sprite::position() const
{
    return this->__position;
}

glm::vec3 Sprite::scale() const
{
    return this->__scale;
}