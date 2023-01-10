#pragma once
#include <string>
#include <vector>
#include <GL\glew.h>

class TextureManager
{
public:
	TextureManager();
	~TextureManager();

	unsigned int CubeMapLoader(std::vector<std::string> faces);
	void BindTexture(unsigned int obj); // bind upto 32 textures
	void TextureLoader(const std::string& filename);

private:

	GLuint textureManager;
	unsigned int textureID;

};

