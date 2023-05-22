#define GLEW_STATIC
#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <iostream>
#include <cmath>

#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective

#include "Camera.h"
#include "Paralelepipedo.h"
#include "Read_Model.h"


#pragma comment (lib,"glew32s.lib")
#pragma comment (lib,"glfw3.lib")
#pragma comment (lib,"opengl32.lib")

using namespace std;
using namespace glm;


float deltaTime;
float prevTime = 0;
int Width = 800, Height = 800;

//Variaveis
Camera* mainCam;

void scrollCallback(GLFWwindow* window, double xoffset, double yoffset) {

	mainCam->ZoomCamera(window, xoffset, yoffset);
}


int main(void)
{
	glewInit();
	Paralelepipedo* paralelepipedo = new Paralelepipedo(2.0f,0.5f,1.0f);

	//iniciar a janela 
	if (!glfwInit()) return -1;

	GLFWwindow* window = glfwCreateWindow(Width, Height, "Programacao3D_Projeto", NULL, NULL); //Criar janela

	if (window == NULL) //verificar se criou a janela, senao criar fecha o programa
	{
		cout << "Error to create Window" << endl;
		glfwTerminate();//fechar a janela
		return -1;
	}
	glfwMakeContextCurrent(window);//para poder usar a janela
	
	glClearColor(0.07f, 0.13f, 0.17f, 1.0f);




	glEnable(GL_DEPTH_TEST);
	// Descomentar para ativar o Face Culling
	glEnable(GL_CULL_FACE);


	mainCam = new Camera(45.0f, Width, Height, 0.1, 100); //criar camera
	
	glfwSetScrollCallback(window, scrollCallback);

	Models::Model* ball = new Models::Model();
	ball->Read("PoolBalls/Ball1.obj");
	
	while (!glfwWindowShouldClose(window)) //ir� fechar a janela, caso se clique no botao de X na janela
	{	
		// Updating delta time
		double time = glfwGetTime();
		deltaTime = time - prevTime;
		prevTime = time;

		mainCam->UpdateCamera(window,deltaTime);

		// MVP
		mat4 mvp = mainCam->getProjection() * mainCam->getViewValue() * paralelepipedo->getModel();

		//mostrar paralelepipedo
		paralelepipedo->displayModel(paralelepipedo->vertex, mvp);


		glfwSwapBuffers(window);
		//cuida de todos os GLFW events
		glfwPollEvents();
	}

	glfwDestroyWindow(window);//destruir a janela
	glfwTerminate();//fechar a janela

	return 0;
}

