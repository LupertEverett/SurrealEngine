#include "GLShader.h"

#include <stdexcept>

GLShader::GLShader() : ProgramID(0)
{
}

GLShader::~GLShader()
{
	glDeleteProgram(ProgramID);
}

void GLShader::Bind()
{
	glUseProgram(ProgramID);
}

void GLShader::Unbind()
{
	glUseProgram(0);
}

void GLShader::Compile(const char* vertexCode, const char* fragmentCode, const char* geometryCode)
{
	GLuint VertexShaderID, FragmentShaderID, GeometryShaderID;

	VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(VertexShaderID, 1, &vertexCode, NULL);
	CheckCompileErrors(VertexShaderID, "Vertex");

	FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(FragmentShaderID, 1, &fragmentCode, NULL);
	CheckCompileErrors(FragmentShaderID, "Fragment");

	if (geometryCode)
	{
		GeometryShaderID = glCreateShader(GL_GEOMETRY_SHADER);
		glShaderSource(GeometryShaderID, 1, &geometryCode, NULL);
		CheckCompileErrors(GeometryShaderID, "Geometry");
	}

	ProgramID = glCreateProgram();
	glAttachShader(ProgramID, VertexShaderID);
	glAttachShader(ProgramID, FragmentShaderID);
	if (geometryCode)
		glAttachShader(ProgramID, GeometryShaderID);
	glLinkProgram(ProgramID);
	CheckLinkErrors();

	// Shaders can be freely deleted now
	glDeleteShader(VertexShaderID);
	glDeleteShader(FragmentShaderID);
	if (geometryCode)
		glDeleteShader(GeometryShaderID);
}

void GLShader::SetUniformMat4(const std::string& uniformName, mat4 value)
{
	GLint uniformLocation = glGetUniformLocation(ProgramID, uniformName.c_str());

	if (uniformLocation == -1)
		throw std::runtime_error(uniformName + " is not a valid Matrix4x4 uniform for the shader!");

	glUniformMatrix4fv(uniformLocation, 1, GL_FALSE, value.matrix);
}

void GLShader::SetUniformSampler2D(const std::string& uniformName, const int GLTextureSlot)
{
	GLint uniformLocation = glGetUniformLocation(ProgramID, uniformName.c_str());

	if (uniformLocation == -1)
		throw std::runtime_error(uniformName + " is not a valid Sampler2D uniform for the shader!");

	glUniform1i(uniformLocation, GLTextureSlot);
}

void GLShader::CheckCompileErrors(GLuint Object, const std::string ObjectType) const
{
	GLint success;
	GLchar infoLog[1024];

	glGetShaderiv(Object, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		glGetShaderInfoLog(Object, 1024, NULL, infoLog);

		throw std::runtime_error("Error while compiling " + ObjectType + " shader: " + infoLog);
	}
}

void GLShader::CheckLinkErrors() const
{
	GLint success;
	GLchar infoLog[1024];

	glGetProgramiv(ProgramID, GL_LINK_STATUS, &success);

	if (!success)
	{
		glGetProgramInfoLog(ProgramID, 1024, NULL, infoLog);

		throw std::runtime_error("Error while linking shader: " + std::string(infoLog));
	}
}