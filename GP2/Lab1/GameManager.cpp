#include "GameManager.h"
#include "MainCamera.h"
#include <iostream>
#include <string>
#define TICK_INTERVAL 30;


Transform transform;

GameManager::GameManager()
{
	offset = 0.0;
	scale = 1;

	counter = 0;
	gameState = GameState::PLAY;
	DisplayGame* gameDisplay = new DisplayGame(); //new display
	// what is this
    MeshManager* mesh();
	MeshManager* mesh1();

	counter = 1.0f;
	collsionCounter = 1.0f;

	x = 0;
	y = 0;
	preX = 0;
	preY = 0;
}

GameManager::~GameManager()
{
}

void GameManager::run()
{
	SystemsStart();
	GameActive();
}

void GameManager::SystemsStart()
{
	gameDisplay.InitalizeDisplay(); 
	gameAudio.AddAudio("..\\res\\background.wav");
	gameAudio.AddSound("..\\res\\shoot.wav");



	mesh2.ModelLoader("..\\res\\cube.obj");
	mesh4.ModelLoader("..\\res\\WoodenLog_obj.obj");
	mesh5.ModelLoader("..\\res\\Apple_obj.obj");

	// saves loadign from file all over;//
	mesh1 = mesh;
	
	mainCamera.InitializeCamera(glm::vec3(0, 0, -5), glm::radians(mainCamera.fov), (float)gameDisplay.getX()/gameDisplay.getY(), 0.01f, 1000.0f);

	shader.InitalizeShader("..\\res\\shader"); //new shader
	// initalize cubemap shader here as well
	cubemapShader.InitalizeShader("..\\res\\cubemapShader");

	cubeMap.InitalizeCubeMap();

	reflectionShader.InitalizeShader("..\\res\\reflectionShader");
	refractionShader.InitalizeShader("..\\res\\refractionShader");

	cubeMap.CubeVertexArrayObject();

	texture.TextureLoader("..\\res\\TarmacDark_D.jpg"); //load texture
	texture1.TextureLoader("..\\res\\water.jpg"); //load texture
	grenadeTexture.TextureLoader("..\\res\\WoodenLog_Diffuse_8K.jpg");
	texture2.TextureLoader("..\\res\\apple l_Material.003_BaseColor.png");

		gameAudio.PlayAudio();
}

//https://www.libsdl.org/release/SDL-1.2.15/docs/html/guidetimeexamples.html
// used to regulate frame rate???
static Uint32 next_time;

Uint32 time_left(void)
{
	Uint32 now;

	now = SDL_GetTicks();

	if (next_time <= now)
		return 0;
	else
		return next_time - now;
}

void GameManager::GameActive()
{
	next_time = SDL_GetTicks() + TICK_INTERVAL;
	while (gameState != GameState::EXIT)
	{
		ProcessInputs();
		DrawGame();
		IsColliding(mesh, mesh1);
		IsColliding(mesh, mesh5);
		IsColliding(mesh1, mesh5);
		SDL_Delay(time_left());
		next_time += TICK_INTERVAL;

		// locks mouse in window and hide it 
		SDL_SetRelativeMouseMode(SDL_TRUE);
	}
}

// adding cube map, reworking collsions 
void GameManager::ProcessInputs()
{

	SDL_Event event;

	while (SDL_PollEvent(&event)) //get and process events
	{
		switch (event.type)
		{
		case SDL_QUIT:
			gameState = GameState::EXIT;
			break;
		case SDL_MOUSEWHEEL:
		{
			if (event.wheel.y > 0 && mainCamera.fov != 0)			
			{			
				mainCamera.Zoom(-1);
				cout << mainCamera.fov << '\n';
				mainCamera.ChangeFOV(glm::radians(mainCamera.fov), (float)gameDisplay.getX() / gameDisplay.getY(), 0.01f, 1000.0f);
			}
		    if (event.wheel.y < 0)
			{
				mainCamera.Zoom(1);
				cout << mainCamera.fov << '\n';
				mainCamera.ChangeFOV(glm::radians(mainCamera.fov), (float)gameDisplay.getX() / gameDisplay.getY(), 0.01f, 1000.0f);
			}
		}
		case SDL_MOUSEBUTTONDOWN:
		{
			if (event.button.button == SDL_BUTTON_LEFT)
			{
				offset += 1;
			}
			if (event.button.button == SDL_BUTTON_RIGHT)
			{
				offset -= 1;
			}
			break;
		}
		case SDL_KEYDOWN:
			switch (event.key.keysym.sym)
			{
			case SDLK_w:
				mainCamera.MoveForward(1);
				break;
			case SDLK_s:
				mainCamera.MoveForward(-1);
				break;
			case SDLK_d:
				mainCamera.MoveHoriz(1);
				break;
			case SDLK_a:
				mainCamera.MoveHoriz(-1);
				break;
			case SDLK_SPACE:
				mainCamera.MoveVertical(1);
				break;
			case SDLK_LSHIFT:
				mainCamera.MoveVertical(-1);
				break;
			case SDLK_e:
				scale += .1;
				break;
			case SDLK_q:
				if (scale > 0)
				{
					scale -= .1;
				}
				break;
			case SDLK_v:
				mainCamera.InitializeCamera(glm::vec3(0, 0, -5), mainCamera.fov, (float)gameDisplay.getX() / gameDisplay.getY(), 0.01f, 1000.0f);
				break;
			}
		case SDL_MOUSEMOTION:
		{
			// stores the x and y position of screen space
			x = event.motion.x;
			y = event.motion.y;
			// checks to see if the x value has increased or decreases from last pos
			if (x > preX || x >= (gameDisplay.getX()) - 1)
			{
				mainCamera.RotateX(-0.01);
			}
			else if (x < preX || x == 0)
			{
				mainCamera.RotateX(0.01);
			}
			// checks to see if the y value has increased or decreases from last pos
			if (y > preY || preY >= (gameDisplay.getY()) - 1)
			{
				mainCamera.RotateY(0.01);
			}
			if (y < preY || y == 0)
			{
				mainCamera.RotateY(-0.01);
			}
			// gives current pos to variables
			preX = x;
			preY = y;
		}
		}
    }
}

bool GameManager::IsColliding(MeshManager& mesh, MeshManager& mesh1)
{
	// magnitiude clacaultion
	float distance = 
		((mesh1.getSpherePos().x - mesh.getSpherePos().x) * (mesh1.getSpherePos().x - mesh.getSpherePos().x) 
		+ (mesh1.getSpherePos().y - mesh.getSpherePos().y) * (mesh1.getSpherePos().y - mesh.getSpherePos().y) 
		+ (mesh1.getSpherePos().z - mesh.getSpherePos().z) * (mesh1.getSpherePos().z - mesh.getSpherePos().z));
	if (distance * distance < (mesh.getSphereRadius() + mesh1.getSphereRadius()))
	{	
    	collsionCounter *= 0;
		gameAudio.PlaySound(0);
		return true;
	}
		return false;
}


void GameManager::Apple()
{
	transform.SetPos(glm::vec3(offset, -0.5, 0.0));
	transform.SetRot(glm::vec3(0.0, counter * 2, 0.0));
	transform.SetScale(glm::vec3(scale, scale, scale));

	texture2.BindTexture(0);

	shader.Bind();
	shader.UpdateShader(transform, mainCamera);

	mesh5.UpdateColData(*transform.GetPos(), scale);

	mesh5.Draw();
}


void GameManager::Spinning()
{
	transform.SetPos(glm::vec3(-sinf(collsionCounter), -0.5, -sinf(collsionCounter) * 5));
	transform.SetRot(glm::vec3(0.0, 0.0, 0/*counter * 5*/));
	transform.SetScale(glm::vec3(scale, scale, scale));

	texture2.BindTexture(0);

	shader.Bind();
	shader.UpdateShader(transform, mainCamera);

	mesh1.UpdateColData(*transform.GetPos(), scale);
	
	mesh5.Draw();
}

void GameManager::Ground()
{
	transform.SetPos(glm::vec3(10, -4, -15));
	transform.SetScale(glm::vec3(50, 1 ,50));

	texture.BindTexture(0);

	shader.Bind();
	shader.UpdateShader(transform, mainCamera);

	mesh2.UpdateColData(*transform.GetPos(), 1);

	mesh2.Draw();
}

void GameManager::Tree()
{
		transform.SetPos(glm::vec3(5 + offset, 0.0,0));
		transform.SetRot(glm::vec3(0.0, counter * 2, 0));
     	transform.SetScale(glm::vec3(scale, scale, scale));

		grenadeTexture.BindTexture(0);

		shader.Bind();
		shader.UpdateShader(transform, mainCamera);

		mesh.UpdateColData(*transform.GetPos(), scale);

		mesh4.Draw();
}

void GameManager::DrawSkyBox()
{
	transform.SetPos(glm::vec3(0.0, 0.0, 0.0));
	transform.SetRot(glm::vec3(0.0, 0.0, 0.0));
	transform.SetScale(glm::vec3(100, 100, 100));

	cubemapShader.Bind();
	cubemapShader.UpdateCubemap(mainCamera);
	cubeMap.DrawCubemap();
}
void GameManager::DrawRefraction()
{
	transform.SetPos(glm::vec3(2, 0.0, 2));
	transform.SetRot(glm::vec3(0.0, counter * 2, 0));
	transform.SetScale(glm::vec3(1, 1, 1));

	reflectionShader.Bind();
	reflectionShader.UpdateReflections(transform, mainCamera);
	cubeMap.DrawCube();
}
void GameManager::DrawReflection()
{
	transform.SetPos(glm::vec3(4, 0.0, 2));
	transform.SetRot(glm::vec3(0.0, counter , 0));
	transform.SetScale(glm::vec3(1, 1, 1));

	refractionShader.Bind();
	refractionShader.UpdateReflections(transform, mainCamera);
	cubeMap.DrawCube();
}

void GameManager::DrawGame()
{
	gameDisplay.ClearDisplay(0.5, 0.5, 0.5, 1.0);

	Apple();
    Spinning();
	Ground();
	Tree();
	DrawRefraction();
	DrawReflection();
	DrawSkyBox();

	counter = counter + 0.05f;
	collsionCounter = collsionCounter + 0.05f;

	glEnableClientState(GL_COLOR_ARRAY); 
	glEnd();

	gameDisplay.ChangeBuffer();
} 