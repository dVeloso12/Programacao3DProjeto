#pragma once

#define GLEW_STATIC
#include <GL\glew.h>

#include <unordered_map>
#include <glm/glm.hpp>

typedef struct {
	GLenum type;
	const char* fileName;
	GLuint shader;
} ShaderData;

class Shader
{
private:

	GLuint _programId;
	std::unordered_map<std::string, int> _uniformLocations;

public:
	Shader(ShaderData* shaders);
	~Shader();

	void LoadShaders(ShaderData* shaders);
	bool IsCompiled();

};
