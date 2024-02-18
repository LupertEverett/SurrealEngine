#include "OpenGLRenderDevice.h"
#include "Window/Window.h"

#include "GLTexture.h"

#include <stdexcept>

// TODO: Implement the OpenGL renderer :V

OpenGLRenderDevice::OpenGLRenderDevice(GameWindow* InWindow)
{
	Viewport = InWindow;

	if (!gladLoadGLLoader(GetProcAddress(InWindow)))
		throw std::runtime_error("Unable to load the Proc addresses.");
}

OpenGLRenderDevice::~OpenGLRenderDevice()
{
}

void OpenGLRenderDevice::Flush(bool AllowPrecache)
{

}

bool OpenGLRenderDevice::Exec(std::string Cmd, OutputDevice& Ar)
{
	return false;
}

void OpenGLRenderDevice::Lock(vec4 FlashScale, vec4 FlashFog, vec4 ScreenClear)
{

}

void OpenGLRenderDevice::Unlock(bool Blit)
{

}

void OpenGLRenderDevice::DrawComplexSurface(FSceneNode* Frame, FSurfaceInfo& Surface, FSurfaceFacet& Facet)
{

}

void OpenGLRenderDevice::DrawGouraudPolygon(FSceneNode* Frame, FTextureInfo& Info, const GouraudVertex* Pts, int NumPts, uint32_t PolyFlags)
{

}

void OpenGLRenderDevice::DrawTile(FSceneNode* Frame, FTextureInfo& Info,
			  float X, float Y, float XL, float YL, 
			  float U, float V, float UL, float VL, float Z, 
			  vec4 Color, vec4 Fog, uint32_t PolyFlags)
{

}

void OpenGLRenderDevice::Draw3DLine(FSceneNode* Frame, vec4 Color, vec3 P1, vec3 P2)
{

}

void OpenGLRenderDevice::Draw2DLine(FSceneNode* Frame, vec4 Color, vec3 P1, vec3 P2)
{

}

void OpenGLRenderDevice::Draw2DPoint(FSceneNode* Frame, vec4 Color, float X1, float Y1, float X2, float Y2, float Z)
{

}

void OpenGLRenderDevice::ClearZ(FSceneNode* Frame)
{
	// Following what the Vulkan driver did, seems like it disregards the Frame parameter
	// and just draws the scene then clears the depth buffer
	DrawScene();

	glClearDepth(1.0f);
	glClear(GL_DEPTH_BUFFER_BIT);
}

void OpenGLRenderDevice::ReadPixels(FColor* Pixels)
{

}

void OpenGLRenderDevice::EndFlash()
{

}

void OpenGLRenderDevice::SetSceneNode(FSceneNode* Frame)
{

}

void OpenGLRenderDevice::PrecacheTexture(FTextureInfo& Info, uint32_t PolyFlags)
{

}

bool OpenGLRenderDevice::SupportsTextureFormat(TextureFormat Format)
{
	return GLTexture::TextureFormatToGL(Format) != 0;
}

void OpenGLRenderDevice::UpdateTextureRect(FTextureInfo& Info, int U, int V, int UL, int VL)
{

}

void OpenGLRenderDevice::DrawScene()
{
	// Following what the Vulkan driver does:
	// Draw*() functions actually add vertices/colors/indexes to the scene
	// Then DrawScene() (DrawBatch() in VulkanRenderDevice) handles the actual drawing
	// TODO: Actually do that :V
}

GLADloadproc OpenGLRenderDevice::GetProcAddress(GameWindow* InWindow)
{
	return (GLADloadproc)InWindow->OpenGL_GetProcAddress();
}
