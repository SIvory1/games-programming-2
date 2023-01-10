#include "MeshManager.h"
#include <vector>


MeshManager::MeshManager()
{
	drawCounter = NULL;
	VAObject = NULL;
	VABuffer[NUM_OF_BUFFERS] = {};

	//meshSphere = col.
	
}

MeshManager::~MeshManager()
{
	glDeleteVertexArrays(1, &VAObject); // delete arrays
}

void MeshManager::Intitalize(Vertex* vertices, unsigned int verticesCount, unsigned int* indices, unsigned int indicesCount)
{
	IndexedModel model;

	for (unsigned int i = 0; i < verticesCount; i++)
	{
		model.positions.push_back(*vertices[i].GetPos());
		model.texCoords.push_back(*vertices[i].GetTexCoord());
		//model.normals.push_back(*vertices[i].GetNormal());
	}

	for (unsigned int i = 0; i < indicesCount; i++)
		model.indices.push_back(indices[i]);

	IntitalizeModel(model);
}

void MeshManager::IntitalizeModel(const IndexedModel& model)
{

	drawCounter = model.indices.size();

	glGenVertexArrays(1, &VAObject); //generate a vertex array and store it in the VAO
	glBindVertexArray(VAObject); //bind the VAO (any operation that works on a VAO will work on our bound VAO - binding)

	glGenBuffers(4, VABuffer); //generate our buffers based of our array of data/buffers - GLuint vertexArrayBuffers[NUM_BUFFERS];

	glBindBuffer(GL_ARRAY_BUFFER, VABuffer[0]); //tell opengl what type of data the buffer is (GL_ARRAY_BUFFER), and pass the data
	glBufferData(GL_ARRAY_BUFFER, model.positions.size() * sizeof(model.positions[0]), &model.positions[0], GL_STATIC_DRAW); //move the data to the GPU - type of data, size of data, starting address (pointer) of data, where do we store the data on the GPU (determined by type)
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, VABuffer[1]); //tell opengl what type of data the buffer is (GL_ARRAY_BUFFER), and pass the data
	glBufferData(GL_ARRAY_BUFFER, model.texCoords.size() * sizeof(model.texCoords[0]), &model.texCoords[0], GL_STATIC_DRAW); //move the data to the GPU - type of data, size of data, starting address (pointer) of data, where do we store the data on the GPU
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, VABuffer[2]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(model.normals[0]) * model.normals.size(), &model.normals[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, VABuffer[3]); //tell opengl what type of data the buffer is (GL_ARRAY_BUFFER), and pass the data
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, model.indices.size() * sizeof(model.indices[0]), &model.indices[0], GL_STATIC_DRAW); //move the data to the GPU - type of data, size of data, starting address (pointer) of data, where do we store the data on the GPU

	glBindVertexArray(0); // unbind our VAO
}

void MeshManager::ModelLoader(const std::string& filename)
{
	IndexedModel model = OBJModel(filename).ToIndexedModel();
	IntitalizeModel(model);
}

void MeshManager::Draw()
{
	glBindVertexArray(VAObject);

	glDrawElements(GL_TRIANGLES, drawCounter, GL_UNSIGNED_INT, 0);
	//glDrawArrays(GL_TRIANGLES, 0, drawCount);

	glBindVertexArray(0);
}
void MeshManager::updateSphereData(glm::vec3 pos, float radius)
{
	meshSphere.SetPos(pos);
	meshSphere.SetRadius(radius);
}


