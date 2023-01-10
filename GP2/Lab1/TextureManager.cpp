#include "TextureManager.h"
#include "stb_image.h"
#include <cassert>
#include <iostream>

TextureManager::TextureManager()
{
}

TextureManager::~TextureManager()
{
	glDeleteTextures(1, &textureManager); // number of and address of textures
}

void TextureManager::BindTexture(unsigned int obj)
{
	assert(obj >= 0 && obj <= 31); /// check we are working with one of the 32 textures

	glActiveTexture(GL_TEXTURE0 + obj); //set acitve texture unit
	glBindTexture(GL_TEXTURE_2D, textureManager); //type of and texture to bind to unit
}

void TextureManager::TextureLoader(const std::string& filename)
{
	int X, Y, componentCount; //width, height, and no of components of image
	unsigned char* imageData = stbi_load((filename).c_str(), &X, &Y, &componentCount, 4); //load the image and store the data

	if (imageData == NULL)
	{
		std::cerr << "texture load failed" << filename << std::endl;
	}

	glGenTextures(1, &textureID); // number of and address of textures
	glBindTexture(GL_TEXTURE_CUBE_MAP, textureID); //bind texture - define type 


	glGenTextures(1, &textureManager); // number of and address of textures
	glBindTexture(GL_TEXTURE_2D, textureManager); //bind texture - define type 

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // wrap texture outside width
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); // wrap texture outside height

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); // linear filtering for minification (texture is smaller than area)
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); // linear filtering for magnifcation (texture is larger)

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, X, Y, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageData); //Target, Mipmapping Level, Pixel Format, Width, Height, Border Size, Input Format, Data Type of Texture, Image Data

	stbi_image_free(imageData);
}