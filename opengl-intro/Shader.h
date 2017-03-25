#pragma once

#include <string>
#include <GL/glew.h>

class Shader
{
public:
	Shader(const std::string& filename);
	~Shader();
	void bind();
private:
	std::string loadShader(const std::string& filename);
	void checkShaderError(GLuint shader, GLuint flag, bool isProgram,
		const std::string& errorMessage);
	GLuint createShader(const std::string& text, unsigned int type);
	// Only Vertex and Fragment shaders for now
	enum
	{
		VERTEX_SHADER,
		FRAGMENT_SHADER,
		NUM_SHADERS
	};
	GLuint m_program;
	GLuint m_shaders[NUM_SHADERS];
};