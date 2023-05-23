#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
#include <iostream>

using namespace std;
using namespace glm;

class Camera
{
public:
	Camera(float Fov, int width, int height, float near, float far);
	void ZoomCamera(GLFWwindow* window, double xoffset, double yoffset);
	mat4 getProjection();
	mat4 getViewValue();
	void UpdateCamera(GLFWwindow* window, float deltaTime);
	

private:
	mat4x4 ViewCamera();
	mat4 Projection;
	mat4 view;
	GLfloat ZOOM;
	GLfloat ANGLE;
	float WIDTH;
	float HEIGHT;
	float rotation;
};