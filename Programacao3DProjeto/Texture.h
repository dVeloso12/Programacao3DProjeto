#pragma once

#include "Shader.h"

class Texture {
private:
	unsigned int _textureId;
	unsigned char* _data;
	int _width, _height, _bpp;

public:
	Texture(const std::string& fileName);
	~Texture();

	void Send(Rendering::Shader* shader);
};