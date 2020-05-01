#include "CEnemy.h"

CEnemy::CEnemy(CCamera* camera, GLint program)
{
	CObject enemyObj;

	float xSize = 75;
	float ySize = 50;

	const char* fileLocation = "Resources/Textures/Sprite-0004.png";
	enemyMesh = new CMesh(program, camera, xSize, ySize, fileLocation, enemyObj);
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
	enemyPosition.y -= 10  * deltaTime;
}