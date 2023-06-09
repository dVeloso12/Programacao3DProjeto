#include "World.h"

#include <glm/glm.hpp>


using namespace std;
using namespace glm;

World::World(Camera* camera)
{
	if (camera == NULL) return;
	mainCamera = camera;
	allCameras.push_back(mainCamera);
	gameObjCoutnt = 0;

}

void World::AddCameraToList(Camera* camera)
{
	if (camera == NULL) return;
	if (!camera) return;

	allCameras.push_back(camera);
	if (!mainCamera)
	{
		mainCamera = camera;
	}
}
void World::SetMainCamera(Camera* camera)
{
	if (camera == NULL) return;
	if (!camera) return;

	allCameras.push_back(camera);
	if (find(allCameras.begin(),allCameras.end(),camera) == allCameras.end())
	{
		allCameras.push_back(camera);
	}
	mainCamera = camera;
}
void World::DisplayWorld(float deltaTime)
{
	setParalelepipedo(deltaTime);
	setAllGameObjects(deltaTime);
}

void World::SaveInWorld(Paralelepipedo* savaParale)
{
	paralelepipedo = savaParale;

}
void World::SaveInWorld(GameObject* obj, int index)
{
	allGameObjectsInWorld[index] = obj;
	gameObjCoutnt = gameObjCoutnt + 1;

}

void World::setParalelepipedo(float deltaTime)
{
	float screenHeightHalf = mainCamera->getHeight() / 2;
	float screenWidthHalf = mainCamera->getWidth() / 2;
	double mouseX, mouseY;
	glfwGetCursorPos(mainCamera->getWindow(), &mouseX, &mouseY);
	const GLfloat MAX_ROTATION = glm::radians(90.0f) * deltaTime;

	float rotateValue = 0.001f;
	if (mouseX < screenWidthHalf / 2)
	{
		paralelepipedo->Rotate(rotateValue, vec3(0.0f, 1.0f, 0.0f));
	}
	else if (mouseX > (screenWidthHalf + (screenWidthHalf / 2)))
	{
		paralelepipedo->Rotate(-rotateValue, vec3(0.0f, 1.0f, 0.0f));

	}
	if (mouseY < screenHeightHalf / 2)
	{
		paralelepipedo->Rotate(rotateValue, vec3(1.0f, 0.0f, 0.0f));

	}
	else if(mouseY > (screenHeightHalf + (screenHeightHalf / 2)))
	{
		paralelepipedo->Rotate(-rotateValue, vec3(1.0f, 0.0f, 0.0f));

	}
	// MVP
	mat4 mvpParalelipedo = mainCamera->getProjection() * mainCamera->getViewValue() * paralelepipedo->getModel();

	//mostrar paralelepipedo
	paralelepipedo->displayModel(paralelepipedo->vertex, mvpParalelipedo);
}
void World::setAllGameObjects(float deltaTime)
{
	if (allGameObjectsInWorld != NULL)
	{
		for (int i = 1; i <= gameObjCoutnt; i++)
		{
			allGameObjectsInWorld[i - 1]->DisplayGameObject(mainCamera->getViewValue(), mainCamera->getProjection());
		}
	}
}
