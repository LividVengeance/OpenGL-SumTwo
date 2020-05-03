#include "CPlayer.h"

CPlayer::CPlayer(CInput* GameInputs, CCamera* camera, GLint program)
{
	PlayerInputs = GameInputs;

	float xSize = 50;
	float ySize = 50;

	const char* fileLocation = "Resources/Textures/PlayerSprite.png";
	playerMesh = new CMesh(program, camera, xSize, ySize, fileLocation);
}

CPlayer::~CPlayer()
{
}

void CPlayer::moveInput(GLfloat deltaTime)
{
	int playerLimitHorzontal = (Utils::SCR_WIDTH / 2) - 25;
	int playerLimitVertical = (Utils::SCR_HEIGHT / 2) - 25;
	// Move Right
	if (PlayerInputs->getKeyState('D') == true || PlayerInputs->getKeyState('d') == true)
	{
		if (!(playerMesh->objPosition.x > playerLimitHorzontal)) // 25 is half player mesh size
		{
			playerMesh->objPosition.x += 200.0f * deltaTime;
		}
	}
	// Move Left
	if (PlayerInputs->getKeyState('A') == true || PlayerInputs->getKeyState('a') == true)
	{
		
		if (!(playerMesh->objPosition.x < -playerLimitHorzontal))
		{
			playerMesh->objPosition.x -= 200.0f * deltaTime;
		}
	}
	// Move Up
	if (PlayerInputs->getKeyState('W') == true || PlayerInputs->getKeyState('w') == true)
	{
		if (!(playerMesh->objPosition.y > playerLimitVertical))
		{
			playerMesh->objPosition.y += 200.0f * deltaTime;
		}
	}
	// Move Up
	if (PlayerInputs->getKeyState('S') == true || PlayerInputs->getKeyState('s') == true)
	{
		if (!(playerMesh->objPosition.y < -playerLimitVertical))
		{
			playerMesh->objPosition.y -= 200.0f * deltaTime;
		}
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

void CPlayer::Update(bool* playersDead)
{
	if (!*playersDead)
	{
		playerMesh->Update();
	}
}