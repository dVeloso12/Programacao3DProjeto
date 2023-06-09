#include "GameObjectMaterial.h"

#include <vector>

GameObjectMaterial::GameObjectMaterial(const string& fileName)
{
	Read(fileName);

}

void GameObjectMaterial::Read(const std::string& fileName) {
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
			_texture = new Texture(path);
		}
	}
}