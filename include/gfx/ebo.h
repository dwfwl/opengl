#ifndef ELEMENT_BUFFER_OBJECT
#define ELEMENT_BUFFER_OBJECT

#include "setup.h"

struct EBO
{
	unsigned int handle;
};

void ebo_create(EBO& self)
{
	glGenBuffers(1, &self.handle);
}

void ebo_bind(EBO& self)
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, self.handle);
}

void ebo_buffer(EBO& self, unsigned int* data, size_t size)
{
	ebo_bind(self);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}

void ebo_unbind(EBO& self)
{
	glBindBuffer(0, self.handle);
}

void ebo_delete(EBO& self)
{
	glDeleteBuffers(1, &self.handle);
}

#endif//ELEMENT_BUFFER_OBJECT