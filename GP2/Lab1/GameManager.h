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
#include "CubemapManager.h"


enum class GameState{PLAY, EXIT};

class GameManager
{
public:
	GameManager();
	~GameManager();

	void run();

private:

	void SystemsStart();
	void ProcessInputs();
	void GameActive();
	void Apple();
	void Spinning();
	void Ground();
	void DrawSkyBox();
	void DrawReflection();
	void DrawRefraction();
	void DrawGame();
	void Tree();
	bool IsColliding(MeshManager& mesh, MeshManager& mesh1);
	//void playAudio(unsigned int Source, glm::vec3 pos);

	DisplayGame gameDisplay;
	GameState gameState;
	MeshManager mesh;
	MeshManager mesh1;
	MeshManager mesh2;
	MeshManager mesh3;
	MeshManager mesh4;
	MeshManager mesh5;
	MainCamera mainCamera;
	ShaderManager shader;
	ShaderManager cubemapShader;
	ShaderManager reflectionShader;
	ShaderManager refractionShader;

	AudioManager gameAudio;
	TextureManager texture;
	TextureManager texture1;
	TextureManager grenadeTexture;
	TextureManager texture2;
	CubemapManager cubeMap;

	float counter;
	float collsionCounter;

	float x;
	float preX;

	float y;
	float preY;

	float scale;
	float offset;

};

