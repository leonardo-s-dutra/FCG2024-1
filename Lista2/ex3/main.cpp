#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp> 
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <Shader.h>
#include "Sprite.h"

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);

const GLuint WIDTH = 800;
const GLuint HEIGHT = 600;


int main()
{
	glfwInit();

	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Exercicio 3", nullptr, nullptr);
	glfwMakeContextCurrent(window);

	glfwSetKeyCallback(window, key_callback);

	if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cerr << "Failed to initialize GLAD" << "\n";
	}

	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
	glViewport(0, 0, width, height);

	Shader* shader = new Shader("VertexShader", "FragmentShader");	
	shader->use();

	Sprite sprite, sprite2, sprite3, background, ground, sprite4;
	sprite.init(glm::vec3(400.0,300.0,0.0), glm::vec3(200.0,200.0,1.0),0.0,glm::vec3(1.0,0.0,1.0));
	sprite.setShader(shader);

	sprite2.init(glm::vec3(200.0,300.0,0.0), glm::vec3(100.0,50.0,1.0));
	sprite2.setShader(shader);

	sprite3.init(glm::vec3(600.0,300.0,0.0), glm::vec3(50.0,100.0,1.0), 0.0,glm::vec3(0.0,0.5,0.0));
	sprite3.setShader(shader);

	background.init(glm::vec3(400.0,300.0,0.0), glm::vec3(800.0,600.0,1.0),0.0,glm::vec3(0.0,1.0,1.0));
	background.setShader(shader);

	ground.init(glm::vec3(400.0,100.0,0.0), glm::vec3(800.0,200.0,1.0),0.0,glm::vec3(0.5,0.5,0.0));
	ground.setShader(shader);

	sprite4.init(glm::vec3(200.0,500.0,0.0), glm::vec3(100.0,100.0,1.0),45.0,glm::vec3(1.0,1.0,0.0));
	sprite4.setShader(shader);

	glm::mat4 projection = glm::ortho(0.0, 800.0, 0.0, 600.0, -1.0, 1.0);
	shader->setMat4("projection", glm::value_ptr(projection));

	while(!glfwWindowShouldClose(window)) {
		glfwPollEvents();

		glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		float angulo = (float)glfwGetTime();
		sprite4.setAngle(glm::degrees(angulo));

		background.draw();
		ground.draw();
		sprite.draw();
		sprite2.draw();
		sprite3.draw();
		sprite4.draw();

		glfwSwapBuffers(window);
	}

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
