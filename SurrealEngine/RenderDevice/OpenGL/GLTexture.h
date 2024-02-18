#pragma once

#include "RenderDevice/RenderDevice.h"

#include "glad/glad.h"

// An OpenGL representation of an UTexture
class GLTexture
{
public:
	GLTexture();
	~GLTexture();

	void Bind();
	void Unbind();

	void Generate(FTextureInfo* info);

	static GLuint TextureFormatToGL(TextureFormat format);
private:
	GLuint textureID;
};