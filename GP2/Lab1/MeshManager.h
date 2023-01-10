#pragma once
#include <glm\glm.hpp>
#include <GL\glew.h>
#include <string>
#include "obj_loader.h"
#include "CollisonDetection.h"

struct Vertex
{
public:
	Vertex(const glm::vec3& pos, const glm::vec2& texCoord)
	{
		this->pos = pos;
		this->texCoord = texCoord;
		this->normal = normal;
	}

	glm::vec3* GetPos() { return &pos; }
	glm::vec2* GetTexCoord() { return &texCoord; }
	glm::vec3* GetNormal() { return &normal; }

private:
	glm::vec3 pos;
	glm::vec2 texCoord;
	glm::vec3 normal;
};

struct Sphere
{
public:

	Sphere() {}

	glm::vec3 GetPos() { return pos; }
	float GetRadius() { return radius; }

	void SetPos(glm::vec3 pos)
	{
		this->pos = pos;
	}

	void SetRadius(float radius)
	{
		this->radius = radius;
	}


private:
	glm::vec3 pos;
	float radius;
};

class MeshManager
{
public:
	MeshManager();
	~MeshManager();


	void Draw();
	void Intitalize(Vertex* vertices, unsigned int verticesCount, unsigned int* indices, unsigned int indicesCount);
	void ModelLoader(const std::string& filename);
	void IntitalizeModel(const IndexedModel& model);
	void updateSphereData(glm::vec3 pos, float radius);
	glm::vec3 getSpherePos() { return meshSphere.GetPos(); }
	float getSphereRadius() { return meshSphere.GetRadius(); }

private:

	enum
	{
		VB_POS,
		VB_TEXTURECOORDS,
		VB_NORMAL,
		VB_INDEX,
		NUM_OF_BUFFERS
	};

	//CollisonDetection col;

	Sphere meshSphere;
	GLuint VAObject;
	GLuint VABuffer[NUM_OF_BUFFERS]; // create our array of buffers
	unsigned int drawCounter; //how much of the VAObject do we want to draw
};