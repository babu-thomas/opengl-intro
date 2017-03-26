#include <iostream>
#include <GL/glew.h>
#include "Display.h"
#include "Shader.h"
#include "Mesh.h"

int main(int argc, char* argv[])
{
	Display display(800, 600, "Hello World");

	Shader shader(".\\res\\basic_shader");

	GLfloat points[] = {
		 0.0f,  0.5f, 0.0f,
		 0.5f, -0.5f, 0.0f,
		-0.5f, -0.5f, 0.0f
	};

	GLfloat colors[] = {
		1.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 1.0f
	};

	// Generate Vertex Array object
	GLuint VAO;
	glGenVertexArrays(1, &VAO);

	// Generate Vertex Buffer objects for points and colors
	GLuint points_vbo, colors_vbo;
	glGenBuffers(1, &points_vbo);
	glGenBuffers(1, &colors_vbo);


	glBindVertexArray(VAO);
		// For points
		glBindBuffer(GL_ARRAY_BUFFER, points_vbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
		glEnableVertexAttribArray(0);

		// For colors
		glBindBuffer(GL_ARRAY_BUFFER, colors_vbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
		glEnableVertexAttribArray(1);
	glBindVertexArray(0);




	while (!display.isClosed())
	{
		display.clear(0.0f, 0.0f, 0.0f, 0.0f);
		shader.bind();

		glBindVertexArray(VAO);
			glDrawArrays(GL_TRIANGLES, 0, 3);
		glBindVertexArray(0);

		display.update();
	}
	return 0;
}