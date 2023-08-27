#ifndef VERTEX_ARRAY_OBJECT
#define VERTEX_ARRAY_OBJECT

#include "setup.h"

struct VAO
{
	GLuint handle;
};

void vao_create(VAO& self)
{
	glGenVertexArrays(1, &self.handle);
}

void vao_bind(VAO& self)
{
	glBindVertexArray(self.handle);
}

void vao_delete(VAO& self)
{
	glDeleteVertexArrays(1, &self.handle);
}

void vao_unbind(VAO& self)
{
	glBindVertexArray(0);
}

void vao_attr(VAO& self, GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, size_t offset)
{
	vao_bind(self);
	glVertexAttribPointer(index, size, type, normalized, stride, (void*)offset);
	glEnableVertexAttribArray(index);
	vao_unbind(self);
}

#endif//VERTEX_ARRAY_OBJECT