#pragma once

#include "RenderDevice/RenderDevice.h"
#include "GLTexture.h"

#include "glad/glad.h"

#include <unordered_map>

class GLTextureManager
{
public:
	~GLTextureManager();
	void ClearTextures();
	GLTexture GetTexture(FTextureInfo* info);
private:
	std::unordered_map<FTextureInfo*, GLTexture> Textures;
};