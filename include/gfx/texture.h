#ifndef TEXTURE_HEADER
#define TEXTURE_HEADER

#include "setup.h"

struct Texture
{
	unsigned int handle;
	unsigned char* data;
};

void texture_create(Texture& self, const char* file)
{
	int width, height, nrChannels;
	self.data = stbi_load(file, &width, &height, &nrChannels, 0);

	glGenTextures(1, &self.handle);
	glBindTexture(GL_TEXTURE_2D, self.handle);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	if (!self.data)
	{
		std::cout << "TEXTURE ERR :: include/gfx/texture.h\nFailed to load image to `data`" << std::endl;
	}
	else
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, self.data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	stbi_image_free(self.data);
}

void texture_bind(Texture& self)
{
	glBindTexture(GL_TEXTURE_2D, self.handle);
}

void texture_unbind(Texture& self)
{
	glBindTexture(0, self.handle);
}

void texture_delete(Texture& self)
{
	glDeleteTextures(1, &self.handle);
}

#endif//TEXTURE_HEADER