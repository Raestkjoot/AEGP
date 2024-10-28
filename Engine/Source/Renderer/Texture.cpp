#include "Texture.h"

#include "Renderer/Renderer.h"
#include "Logger.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

Texture::Texture() {
	glGenTextures(1, &_id);
}

void Texture::Load(const char* filepath) {
	glBindTexture(GL_TEXTURE_2D, _id); // all upcoming GL_TEXTURE_2D operations now have effect on this texture object
	// set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// load image, create texture and generate mipmaps
	int width, height, nrChannels;
	stbi_set_flip_vertically_on_load(true);
	unsigned char* data = stbi_load(filepath, &width, &height, &nrChannels, 0);
	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else {
		Logger::PrintError("Failed to load texture");
	}
	stbi_image_free(data);
}

void Texture::Use() {
	glBindTexture(GL_TEXTURE_2D, _id);
}

unsigned int Texture::GetID() const {
	return _id;
}
