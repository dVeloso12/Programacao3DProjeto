#include "Camera.h"

#pragma region Contrutor
Camera::Camera(float Fov,int width,int height,float near,float far)
{
	Projection = perspective(radians(Fov), float(width) / float(height), near, far);
	ZOOM = 10.0f;
	ANGLE = 0.0f;
	WIDTH = width;
	HEIGHT = height;
	view = ViewCamera();
}
#pragma endregion
#pragma region get Variaveis
mat4 Camera :: getViewValue(){return view;}
mat4 Camera :: getProjection() { return Projection; }
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
mat4x4 Camera :: ViewCamera()
{
	return lookAt(
		vec3(0.0f, 0.0f, ZOOM),	// Posição da câmara no mundo
		vec3(0.0f, 0.0f, -1.0f),	// Direção para a qual a câmara esta apontada
		vec3(0.0f, 1.0f, 0.0f)		// Vector vertical
	);

}
mat4x4 Camera::RotateCamera(GLFWwindow* window, float deltaTime)
{
		float screenHalf = WIDTH / 2;
		double mouseX, mouseY;
		glfwGetCursorPos(window, &mouseX, &mouseY);
		const GLfloat MAX_ROTATION = glm::radians(90.0f) * deltaTime;

		if (mouseX < screenHalf / 2)
		{
			rotation = 0.7f;
			/*cout << ((screenHalf - mouseX) / screenHalf * MAX_ROTATION) << endl; */
		}
		else if(mouseX > (screenHalf + (screenHalf/2)))
		{
			rotation = -0.7f;
		}
		else
		{
			rotation = 0;
		}
		
		return rotate(view, rotation * deltaTime, vec3(0.0f, 1.0f, 0.0f));
	
}
void Camera::UpdateCamera(GLFWwindow* window,float deltaTime)
{
	if (glfwGetWindowAttrib(window, GLFW_HOVERED))
	{
		view = RotateCamera(window, deltaTime) + ViewCamera();

	}
	else
	{
		view = view;
	}
	
}
#pragma endregion
