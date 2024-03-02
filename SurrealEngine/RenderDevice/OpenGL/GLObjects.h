#pragma once

#include <vector>
#include <memory>

#include "glad/glad.h"

#include "SceneData.h"

class GLVertexBuffer
{
public:
	GLVertexBuffer();
	~GLVertexBuffer();

	void Bind();
	void Unbind();

	void LoadBufferData(const std::vector<SceneVertex>& vertices);

private:
	GLuint vertexBufferID;
};

class GLVertexArray
{
public:
	GLVertexArray();
	~GLVertexArray();

	void Bind();
	void Unbind();

	void LoadVertexData(const std::vector<SceneVertex>& vertices);

private:
	void CreateVertexArrayAttribs();
	GLuint vertexArrayID;
	std::unique_ptr<GLVertexBuffer> vertexBufferObject;
};

class GLIndexBuffer
{
public:
	GLIndexBuffer();
	~GLIndexBuffer();

	void Bind();
	void Unbind();

	void LoadIndicesData(const std::vector<unsigned int>& indices);
	size_t IndicesCount() { return indices.size(); }

private:
	GLuint IndexArrayID;
	std::vector<unsigned int> indices;
};
