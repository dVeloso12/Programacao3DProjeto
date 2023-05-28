
#pragma once
#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
#include <iostream>
#include <vector>

#include "Camera.h"

using namespace std;
using namespace glm;

class World
{
private:
	Camera* mainCamera;
	vector<Camera*> allCameras;



public:
	World(Camera* camera);
	void AddCameraToList(Camera* camera);
	void SetMainCamera(Camera* camera);
};