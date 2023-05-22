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

namespace Models {
	class Model {

	private:
		Read_MTL* _material;
		GLuint _vao;
		GLuint _posBuffer, _texBuffer, _normalBuffer;
		std::vector<GLfloat> _positions;
		std::vector<GLfloat> _texCoords;
		std::vector<GLfloat> _normals;
	

	public:
		void Read(const std::string& fileName);
	private:
		void Send();

	};
}