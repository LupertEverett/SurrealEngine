#include "GLShaderManager.h"

#include "GLShaderDefinitions.h"

GLShaderManager::GLShaderManager()
{
	sceneShader = std::make_unique<GLShader>();

	LoadShaderCode(vertexShaderCode, fragmentShaderCode);
}

void GLShaderManager::LoadShaderCode(const std::string& vertexShaderCode, const std::string& fragmentShaderCode)
{
	sceneShader->Compile(vertexShaderCode.c_str(), fragmentShaderCode.c_str());

	// Set the common Uniforms
	sceneShader->SetUniformSampler2D("tex", TEXTURE_LAYOUT_LOCATION);
	sceneShader->SetUniformSampler2D("texLightmap", TEXTURE_LIGHTMAP_LAYOUT_LOCATION);
	sceneShader->SetUniformSampler2D("texMacro", TEXTURE_MACRO_LAYOUT_LOCATION);
	sceneShader->SetUniformSampler2D("texDetail", TEXTURE_DETAIL_LAYOUT_LOCATION);
}