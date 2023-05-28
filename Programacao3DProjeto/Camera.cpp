#include "Camera.h"

#pragma region Contrutor
Camera::Camera(float Fov,int width,int height,float near,float far,vec3 Pos)
{
	Projection = perspective(radians(Fov), float(width) / float(height), near, far);
	ZOOM = 10.0f;
	ANGLE = 0.0f;
	WIDTH = width;
	HEIGHT = height;
	Position = Pos;
	view = ViewCamera();
	Direction = vec3(0.0f, 0.0f, -1.0f);
}
#pragma endregion
#pragma region get Variaveis
mat4 Camera :: getViewValue(){return view;}
mat4 Camera :: getProjection() { return Projection; }
vec3 Camera::getPosition() { return Position; }
vec3 Camera::getDirection() { return Direction; }
#pragma endregion
#pragma region Metodos
void Camera::ZoomCamera(GLFWwindow* window, double xoffset, double yoffset)
{
	// Se faz zoom in
	if (yoffset == 1) {
		// Incremento no zoom, varia com a distância da câmara
		ZOOM -= fabs(ZOOM) * 0.1f;
		
	}
	// Senão, se faz zoom out
	else if (yoffset == -1) {
		// Incremento no zoom, varia com a distância da câmara
		ZOOM += fabs(ZOOM) * 0.1f;
	}

	std::cout << "ZOOM = " << ZOOM << std::endl;
}
void Camera::ChangeCameraPosition(vec3 newPosition)
{
	WorldPosition::SetPosition(newPosition);
	Position = newPosition;
}
void Camera::ChangeCameraDirection(vec3 newDirection)
{
	Direction = newDirection;
}
mat4x4 Camera :: ViewCamera()
{
	Direction = normalize(Direction);
	return lookAt(
		vec3(Position.x, Position.y, Position.z + ZOOM),	// Posição da câmara no mundo
		vec3(Direction.x, Direction.y, Direction.z),	// Direção para a qual a câmara esta apontada
		vec3(0.0f, 1.0f, 0.0f)		// Vector vertical
	);
}
void Camera::UpdateCamera(GLFWwindow* window,float deltaTime)
{
	if (glfwGetWindowAttrib(window, GLFW_HOVERED))
	{
		view =  ViewCamera();

	}
	else
	{
		view = view;
	}
	
}
#pragma endregion
