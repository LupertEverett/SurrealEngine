#pragma once

#include "RenderDevice/RenderDevice.h"
#include "GLTexture.h"

#include "GLAD/glad.h"

#include <unordered_map>

class TextureManager
{
public:
	void LoadTexture(FTextureInfo* info);
	GLTexture GetTexture(FTextureInfo* info);
private:
	std::unordered_map<FTextureInfo*, GLTexture> Textures;
};