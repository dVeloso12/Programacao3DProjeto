#include <iostream>
#include "Paralelepipedo.h"
#include <glm/gtc/type_ptr.hpp> // value_ptr



Paralelepipedo :: Paralelepipedo(float xLenght,float yLenght,float zLenght)
{
	vertex = getVertex(xLenght,yLenght,zLenght);
	Model = mat4(1.0f);
}
Paralelepipedo::Paralelepipedo()
{
	
}
vector<vec3> Paralelepipedo :: getVertex(float xLenght,float yLenght,float zLenght)
{
	// 6 faces * 4 vértices por face
	vec3 point[6 * 4] = {
		 // Face frontal
	vec3(-xLenght, -yLenght,  zLenght),
	vec3(xLenght, -yLenght,  zLenght),
	vec3(xLenght,  yLenght,  zLenght),
	vec3(-xLenght,  yLenght,  zLenght),
	// Face traseira
	vec3(-xLenght, -yLenght, -zLenght),
	vec3(-xLenght,  yLenght, -zLenght),
	vec3(xLenght,  yLenght, -zLenght),
	vec3(xLenght, -yLenght, -zLenght),
	// Face direita
	vec3(xLenght, -yLenght,  zLenght),
	vec3(xLenght, -yLenght, -zLenght),
	vec3(xLenght,  yLenght, -zLenght),
	vec3(xLenght,  yLenght,  zLenght),
	// Face esquerda
	vec3(-xLenght, -yLenght,  zLenght),
	vec3(-xLenght,  yLenght,  zLenght),
	vec3(-xLenght,  yLenght, -zLenght),
	vec3(-xLenght, -yLenght, -zLenght),
	// Face superior
	vec3(-xLenght,  yLenght,  zLenght),
	vec3(xLenght,  yLenght,  zLenght),
	vec3(xLenght,  yLenght, -zLenght),
	vec3(-xLenght,  yLenght, -zLenght),
	// Face inferior
	vec3(-xLenght, -yLenght,  zLenght),
	vec3(-xLenght, -yLenght, -zLenght),
	vec3(xLenght, -yLenght, -zLenght),
	vec3(xLenght, -yLenght,  zLenght)
	};

	vector<vec3> ret;
	for (auto i : point)
		ret.push_back(i);

	return ret;
}
mat4 Paralelepipedo::getModel()
{
	return Model;
}
void Paralelepipedo::displayModel(vector<vec3> vertex, mat4 mvp)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	float* vertex_stream = static_cast<float*>(value_ptr(vertex.front()));
	
	std::vector<glm::vec3> colors{
		glm::vec3(1.0f, 0.0f, 0.0f), // Red
		glm::vec3(1.0f, 1.0f, 0.0f), // Yellow
		glm::vec3(0.0f, 1.0f, 0.0f), // Green
		glm::vec3(0.0f, 1.0f, 1.0f), // Cyan
		glm::vec3(0.0f, 0.0f, 1.0f), // Blue
		glm::vec3(1.0f, 0.0f, 1.0f)  // Magenta
	};

	// Desenha quad em modo imediato
	glBegin(GL_QUADS);
	/* obj.size() * (obj.front().length()) é o mesmo que (6*4)*3 */
	/* 6 faces * 4 vértices por face * 3 coordenadas por vértice */
	for (int nv = 0; nv < 6 * 4 * 3; nv += 3) {
		// Uma cor por face
		glColor3f(colors[nv / (4 * 3)].r, colors[nv / (4 * 3)].g, colors[nv / (4 * 3)].b);
		glm::vec4 vertex = glm::vec4(vertex_stream[nv], vertex_stream[nv + 1], vertex_stream[nv + 2], 1.0f);
		// Cálculo das coordenadas de recorte
		glm::vec4 transformed_vertex = mvp * vertex;
		// Divisão de Perspetiva
		glm::vec4 normalized_vertex = transformed_vertex / transformed_vertex.w;
		// Desenho do vértice
		glVertex3f(normalized_vertex.x, normalized_vertex.y, normalized_vertex.z);
	}
	glEnd();
}
void Paralelepipedo::Rotate(float value,vec3 direction)
{
	//Model = rotate(Model, value, normalize(vec3(0.0f, 1.0f, 0.0f)));
	//Model = rotate(Model, value, normalize(vec3(1.0f, 0.0f, 0.0f)));

	Model = rotate(Model, value, normalize(direction));

}
