#include <iostream>
#include <GL/glew.h>
#include "Display.h"
#include "Shader.h"
#include "Mesh.h"

int main(int argc, char* argv[])
{
	Display display(800, 600, "Hello World");

	Shader shader(".\\res\\basic_shader");

	GLfloat vertices[] = {
		-0.5f,  0.5f, 0.0f, // Top left
		 0.5f,  0.5f, 0.0f, // Top right
		 0.5f, -0.5f, 0.0f, // Bottom right
		-0.5f, -0.5f, 0.0f  // Bottom left
	};

	GLuint indices[] = {
		0, 1, 2, // First triangle
		0, 2, 3  // Second triangle
	};

	// Generate Vertex Array object
	GLuint VAO;
	glGenVertexArrays(1, &VAO);

	// Generate Vertex Buffer object
	GLuint VBO;
	glGenBuffers(1, &VBO);

	// Generate Element Buffer object
	GLuint EBO;
	glGenBuffers(1, &EBO);


	glBindVertexArray(VAO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		// Copy vertices data to buffer for opengl to use
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

		// Tell opengl how to interpret the data
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
		glEnableVertexAttribArray(0);
	glBindVertexArray(0);




	while (!display.isClosed())
	{
		display.clear(0.0f, 1.0f, 0.3f, 1.0f);
		shader.bind();

		glBindVertexArray(VAO);
			//glDrawArrays(GL_TRIANGLES, 0, 3);
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);

		display.update();
	}
	return 0;
}