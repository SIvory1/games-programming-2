#pragma once
#include <SDL\SDL.h>
#include <GL/glew.h>
#include <SDL/SDL_mixer.h>
#include "DisplayGame.h" 
#include "ShaderManager.h"
#include "MeshManager.h"
#include "TextureManager.h"
#include "transform.h"
#include "AudioManager.h"
#include "GameObject.h"
#include "TextureManager.h"
#include "CollisonDetection.h"
#include "CubemapManager.h"


enum class GameState{PLAY, EXIT};

class GameManager
{
public:
	GameManager();
	~GameManager();

	void run();

private:

	void Fog();
	void SystemsStart();
	void ProcessInputs();
	void GameActive();
	void TransformMesh();
	void TransformMesh1();
	void TransformMesh2();
	void DrawSkyBox();
	void DrawReflection();
	void DrawRefraction();
	void DrawGame();
	void ShootObject();
	bool collision(glm::vec3 m1Pos, float m1Rad, glm::vec3 m2Pos, float m2Rad);
	bool newCol(MeshManager& mesh, MeshManager& mesh1);
	//void playAudio(unsigned int Source, glm::vec3 pos);

	DisplayGame gameDisplay;
	GameState gameState;
	MeshManager mesh;
	MeshManager mesh1;
	MeshManager mesh2;
	MeshManager mesh3;
	MainCamera mainCamera;
	ShaderManager shader;
	ShaderManager cubemapShader;
	ShaderManager reflectionShader;
	ShaderManager refractionShader;

	AudioManager gameAudio;
	TextureManager texture;
	TextureManager texture1;
	CubemapManager cubeMap;
//	CollisonDetection col;

	float counter;
	float inputCounter;

	bool pressedDown;
	
	float deltaX;
	float preDeltaX;

	float deltaY;
	float preDeltaY;

	// objetc manipluation
	float scale;
	float offset;

	float collsionCounter;
	//bool hasCollided;
};

