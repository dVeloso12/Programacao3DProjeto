#include "World.h"

#include <glm/glm.hpp>


using namespace std;
using namespace glm;

World::World(Camera* camera)
{
	if (camera == NULL) return;
	mainCamera = camera;
	allCameras.push_back(mainCamera);
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
