#include "CPlayer.h"

CPlayer::CPlayer(CInput* GameInputs, CCamera* camera, GLint program)
{
	PlayerInputs = GameInputs;

	float xSize = 50;
	float ySize = 50;

	// Translation Matrix
	playerPostion = vec3(0, 0, 0);
	mat4 translationMatrix = playersObject.Translation(playerPostion);
	// Rotation Matrix
	playerRotation = vec3(1.0f, 1.0f, 1.0f);
	mat4 rotationMatrix = playersObject.Rotation(playerRotation, 0.0f); // 0.0f is rotaition angle
	// Scale Matrix
	float scaleAmount = 1.0f;
	playerScale = vec3(1.0f, 1.0f, 1.0f);
	mat4 scaleMatrix = playersObject.Scale(playerScale, scaleAmount);
	// Create model matrix to combine them
	model = translationMatrix * rotationMatrix * scaleMatrix;

	const char* fileLocation = "Resources/Textures/Sprite-0001.png";
	playerMesh = new CMesh(program, camera, xSize, ySize, fileLocation, model);
}

CPlayer::~CPlayer()
{
}

void CPlayer::Update(GLfloat deltaTime)
{
	// Move Right
	if (PlayerInputs->getKeyState('D') == true || PlayerInputs->getKeyState('d') == true)
	{
		playerPostion.x += 200.0f * deltaTime;
	}
	// Move Left
	if (PlayerInputs->getKeyState('A') == true || PlayerInputs->getKeyState('a') == true)
	{
		playerPostion.x -= 200.0f * deltaTime;
	}
	// Move Up
	if (PlayerInputs->getKeyState('W') == true || PlayerInputs->getKeyState('w') == true)
	{
		playerPostion.y += 200.0f * deltaTime;
	}
	// Move Up
	if (PlayerInputs->getKeyState('S') == true || PlayerInputs->getKeyState('s') == true)
	{
		playerPostion.y -= 200.0f * deltaTime;
	}
	// Shoot
	if (PlayerInputs->getKeyState(' ') == true)
	{
		std::cout << "Player Shoot Meme" << std::endl;
	}
}

void CPlayer::Render()
{
	playerMesh->Render();
}