#pragma once

#define GLEW_STATIC
#include <GL\glew.h>

#include <unordered_map>
#include <glm/glm.hpp>

using namespace std;
using namespace glm;

typedef struct {
	GLenum type;
	const char* fileName;
	GLuint shader;
} ShaderData;

class Shader
{
private:

	GLuint _programId;
	unordered_map<string, int> _uniformLocations;

public:
	Shader(ShaderData* shaders);
	~Shader();

	void Bind();
	void Unbind();

	void LoadShaders(ShaderData* shaders);
	bool IsCompiled();

	void LinkInput(const string& name, unsigned int type, unsigned int count);

	void SetUniform1i(const string& name, int value);
	void SetUniform1f(const string& name, float value);
	void SetUniform3f(const string& name, float v1, float v2, float v3);
	void SetUniform3fv(const string& name, vec3 value);
	void SetUniformMatrix3fv(const string& name, mat3 value);
	void SetUniformMatrix4fv(const string& name, mat4 value);

private:
	int GetUniformLocation(const string& name);
};
