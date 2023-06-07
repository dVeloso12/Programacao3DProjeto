#include <iostream>
#include <fstream>

#include <glm/gtc/type_ptr.hpp>

#include "Shader.h"

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

namespace Rendering {
	Shader::Shader(ShaderData* shaders) {
		LoadShaders(shaders);
	}

	Shader::~Shader() {
		if (_programId != 0) {
			glDeleteProgram(_programId);
		}
	}

	void Shader::Bind() {
		glUseProgram(_programId);
	}

	void Shader::Unbind() {
		glUseProgram(0);
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

	bool Shader::IsCompiled() {
		return _programId != 0;
	}

	void Shader::LinkInput(const std::string& name, unsigned int type, unsigned int count) {
		int id = glGetProgramResourceLocation(_programId, GL_PROGRAM_INPUT, name.c_str());
		glVertexAttribPointer(id, count, type, GL_FALSE, count * sizeof(type), 0);
		glEnableVertexAttribArray(id);
	}

	void Shader::SetUniform1i(const std::string& name, int value) {
		glProgramUniform1i(_programId, GetUniformLocation(name), value);
	}

	void Shader::SetUniform1f(const std::string& name, float value) {
		glProgramUniform1f(_programId, GetUniformLocation(name), value);
	}

	void Shader::SetUniform3f(const std::string& name, float v1, float v2, float v3) {
		glProgramUniform3f(_programId, GetUniformLocation(name), v1, v2, v3);
	}

	void Shader::SetUniform3fv(const std::string& name, glm::vec3 value) {
		glProgramUniform3fv(_programId, GetUniformLocation(name), 1, glm::value_ptr(value));
	}

	void Shader::SetUniformMatrix3fv(const std::string& name, glm::mat3 value) {
		glProgramUniformMatrix3fv(_programId, GetUniformLocation(name), 1, GL_FALSE, glm::value_ptr(value));
	}

	void Shader::SetUniformMatrix4fv(const std::string& name, glm::mat4 value) {
		glProgramUniformMatrix4fv(_programId, GetUniformLocation(name), 1, GL_FALSE, glm::value_ptr(value));
	}

	int Shader::GetUniformLocation(const std::string& name) {
		if (_uniformLocations.find(name) != _uniformLocations.end()) {
			return _uniformLocations.at(name);
		}

		int location = glGetUniformLocation(_programId, name.c_str());
		if (location == -1) {
			std::cerr << "Invalid uniform name: " << name << std::endl;
		}

		_uniformLocations[name] = location;
		return location;
	}
}

