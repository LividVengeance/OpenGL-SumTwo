#include "CPlayer.h"

CPlayer::CPlayer(CInput* GameInputs, CCamera* camera, GLint program)
{
	PlayerInputs = GameInputs;

	float xSize = 50;
	float ySize = 50;

	const char* fileLocation = "Resources/Textures/Sprite-0001.png";
	playerMesh = new CMesh(program, camera, xSize, ySize, fileLocation);
}

CPlayer::~CPlayer()
{
}

void CPlayer::moveInput(GLfloat deltaTime)
{
	// Move Right
	if (PlayerInputs->getKeyState('D') == true || PlayerInputs->getKeyState('d') == true)
	{
		playerMesh->objPosition.x += 200.0f * deltaTime;
	}
	// Move Left
	if (PlayerInputs->getKeyState('A') == true || PlayerInputs->getKeyState('a') == true)
	{
		playerMesh->objPosition.x -= 200.0f * deltaTime;
	}
	// Move Up
	if (PlayerInputs->getKeyState('W') == true || PlayerInputs->getKeyState('w') == true)
	{
		playerMesh->objPosition.y += 200.0f * deltaTime;
	}
	// Move Up
	if (PlayerInputs->getKeyState('S') == true || PlayerInputs->getKeyState('s') == true)
	{
		playerMesh->objPosition.y -= 200.0f * deltaTime;
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

void CPlayer::Update()
{
	playerMesh->Update();
}