#include "Read_MTL.h"

#include <vector>

namespace Material {
	Read_MTL::Read_MTL(const std::string& fileName) {
		Read(fileName);
	}

	void Read_MTL::Read(const std::string& fileName) {
		std::ifstream inFile(fileName);

		if (!inFile.is_open()) {
			std::cerr << "Models::Material::Read: Could not open file" << std::endl;
			return;
		}

		int pos = fileName.find_last_of('/');
		std::string path = fileName.substr(0, pos + 1);

		std::istringstream iss;
		std::string line;
		std::string prefix;

		while (std::getline(inFile, line)) {
			iss.clear();
			iss.str(line);
			iss >> prefix;

			if (prefix == "Ns") {
				iss >> _shininess;
			}
			else if (prefix == "Ka") {
				iss >> _ambient.x >> _ambient.y >> _ambient.z;
			}
			else if (prefix == "Kd") {
				iss >> _diffuse.x >> _diffuse.y >> _diffuse.z;
			}
			else if (prefix == "Ks") {
				iss >> _specular.x >> _specular.y >> _specular.z;
			}
			else if (prefix == "map_Kd") {
				iss >> prefix;
				path = path + prefix;
				//_texture = new Texture(path); // -> deve estar errado pq no outro projeto esta a ler um ficheiro tga e agr temos que ler um png ou colocar um png na bola
			}
		}
	}

	void Read_MTL::Send(Shader* shader) {
		shader->SetUniform3fv("uMaterial.emissive", _emissive);
		shader->SetUniform3fv("uMaterial.ambient", _ambient);
		shader->SetUniform3fv("uMaterial.diffuse", _diffuse);
		shader->SetUniform3fv("uMaterial.specular", _specular);
		shader->SetUniform1f("uMaterial.shininess", _shininess);

		if (_texture) {
			_texture->Send(shader);
		}
	}
}
