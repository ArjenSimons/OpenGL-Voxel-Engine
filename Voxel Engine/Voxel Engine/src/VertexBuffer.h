#pragma once

class VertexBuffer {
private:
	unsigned int rendererId;
public:
	VertexBuffer(const void* data, unsigned int size);
	~VertexBuffer();
	
	void Bind();
	void Unbind();
};