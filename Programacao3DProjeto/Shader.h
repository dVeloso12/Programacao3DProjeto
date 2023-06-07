#pragma once

#define GLEW_STATIC
#include <GL\glew.h>

#include <unordered_map>
#include <glm/glm.hpp>

namespace Rendering {
	typedef struct {
		GLenum type;
		const char* fileName;
		GLuint shader;
	} ShaderData;

	class Shader {
	private:
		GLuint _programId;
		std::unordered_map<std::string, int> _uniformLocations;

	public:
		Shader(ShaderData* shaders);
		~Shader();

		void Bind();
		void Unbind();

		void LoadShaders(ShaderData* shaders);
		bool IsCompiled();

		void LinkInput(const std::string& name, unsigned int type, unsigned int count);

		void SetUniform1i(const std::string& name, int value);
		void SetUniform1f(const std::string& name, float value);
		void SetUniform3f(const std::string& name, float v1, float v2, float v3);
		void SetUniform3fv(const std::string& name, glm::vec3 value);
		void SetUniformMatrix3fv(const std::string& name, glm::mat3 value);
		void SetUniformMatrix4fv(const std::string& name, glm::mat4 value);

	private:
		int GetUniformLocation(const std::string& name);
	};
}