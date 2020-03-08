#include "VertexBuffer.h"
#include "GL/glew.h"

VertexBuffer::VertexBuffer(const void * data, unsigned int size)
{
	glGenBuffers(1, &rendererId);
	glBindBuffer(GL_ARRAY_BUFFER, rendererId);
	glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}

VertexBuffer::~VertexBuffer()
{
	glDeleteBuffers(1, &rendererId);
}

void VertexBuffer::Bind()
{
	glBindBuffer(GL_ARRAY_BUFFER, rendererId);
}

void VertexBuffer::Unbind()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
