#pragma once

#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/quaternion.hpp>

using namespace glm;

// Base class for objects that can be placed in a world with a transformation
class WorldPosition {

protected:
	vec3 _position;
	vec3 _rotation;
	vec3 _scale;

public:
	WorldPosition();
	virtual void SetPosition(vec3 value);
	vec3 GetPosition();
	virtual void SetRotation(vec3 value);
	vec3 GetRotation();
	virtual void SetScale(vec3 value);
	vec3 getScale();
	virtual void Rotate(vec3 rotation);

};
