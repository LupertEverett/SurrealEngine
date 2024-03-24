#pragma once

#include "glad/glad.h"

#include "GLObjects.h"

#include <memory>

class GLFrameBufferManager
{
public:
	GLFrameBufferManager(OpenGLRenderDevice* renderDevice);

	void CreateSceneFrameBuffer();
	void DestroySceneFrameBuffer();

	std::unique_ptr<GLFrameBuffer> SceneFrameBuffer;
private:
	OpenGLRenderDevice* renderDevice;
};