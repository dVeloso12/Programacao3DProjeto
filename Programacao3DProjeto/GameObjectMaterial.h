#pragma once

#include <fstream>
#include <iostream>
#include <sstream>
#include <glm/glm.hpp>

#include "Texture.h"
#include "Shader.h"

using namespace std;


class GameObjectMaterial
{
private:
	glm::vec3 _emissive;
	glm::vec3 _ambient;
	glm::vec3 _diffuse;
	glm::vec3 _specular;
	float _shininess;
	Texture* _texture;
public:
	GameObjectMaterial(const string& fileName);
	~GameObjectMaterial();
	void Read(const std::string& fileName);



};