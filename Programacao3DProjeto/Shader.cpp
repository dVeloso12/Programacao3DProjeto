#include <iostream>
#include <fstream>

#include <glm/gtc/type_ptr.hpp>

#include "Shader.h"
using namespace std;


const GLchar* ReadShader(const char* fileName) {

	std::ifstream file(fileName, std::ifstream::ate | std::ifstream::binary);

	if (file.is_open()) {
		std::streampos fileSize = file.tellg();

		file.seekg(0);

		GLchar* source = new GLchar[int(fileSize) + 1];

		file.read(source, fileSize);

		source[fileSize] = 0;

		file.close();

		return const_cast<const GLchar*>(source);
	}
	else {
		std::cerr << "Could not open file '" << fileName << "'" << std::endl;

		return nullptr;
	}

	return nullptr;
}

Shader::Shader(ShaderData* shaders) {

	LoadShaders(shaders);
}

Shader::~Shader() {
	if (_programId != 0) {
		glDeleteProgram(_programId);
	}
}

bool Shader::IsCompiled() {
	return _programId != 0;
}

void Shader::LoadShaders(ShaderData* shaders) {
	if (_programId != 0) {
		glDeleteProgram(_programId);
	}

	if (!shaders) {
		_programId = 0;
		return;
	}

	GLuint program = glCreateProgram();

	if (program != NULL)
	{
		for (GLint i = 0; shaders[i].type != GL_NONE; i++)
		{
			shaders[i].shader = glCreateShader(shaders[i].type);

			const GLchar* source = ReadShader(shaders[i].fileName);

			if (!source) {
				for (GLint j = 0; shaders[j].type != GL_NONE; j++)
				{
					if (shaders[j].shader != 0) {
						glDeleteShader(shaders[j].shader);
						shaders[j].shader = 0;
					}
				}

				_programId = 0;
				return;
			}

			glShaderSource(shaders[i].shader, 1, &source, NULL);
			delete[] source;

			glCompileShader(shaders[i].shader);

			GLint compiled;
			glGetShaderiv(shaders[i].shader, GL_COMPILE_STATUS, &compiled);
			if (!compiled) {
				for (GLint j = 0; shaders[j].type != GL_NONE; j++)
				{
					if (shaders[j].shader != 0) {
						glDeleteShader(shaders[j].shader);
						shaders[j].shader = 0;
					}
				}

				std::cout << "Error compiling shader: " << shaders[i].fileName << std::endl;

				_programId = 0;
				return;
			}

			glAttachShader(program, shaders[i].shader);
		}

		glLinkProgram(program);

		GLint linked;
		glGetProgramiv(program, GL_LINK_STATUS, &linked);
		if (!linked) {
			for (GLint j = 0; shaders[j].type != GL_NONE; j++)
			{
				if (shaders[j].shader != 0) {
					glDeleteShader(shaders[j].shader);
					shaders[j].shader = 0;
				}
			}

			_programId = 0;
			return;
		}

		_programId = program;
	}
}