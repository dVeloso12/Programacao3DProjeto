#include "WorldPosition.h"

using namespace glm;

WorldPosition::WorldPosition() {

	_position = vec3(0.0f);
	_rotation = vec3(0.0f);
	_scale = vec3(1.0f);
}

void WorldPosition::SetPosition(vec3 value) {
	_position = value;
}

vec3 WorldPosition::GetPosition() {
	return _position;
}

void WorldPosition::SetRotation(vec3 value) {
	_rotation = value;
}

vec3 WorldPosition::GetRotation() {
	return _rotation;
}

void WorldPosition::SetScale(vec3 value) {
	_scale = value;
}

vec3 WorldPosition::getScale() {
	return _scale;
}

void WorldPosition::Rotate(vec3 rotation) {
	_rotation += rotation;
}