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
	void Spinning();
	void Ground();
	void DrawSkyBox();
	void DrawReflection();
	void DrawRefraction();
	void DrawGame();
	void Tree();
	bool IsColliding(MeshManager& mesh, MeshManager& mesh1);

	DisplayGame gameDisplay;
	GameState gameState;
	MeshManager cube;
	MeshManager apple;
	MeshManager tree;
	MainCamera mainCamera;
	ShaderManager shader;
	ShaderManager cubemapShader;
	ShaderManager reflectionShader;
	ShaderManager refractionShader;

	AudioManager gameAudio;
	TextureManager tarmacTex;
	TextureManager treeTex;
	TextureManager appleTex;
	CubemapManager cubeMap;

	// for object transform
	float counter;
	float collsionCounter;

	// mouse movement
	float x;
	float preX;
	float y;
	float preY;

	// object manipluation
	float scale;
	float offset;
};

