#pragma once

#include "Math/mat.h"
#include "Math/vec.h"

#include "GLAD/glad.h"


// Basically the vertex format from the Vulkan Renderer
struct SceneVertex
{
	uint32_t Flags;
	vec3 Position;
	vec2 TexCoord;
	vec2 TexCoord2;
	vec2 TexCoord3;
	vec2 TexCoord4;
	vec4 Color;
	ivec4 TextureBinds;
};

class GLShader
{
public:
	GLShader();
	~GLShader();

	void Bind();
	void Unbind();

	void Compile(const char* vertexCode, const char* fragmentCode, const char* geometryCode = nullptr);
private:
	void CheckCompileErrors(GLuint Object, const std::string ObjectType) const;
	void CheckLinkErrors() const;

	GLuint ProgramID;
};