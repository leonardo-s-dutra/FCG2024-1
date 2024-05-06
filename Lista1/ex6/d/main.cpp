#include <iostream>
#include <cmath>
#include <vector>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <Shader.h>

#define _USE_MATH_DEFINES

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
int setupPizza(float radius);

const GLuint WIDTH = 800;
const GLuint HEIGHT = 600;

const GLuint NO_OF_POINTS = 30;

int main()
{
	glfwInit();

	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Exercicio 6.d", nullptr, nullptr);
	glfwMakeContextCurrent(window);

	glfwSetKeyCallback(window, key_callback);

	if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cerr << "Failed to initialize GLAD" << "\n";
	}

	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
	glViewport(0, 0, width, height);

	Shader* shader = new Shader("VertexShader", "FragmentShader");

	GLuint VAO = setupPizza(0.5);
	GLuint no_of_vertices = NO_OF_POINTS + 2;

	GLint colorLoc = glGetUniformLocation(shader->ID(), "inputColor");
	
	shader->use();

	while(!glfwWindowShouldClose(window)) {
		glfwPollEvents();

		glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glBindVertexArray(VAO);

		glUniform4f(colorLoc, 0.0f, 0.0f, 1.0f, 1.0f);
		glDrawArrays(GL_TRIANGLE_FAN, 0, no_of_vertices);

		glUniform4f(colorLoc, 1.0f, 0.0f, 1.0f, 1.0f);
		glDrawArrays(GL_LINE_LOOP, 1, no_of_vertices-2);

		glBindVertexArray(0);

		glfwSwapBuffers(window);
	}

	glDeleteVertexArrays(1, &VAO);

	glfwTerminate();
	
	delete shader;

	return 0;
}


void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, GL_TRUE);
	}
}


int setupPizza(float radius)
{
	std::vector<GLfloat> vertices;

	float slice = 2 * M_PI / NO_OF_POINTS;
	float angle = -slice;

	/* Add origin point as center of the circle */
	vertices.push_back(0.0);	/* x */
	vertices.push_back(0.0);	/* y */
	vertices.push_back(0.0);	/* z */

	for(int i = 0; i < 3; i++) {
		float x = radius * cos(angle);
		float y = radius * sin(angle);
		float z = 0.0;

		vertices.push_back(x);
		vertices.push_back(y);
		vertices.push_back(z);

		angle = angle + slice;
	}

	GLuint VBO, VAO;

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(GLfloat), vertices.data(), GL_STATIC_DRAW);

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0); 

	glBindVertexArray(0); 

	return VAO;
}
