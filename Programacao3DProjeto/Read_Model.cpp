#include <iostream>
#include <fstream>
#include <sstream>
#include <GL/glew.h>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_inverse.hpp>

#include "Read_Model.h"
#include "Read_MTL.h"

namespace Models {
	
	void Model::SetShader(Shader* shader) {
		_shader = shader;
	}

	Shader* Model::GetShader() {
		return _shader;
	}

	void Model::Read(const std::string& fileName) {
		std::ifstream inFile(fileName);

		if (!inFile.is_open()) {
			std::cerr << "Models::Model::Read: Could not open file" << std::endl;
			return;
		}

		int pos = fileName.find_last_of('/');
		std::string path = fileName.substr(0, pos + 1);

		
		std::vector<glm::vec3> tempPositions;
		std::vector<glm::vec2> tempTexCoords;
		std::vector<glm::vec3> tempNormals;

		std::vector<unsigned int> tempPosIndices;
		std::vector<unsigned int> tempTexCoordIndices;
		std::vector<unsigned int> tempNormalIndices;

		std::istringstream iss;
		std::string line;
		std::string prefix;
		glm::vec3 tempVec3;
		glm::vec2 tempVec2;
		GLint tempGLint;

		while (std::getline(inFile, line)) {
			iss.clear();
			iss.str(line);
			iss >> prefix;

			if (prefix == "v") {
				iss >> tempVec3.x >> tempVec3.y >> tempVec3.z;
				tempPositions.push_back(tempVec3);
			}
			else if (prefix == "vt") {
				iss >> tempVec2.x >> tempVec2.y;
				tempTexCoords.push_back(tempVec2);
			}
			else if (prefix == "vn") {
				iss >> tempVec3.x >> tempVec3.y >> tempVec3.z;
				tempNormals.push_back(tempVec3);
			}
			else if (prefix == "f") {
				for (int i = 0; iss >> tempGLint; )
				{
					if (i == 0) {
						tempPosIndices.push_back(tempGLint - 1);
					}
					else if (i == 1) {
						tempTexCoordIndices.push_back(tempGLint - 1);
					}
					else if (i == 2) {
						tempNormalIndices.push_back(tempGLint - 1);
					}

					if (iss.peek() == '/') {
						iss.ignore(1, '/');
						i++;
					}
					else if (iss.peek() == ' ') {
						iss.ignore(1, ' ');
						i++;
					}

					if (i > 2) {
						i = 0;
					}
				}

			}
			else if (prefix == "mtllib") {
				iss >> prefix;
				path = path + prefix;
				//_material = new Material::Read_MTL(path);   //-> dar fix a class texture
			}
		}

		_positions.resize( tempPosIndices.size());
		for (int i = 0; i < tempPosIndices.size(); i++)
		{
			_positions[i] = tempPositions[tempPosIndices[i]].x;
			_positions[i + 1] = tempPositions[tempPosIndices[i]].y;
			_positions[i + 2] = tempPositions[tempPosIndices[i]].z;
		}

		_texCoords.resize(tempTexCoordIndices.size());
		for (int i = 0; i < tempTexCoordIndices.size(); i++)
		{
			_texCoords[i] = tempTexCoords[tempTexCoordIndices[i]].x;
			_texCoords[i + 1] = tempTexCoords[tempTexCoordIndices[i]].y;
		}

		_normals.resize( tempNormalIndices.size());
		for (int i = 0; i < tempNormalIndices.size(); i++)
		{
			_normals[i] = tempNormals[tempNormalIndices[i]].x;
			_normals[i + 1] = tempNormals[tempNormalIndices[i]].y;
			_normals[i + 2] = tempNormals[tempNormalIndices[i]].z;
		}

		std::cout << "Number of vertices: " << tempPositions.size() << std::endl;
		std::cout << "Number of Normals: " << tempNormals.size() << std::endl;
		std::cout << "Number of uvs: " << tempTexCoords.size() << std::endl;
		

		Send();
	}

	void Model::DrawModel(glm::mat4 model, glm::mat4 view, glm::mat4 projection) {
		// Activate the vertex array that holds the data of this model
		glBindVertexArray(_vao);

		glm::mat4 mv = view * model;

		glm::mat4 mvp = projection * mv;

		glm::mat3 normalMatrix = glm::inverseTranspose(glm::mat3(view * model));

		

		//SEM ISTO NAO DA LOAD DO MODEL
		 
		// Updates the matrices used to draw the model in the program shader
		_shader->SetUniformMatrix4fv("uView", view);
		/*_shader->SetUniformMatrix4fv("uMV", mv);*/
		//_shader->SetUniformMatrix4fv("uMVP", mvp);
		//_shader->SetUniformMatrix3fv("uNormalMatrix", normalMatrix);

		// Draw call
		glDrawArrays(GL_TRIANGLES, 0, _positions.size() / 3);
	}

	void Model::Send() {
	
		// Create new vertex array that will hold the data of this model
		// In the GPU side
		glGenVertexArrays(1, &_vao);
		glBindVertexArray(_vao);

		// Creates and binds the needed buffers to the currently activated VAO
		// And links said buffers to the corresponding attributes of the shader program

		// Buffer that holds the positions of the vertices
		glGenBuffers(1, &_posBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, _posBuffer);
		glBufferData(GL_ARRAY_BUFFER, _positions.size() * sizeof(GL_FLOAT), &_positions[0], GL_STATIC_DRAW);

		_shader->LinkInput("vPosition", GL_FLOAT, 3);

		// Buffer that holds the texture coordinates of the vertices
		glGenBuffers(1, &_texBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, _texBuffer);
		glBufferData(GL_ARRAY_BUFFER, _texCoords.size() * sizeof(GL_FLOAT), &_texCoords[0], GL_STATIC_DRAW);

		_shader->LinkInput("vTexCoord", GL_FLOAT, 2);

		// Buffer that holds the normals of the vertices
		glGenBuffers(1, &_normalBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, _normalBuffer);
		glBufferData(GL_ARRAY_BUFFER, _normals.size() * sizeof(GL_FLOAT), &_normals[0], GL_STATIC_DRAW);

		_shader->LinkInput("vNormal", GL_FLOAT, 3);

		// Tell the material to send its data to the shader program
	/*	_material->Send(_shader);*/




	}
}