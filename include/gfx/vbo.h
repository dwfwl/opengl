#ifndef VERTEX_BUFFER_OBJECT
#define VERTEX_BUFFER_OBJECT

#include "setup.h"

struct VBO
{
	unsigned int handle;
};

void vbo_create(VBO& self)
{
	glGenBuffers(1, &self.handle);
}

void vbo_bind(VBO& self, GLfloat* data, size_t size)
{
	glBindBuffer(GL_ARRAY_BUFFER, self.handle);
	glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}

void vbo_delete(VBO& self)
{
	glDeleteBuffers(1, &self.handle);
}

void vbo_unbind(VBO& self)
{
	glBindBuffer(NULL, self.handle);
}

#endif//VERTEX_BUFFER_OBJECT