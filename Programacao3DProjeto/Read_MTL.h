#pragma once

#include <fstream>
#include <iostream>
#include <sstream>
#include <glm/glm.hpp>

#include "Texture.h"

using namespace std;

namespace Material {
	class Read_MTL {
	private:
		glm::vec3 _emissive;
		glm::vec3 _ambient;
		glm::vec3 _diffuse;
		glm::vec3 _specular;
		float _shininess;
		Texture* _texture;

	public:

		Read_MTL(const string& fileName);
		void Read(const string& fileName);
		void Send(Shader* shader);
	};
}
#pragma once
