#pragma once
#include <glm/glm.hpp>
#include <vector>
#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <iostream>
#include <cmath>

#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective

#include "Read_MTL.h"
#include "Shader.h"

namespace Models {

	class Model {

	private:
		Shader* _shader;
		Read_MTL* _material;
		GLuint _vao;
		GLuint _posBuffer, _texBuffer, _normalBuffer;
		std::vector<GLfloat> _positions;
		std::vector<GLfloat> _texCoords;
		std::vector<GLfloat> _normals;
	

	public:
		void SetShader(Shader* shader);
		Shader* GetShader();
		void Read(const std::string& fileName);
		void DrawModel(glm::mat4 model, glm::mat4 view, glm::mat4 projection);
	private:
		void Send();

	};
}