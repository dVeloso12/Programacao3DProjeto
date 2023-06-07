#include "Texture.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

Texture::Texture(const std::string& fileName) {
	stbi_set_flip_vertically_on_load(true);
	_data = stbi_load(fileName.c_str(), &_width, &_height, &_bpp, 0);

	glGenTextures(1, &_textureId);
	glBindTexture(GL_TEXTURE_2D, _textureId);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, _width, _height, 0, _bpp == 4 ? GL_RGBA : GL_RGB, GL_UNSIGNED_BYTE, _data);

	if (_data) {
		stbi_image_free(_data);
	}
}

Texture::~Texture() {
	glDeleteTextures(1, &_textureId);
}

void Texture::Send(Rendering::Shader* shader) {
	shader->SetUniform1i("uTexSampler", 0);
}
