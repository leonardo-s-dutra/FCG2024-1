#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp> 
#include <stb_image.h>

#include <Shader.h>
#include "Sprite.h"

const GLuint SCREEN_WIDTH = 800;
const GLuint SCREEN_HEIGHT = 600;
const GLuint SCREEN_PLAYABLE_LIMIT = 48;

const glm::vec3 playerInitPosition = glm::vec3(SCREEN_WIDTH/2, 40, 0.0);
const GLchar* playerTexturePath = "Textures/Player/Fighter/Attack_1.png";
Sprite playerSprite;

const glm::vec3 backgroundScale = glm::vec3(static_cast<float>(SCREEN_WIDTH), static_cast<float>(SCREEN_HEIGHT), 1.0);
const glm::vec3 backgroundPosition = glm::vec3(static_cast<float>(SCREEN_WIDTH)/2.0, static_cast<float>(SCREEN_HEIGHT)/2.0, 1.0);
const GLchar* backgroundTexturePath = "Textures/Background/background.jpg";


void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
GLuint loadTexture(const GLchar* filePath, int* spriteWidth, int* spriteHeight);


int main()
{
	GLFWwindow* window;
	int width, height;
	int spriteWidth;
	int spriteHeight;
	Sprite backgroundSprite;
	Sprite enemySprite;
	GLuint playerTextureId;
	GLuint backgroundTextureId;
	GLuint enemyTextureId;

	glfwInit();

	window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Trabalho GA", nullptr, nullptr);
	glfwMakeContextCurrent(window);

	glfwSetKeyCallback(window, key_callback);

	if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cerr << "Failed to initialize GLAD" << "\n";
	}

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glfwGetFramebufferSize(window, &width, &height);
	glViewport(0, 0, width, height);

	Shader* shader = new Shader("VertexShader", "FragmentShader");
	shader->use();

	backgroundTextureId = loadTexture(backgroundTexturePath, &spriteWidth, &spriteHeight);
	backgroundSprite.init(
		backgroundTextureId,
		1,
		1,
		backgroundPosition,
		backgroundScale,
		0.0
	);
	backgroundSprite.setShader(shader);

	playerTextureId = loadTexture(playerTexturePath, &spriteWidth, &spriteHeight);
	playerSprite.init(
		playerTextureId,
		1,
		4,
		playerInitPosition,
		glm::vec3(spriteWidth, spriteHeight, 1.0),
		90.0
	);
	playerSprite.setShader(shader);

	enemyTextureId = loadTexture("Textures/Enemy/green.png", &spriteWidth, &spriteHeight);
	enemySprite.init(
		enemyTextureId,
		1,
		1,
		glm::vec3(200.0,300.0,0.0),
		glm::vec3(spriteWidth, spriteHeight, 1.0),
		0.0
	);
	enemySprite.setShader(shader);

	glm::mat4 projection = glm::ortho(0.0, static_cast<double>(SCREEN_WIDTH), 0.0, static_cast<double>(SCREEN_HEIGHT), -1.0, 1.0);
	shader->setMat4("projection", glm::value_ptr(projection));

	glActiveTexture(GL_TEXTURE0);
	shader->setInt("textureBuffer", 0);

	while(!glfwWindowShouldClose(window)) {
		glfwPollEvents();

		glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		backgroundSprite.draw();
		playerSprite.draw();
		enemySprite.draw();

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
	else if(key == GLFW_KEY_LEFT && (action == GLFW_PRESS || action == GLFW_REPEAT)) {
		if(playerSprite.position().x > SCREEN_PLAYABLE_LIMIT) {
			playerSprite.decPosX(10);
		}
	}
	else if(key == GLFW_KEY_RIGHT && (action == GLFW_PRESS || action == GLFW_REPEAT)) {
		if(playerSprite.position().x < (SCREEN_WIDTH-SCREEN_PLAYABLE_LIMIT)) {
			playerSprite.incPosX(10);
		}
	}
}


GLuint loadTexture(const GLchar* filePath, int* spriteWidth, int* spriteHeight)
{
	GLuint texID = -1;
	int no_of_channels;
	GLenum mode;

	glGenTextures(1, &texID);
	glBindTexture(GL_TEXTURE_2D, texID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); 
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	stbi_uc* data = stbi_load(filePath, spriteWidth, spriteHeight, &no_of_channels, 0);
	if(!data) {
    	std::cerr << "Failed to load texture from " << filePath << "\n";
		goto loadTextureEnd;
	}

	mode = no_of_channels == 3 ? GL_RGB : GL_RGBA;
	glTexImage2D(GL_TEXTURE_2D, 0, mode, *spriteWidth, *spriteHeight, 0, mode, GL_UNSIGNED_BYTE, data);

	glGenerateMipmap(GL_TEXTURE_2D);

	stbi_image_free(data);

	glBindTexture(GL_TEXTURE_2D, 0);

loadTextureEnd:
	return texID;
}
