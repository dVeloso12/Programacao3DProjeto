#pragma once

#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/quaternion.hpp>

#define GLEW_STATIC
#include <GL\glew.h>

#pragma comment(lib, "glew32s.lib")
#pragma comment(lib, "opengl32.lib")

#include "Read_Model.h"
#include "WorldPosition.h"

class GameObject : public WorldPosition{
private:

	Models :: Model* model;

public:

	GameObject();
	GameObject(Models::Model* _model);
	void SetModel(Models::Model* _model);
	void DisplayGameObject(mat4 view,mat4 projection);
};