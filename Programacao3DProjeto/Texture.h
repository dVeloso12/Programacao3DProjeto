#pragma once

#include "Shader.h"

using namespace std;

class Texture {
private:
	unsigned int _textureId;
	unsigned char* _data;
	int _width, _height, _bpp;

public:
	Texture(const string& fileName);
	~Texture();

	void Send(Shader* shader);
};
