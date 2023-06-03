#include "GameObject.h"

using namespace std;
using namespace glm;

GameObject::GameObject() {};

GameObject::GameObject(Models :: Model* _model) {
	 model = _model;
};

void GameObject::SetModel(Models :: Model* _model)
{
	model = _model;
}

void GameObject::DisplayGameObject(mat4 view, mat4 projection)
{
	mat4 newmodel = mat4(1.0f);

	newmodel = scale(newmodel, _scale);

	newmodel = rotate(newmodel, _rotation.x, glm::vec3(1.0f, 0.0f, 0.0f));
	newmodel = rotate(newmodel, _rotation.y, glm::vec3(0.0f, 1.0f, 0.0f));
	newmodel = rotate(newmodel, _rotation.z, glm::vec3(0.0f, 0.0f, 1.0f));

	newmodel = translate(newmodel, _position);
	
	model->DrawModel(newmodel, view, projection);

}

