#include "Shader.h"
#include <iostream>
#include <fstream>

Shader::Shader(const std::string& filename)
{
	m_program = glCreateProgram();
	// Compile shaders
	m_shaders[VERTEX_SHADER] = createShader(loadShader(filename + ".vert"), GL_VERTEX_SHADER);
	m_shaders[FRAGMENT_SHADER] = createShader(loadShader(filename + ".frag"), GL_FRAGMENT_SHADER);
	for (int i = 0; i < NUM_SHADERS; i++)
	{
		glAttachShader(m_program, m_shaders[i]);
	}

	// Link shaders
	glLinkProgram(m_program);
	checkShaderError(m_program, GL_LINK_STATUS, true, "Error: Program linking failed: ");
	// Validate shaders
	glValidateProgram(m_program);
	checkShaderError(m_program, GL_VALIDATE_STATUS, true, "Error: Program validation failed: ");

}

Shader::~Shader()
{
	for (int i = 0; i < NUM_SHADERS; i++)
	{
		glDetachShader(m_program, m_shaders[i]);
		glDeleteShader(m_shaders[i]);
	}
	glDeleteProgram(m_program);
}

void Shader::bind()
{
	glUseProgram(m_program);
}

std::string Shader::loadShader(const std::string& filename)
{
	std::ifstream file;
	file.open(filename.c_str());

	std::string output;
	std::string line;

	if (file.is_open())
	{
		while (file.good())
		{
			std::getline(file, line);
			output.append(line + "\n");
		}
	}
	else
	{
		std::cerr << "Unable to load shader: " << filename << std::endl;
	}

	return output;
}

void Shader::checkShaderError(GLuint shader, GLuint flag, bool isProgram,
	const std::string & errorMessage)
{
	GLint success = 0;
	GLchar error[1024] = { 0 };

	if (isProgram)
		glGetProgramiv(shader, flag, &success);
	else
		glGetShaderiv(shader, flag, &success);

	if (success == GL_FALSE)
	{
		if (isProgram)
			glGetProgramInfoLog(shader, sizeof(error), NULL, error);
		else
			glGetShaderInfoLog(shader, sizeof(error), NULL, error);

		std::cerr << errorMessage << ": '" << error << "'" << std::endl;
	}
}

GLuint Shader::createShader(const std::string & text, unsigned int type)
{
	GLuint shader = glCreateShader(type);
	if (shader == 0)
	{
		std::cerr << "Error: Shader creation failed!" << std::endl;
	}
	
	const GLchar* shaderSources[1];
	GLint shaderSourceLengths[1];

	shaderSources[0] = text.c_str();
	shaderSourceLengths[0] = text.length();

	glShaderSource(shader, 1, shaderSources, shaderSourceLengths);
	glCompileShader(shader);

	checkShaderError(shader, GL_COMPILE_STATUS, false, "Error: Shader compilation failed: ");
	return shader;
}
