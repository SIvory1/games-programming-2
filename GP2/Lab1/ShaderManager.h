#pragma once
#include <string>
#include <GL\glew.h>
#include "transform.h"
#include "MainCamera.h"

class ShaderManager
{
public:
	ShaderManager();
	~ShaderManager();

	void Bind(); //Set gpu to use our shaders
	void UpdateShader(const Transform& transform, const MainCamera& cam);
	void UpdateCubemap(const MainCamera& cam);
	void InitalizeShader(const std::string& filename);
	void UpdateReflections(const Transform& transform, const MainCamera& cam);

	std::string ShaderManager::ShaderLoader(const std::string& fileName);
	void ShaderManager::CheckShaderError(GLuint shader, GLuint flag, bool programOn, const std::string& errorMessage);
	GLuint ShaderManager::CreateShader(const std::string& text, unsigned int type);

private:
	static const unsigned int NUM_OF_SHADERS = 2; // number of shaders

	enum
	{
		TRANSFORM_U,
		VIEWMATRIX_U,
		PROJECTION_U,
		MODEL_U,
		CAMERAPOS_U,
		NUM_OF_UNIFORMS
	};

	GLuint program; // Track the shader program
	GLuint shaders[NUM_OF_SHADERS]; //array of shaders
	GLuint uniforms[NUM_OF_UNIFORMS]; //no of uniform variables
};
