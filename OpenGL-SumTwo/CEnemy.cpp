#include "CEnemy.h"

CEnemy::CEnemy(CCamera* camera, GLint program)
{
	enemyCamera = camera;
	enemyProgram = program;

	int randomX = rand() % Utils::SCR_WIDTH - 400;

	float xSize = 75;
	float ySize = 50;

	const char* fileLocation = "Resources/Textures/Sprite-0004.png";
	enemyMesh = new CMesh(enemyProgram, enemyCamera, xSize, ySize, fileLocation);
	enemyMesh->objPosition.x = randomX;
	enemyMesh->objPosition.y = 400;
}

CEnemy::~CEnemy()
{
}

void CEnemy::Render()
{
	enemyMesh->Render();
}
 
void CEnemy::Update(float deltaTime)
{ 
	enemyMesh->objPosition.y -= 100  * deltaTime;
	enemyMesh->Update();
}

void CEnemy::Spawn()
{
	std::vector<CEnemy> allEnemies;
	
}