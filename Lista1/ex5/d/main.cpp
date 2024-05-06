#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <Shader.h>

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
int setupGeometry();

const GLuint WIDTH = 800;
const GLuint HEIGHT = 600;


int main()
{
	glfwInit();

	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Exercicio 5.d", nullptr, nullptr);
	glfwMakeContextCurrent(window);

	glfwSetKeyCallback(window, key_callback);

	if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cerr << "Failed to initialize GLAD" << "\n";
	}

	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
	glViewport(0, 0, width, height);

	Shader* shader = new Shader("VertexShader", "FragmentShader");

	GLuint VAO = setupGeometry();
	
	GLint colorLoc = glGetUniformLocation(shader->ID(), "inputColor");
	
	shader->use();

	while(!glfwWindowShouldClose(window)) {
		glfwPollEvents();

		glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glLineWidth(5);
		glPointSize(10);

		glBindVertexArray(VAO);

		glUniform4f(colorLoc, 0.0f, 0.0f, 1.0f, 1.0f);
		glDrawArrays(GL_TRIANGLES, 0, 6);

		glUniform4f(colorLoc, 0.0f, 1.0f, 0.0f, 1.0f);
		glDrawArrays(GL_LINE_LOOP, 0, 3);
		glDrawArrays(GL_LINE_LOOP, 3, 3);

		glUniform4f(colorLoc, 1.0f, 0.0f, 0.0f, 1.0f);
		glDrawArrays(GL_POINTS, 0, 6);

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


int setupGeometry()
{
	GLfloat vertices[] = {
	/*   x    y    z 	*/
		-0.5, 0.5, 0.0, /* Vertice 0 */
		 0.0, 0.0, 0.0, /* Vertice 1 */
		 0.5, 0.5, 0.0, /* Vertice 2 */
		 0.0, 0.0, 0.0, /* Vertice 3 */
		-0.5,-0.5, 0.0, /* Vertice 4 */
		 0.5,-0.5, 0.0  /* Vertice 5 */
	};

	GLuint VBO, VAO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glGenVertexArrays(1, &VAO);

	glBindVertexArray(VAO);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0); 

	glBindVertexArray(0); 

	return VAO;
}
