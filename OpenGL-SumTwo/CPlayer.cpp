#include "CPlayer.h"

CPlayer::CPlayer(CInput* GameInputs, CObject* playerObj, CCamera* camera, GLint program)
{
	PlayerInputs = GameInputs;
	playersObject = playerObj;

	GLfloat Vertices[]{
		// Position				// Color			// Texture Coords
		 0.0f,   0.0f,  0.0f,	1.0f, 1.0f, 1.0f,	0.0f,   0.0f,	// Top Left
		 1.0f,   0.0f,  0.0f,	1.0f, 1.0f, 1.0f,	1.0f,   0.0f,	// Top Right
		 0.0f,   1.0f,  0.0f,	1.0f, 1.0f, 1.0f,	0.0f,   1.0f,	// Bot Left
		 1.0f,   1.0f,  0.0f,	1.0f, 1.0f, 1.0f,	1.0f,   1.0f,	// Bot Right
	};
	GLuint Indices[] = {
		0, 1, 2,	// First Triangle
		1, 3, 2,	// Second Triangle
	};

	playerPostion = vec3(0, 0, 0);
	playerRotation = vec3(1.0f, 1.0f, 1.0f);
	playerScale = vec3(1.0f, 1.0f, 1.0f);
	const char *fileLocation = "Resources/Textures/Sprite-0002.png";
	CMesh playerMesh(CCamera* camera, GLint program, GLfloat vertices, GLuint indices, const char* fileLocation);
}

CPlayer::~CPlayer()
{
}

void CPlayer::Update(GLfloat deltaTime)
{
	// Move Right
	if (PlayerInputs->getKeyState('D') == true || PlayerInputs->getKeyState('d') == true)
	{
		if (!(playerPostion.x > (Utils::SCR_WIDTH / 4)))
		{
			playerPostion.x += 200 * deltaTime;
		}
	}
	// Move Left
	if (PlayerInputs->getKeyState('A') == true || PlayerInputs->getKeyState('a') == true)
	{
		float scrWidth = Utils::SCR_WIDTH;
		if (playerPostion.x > -(scrWidth / 3))
		{
			playerPostion.x -= 200 * deltaTime;
		}
	}
	// Move Up
	if (PlayerInputs->getKeyState('W') == true || PlayerInputs->getKeyState('w') == true)
	{
		if (!(playerPostion.y > (Utils::SCR_HEIGHT / 2)))
		{
			playerPostion.y += 200 * deltaTime;
		}
	}
	// Move Up
	if (PlayerInputs->getKeyState('S') == true || PlayerInputs->getKeyState('s') == true)
	{
		float scrHeight = Utils::SCR_HEIGHT;
		if (playerPostion.y > -(scrHeight / 1.5))
		{
			playerPostion.y -= 200 * deltaTime;
		}
	}
	// Shoot
	if (PlayerInputs->getKeyState(' ') == true)
	{
		std::cout << "Player Shoot Meme" << std::endl;
	}
}