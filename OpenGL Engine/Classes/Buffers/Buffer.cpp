#include "Buffer.h"

Buffer::Buffer(GLfloat* data, GLsizei count, GLsizei componentCount) : componentCount(componentCount) {
	glGenBuffers(1, &bufferID);
	Bind();
	glBufferData(GL_ARRAY_BUFFER, count * sizeof(GLfloat), data, GL_STATIC_DRAW);
	Unbind();
}
Buffer::Buffer(const std::vector<Vector2>& data) : componentCount(2) {
	glGenBuffers(1, &bufferID);
	Bind();
	glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(Vector2), &data[0], GL_STATIC_DRAW);
	Unbind();
}
Buffer::Buffer(const std::vector<Vector3>& data) : componentCount(3) {
	glGenBuffers(1, &bufferID);
	Bind();
	glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(Vector3), &data[0], GL_STATIC_DRAW);
	Unbind();
}
Buffer::Buffer(const std::vector<Vector4>& data) : componentCount(4) {
	glGenBuffers(1, &bufferID);
	Bind();
	glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(Vector4), &data[0], GL_STATIC_DRAW);
	Unbind();
}
Buffer::~Buffer() {
	glDeleteBuffers(1, &bufferID);
}

void Buffer::Bind() {
	glBindBuffer(GL_ARRAY_BUFFER, bufferID);
}

void Buffer::Unbind() {
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

GLsizei Buffer::GetComponentCount() {
	return componentCount;
}