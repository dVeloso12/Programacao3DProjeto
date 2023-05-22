#pragma once

#include <fstream>
#include <iostream>
#include <sstream>
#include <glm/glm.hpp>

//#include "Texture.hpp"


namespace Models {
	class Read_MTL {
	private:
		glm::vec3 _emissive;
		glm::vec3 _ambient;
		glm::vec3 _diffuse;
		glm::vec3 _specular;
		float _shininess;
		//Texture* _texture;

	public:
		Read_MTL(const std::string& fileName);
	

		void Read(const std::string& fileName);
	};
}
#pragma once
