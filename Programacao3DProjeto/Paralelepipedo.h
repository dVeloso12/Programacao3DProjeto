#pragma once
#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
#include <iostream>
#include <vector>


using namespace std;
using namespace glm;

class Paralelepipedo
{
public :
	Paralelepipedo(float xLenght,float yLenght,float zLenght);
	Paralelepipedo();
	mat4 getModel();
	vector<vec3> vertex;
	void displayModel(vector<vec3> vertex,mat4 mvp);
	void Rotate(float value, vec3 direction);
private:
	vector<vec3> getVertex(float xLenght, float yLenght,float zLenght);
	mat4 Model;
	
};