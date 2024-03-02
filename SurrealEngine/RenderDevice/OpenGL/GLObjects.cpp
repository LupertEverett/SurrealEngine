#include "GLObjects.h"

GLVertexArray::GLVertexArray()
{
	glGenVertexArrays(1, &vertexArrayID);
}

GLVertexArray::~GLVertexArray()
{
	glDeleteVertexArrays(1, &vertexArrayID);
}

void GLVertexArray::Bind()
{
	glBindVertexArray(vertexArrayID);
}

void GLVertexArray::Unbind()
{
	glBindVertexArray(NULL);
}

void GLVertexArray::LoadVertexData(const std::vector<SceneVertex>& vertices)
{
	Bind();
	
	vertexBufferObject = std::make_unique<GLVertexBuffer>();

	vertexBufferObject->LoadBufferData(vertices);

	CreateVertexArrayAttribs();

	Unbind();
}

void GLVertexArray::CreateVertexArrayAttribs()
{
	vertexBufferObject->Bind();

	// Layout follows the SceneVertex struct
	// uint32_t Flags
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 1, GL_UNSIGNED_INT, GL_FALSE, sizeof(uint32_t), (GLvoid*)offsetof(SceneVertex, Flags));

	// vec3 Position
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(vec3), (GLvoid*)offsetof(SceneVertex, Position));

	// vec2 TexCoord
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(vec2), (GLvoid*)offsetof(SceneVertex, TexCoord));

	// vec2 TexCoord2
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, sizeof(vec2), (GLvoid*)offsetof(SceneVertex, TexCoord2));

	// vec2 TexCoord3
	glEnableVertexAttribArray(4);
	glVertexAttribPointer(4, 2, GL_FLOAT, GL_FALSE, sizeof(vec2), (GLvoid*)offsetof(SceneVertex, TexCoord3));

	// vec2 TexCoord4
	glEnableVertexAttribArray(5);
	glVertexAttribPointer(5, 2, GL_FLOAT, GL_FALSE, sizeof(vec2), (GLvoid*)offsetof(SceneVertex, TexCoord4));

	// vec4 Color
	glEnableVertexAttribArray(6);
	glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, sizeof(vec4), (GLvoid*)offsetof(SceneVertex, Color));

	// ivec4 TextureBinds
	glEnableVertexAttribArray(7);
	glVertexAttribPointer(7, 4, GL_INT, GL_FALSE, sizeof(ivec4), (GLvoid*)offsetof(SceneVertex, TextureBinds));

	vertexBufferObject->Unbind();
}

//=================================================

GLVertexBuffer::GLVertexBuffer()
{
	glGenBuffers(1, &vertexBufferID);
}

GLVertexBuffer::~GLVertexBuffer()
{
	glDeleteBuffers(1, &vertexBufferID);
}

void GLVertexBuffer::Bind()
{
	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID);
}

void GLVertexBuffer::Unbind()
{
	glBindBuffer(GL_ARRAY_BUFFER, NULL);
}

void GLVertexBuffer::LoadBufferData(const std::vector<SceneVertex>& vertices)
{
	Bind();

	glBufferData(GL_ARRAY_BUFFER, sizeof(SceneVertex) * vertices.size(), vertices.data(), GL_DYNAMIC_DRAW);

	Unbind();
}

//=================================================

GLIndexBuffer::GLIndexBuffer()
{
	glGenBuffers(1, &IndexArrayID);
}

GLIndexBuffer::~GLIndexBuffer()
{
	indices.clear();
	glDeleteBuffers(1, &IndexArrayID);
}

void GLIndexBuffer::Bind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IndexArrayID);
}

void GLIndexBuffer::Unbind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, NULL);
}

void GLIndexBuffer::LoadIndicesData(const std::vector<unsigned int>& indices)
{
	Bind();

	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size(), indices.data(), GL_DYNAMIC_DRAW);

	Unbind();

	this->indices = indices;
}
