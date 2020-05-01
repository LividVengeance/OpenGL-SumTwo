#include "CEnemy.h"

CEnemy::CEnemy(CCamera* camera, GLint program)
{
	CObject enemyObj;

	srand(time(NULL));
	
	int randomX = rand() % Utils::SCR_WIDTH;

	float xSize = 75;
	float ySize = 50;

	const char* fileLocation = "Resources/Textures/Sprite-0004.png";
	enemyMesh = new CMesh(program, camera, xSize, ySize, fileLocation, enemyObj);
	enemyMesh->objPosition.x = randomX;
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