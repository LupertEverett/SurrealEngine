
#include "Precomp.h"
#include "RenderDevice.h"
#include "Vulkan/VulkanRenderDevice.h"
#include "OpenGL/OpenGLRenderDevice.h"

std::unique_ptr<RenderDevice> RenderDevice::Create(GameWindow* viewport, std::shared_ptr<VulkanSurface> surface)
{
	return std::make_unique<VulkanRenderDevice>(viewport, surface);
}

std::unique_ptr<RenderDevice> RenderDevice::CreateOpenGLRenderDevice(GameWindow* viewport)
{
	return std::make_unique<OpenGLRenderDevice>(viewport);
}
