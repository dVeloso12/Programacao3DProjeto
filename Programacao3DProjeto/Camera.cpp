#include "Camera.h"

#pragma region Contrutor
Camera::Camera(float Fov,int width,int height,float near,float far,vec3 Pos, GLFWwindow* _window)
{
	Projection = perspective(radians(Fov), float(width) / float(height), near, far);
	ZOOM = 10.0f;
	ANGLE = 0.0f;
	WIDTH = width;
	HEIGHT = height;
	Position = Pos;
	Direction = vec3(0.0f, 0.0f, -1.0f);
	rotation = 0;

	Direction = normalize(Direction);
	//view = ViewCamera();
	view = lookAt(
		vec3(Position.x, Position.y, Position.z + ZOOM),	// Posi��o da c�mara no mundo
		vec3(Direction.x, Direction.y, Direction.z),	// Dire��o para a qual a c�mara esta apontada
		vec3(0.0f, 1.0f, 0.0f));	// Vector vertical

	window = _window;
}
#pragma endregion
#pragma region get Variaveis
mat4 Camera :: getViewValue(){return view;}
mat4 Camera :: getProjection() { return Projection; }
vec3 Camera::getPosition() { return Position; }
vec3 Camera::getDirection() { return Direction; }
GLFWwindow* Camera::getWindow() { return window;};
float Camera::getWidth() { return WIDTH;};
float Camera::getHeight() { return HEIGHT;};
#pragma endregion
#pragma region Metodos
void Camera::ZoomCamera(GLFWwindow* window, double xoffset, double yoffset)
{
	// Se faz zoom in
	if (yoffset == 1) {
		// Incremento no zoom, varia com a dist�ncia da c�mara
		ZOOM -= fabs(ZOOM) * 0.1f;
		
	}
	// Sen�o, se faz zoom out
	else if (yoffset == -1) {
		// Incremento no zoom, varia com a dist�ncia da c�mara
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
		vec3(Position.x, Position.y, Position.z + ZOOM),	// Posi��o da c�mara no mundo
		vec3(Direction.x, Direction.y, Direction.z),	// Dire��o para a qual a c�mara esta apontada
		vec3(0.0f, 1.0f, 0.0f)		// Vector vertical
	);
}
void Camera::UpdateCamera(float deltaTime)
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
