#include "CEnemyManager.h"

CEnemyManager::CEnemyManager(CCamera* camera, GLint program)
{
	enemyCamera = camera;
	enemyProgram = program;

	int randomX = rand() % Utils::SCR_WIDTH - 400;

	float xSize = 75;
	float ySize = 50;

	const char* fileLocation = "Resources/Textures/Sprite-0004.png";
	enemyMesh = new CMesh(enemyProgram, enemyCamera, xSize, ySize, fileLocation);

	NewEnemy();
}

CEnemyManager::~CEnemyManager()
{
}

void CEnemyManager::Render()
{
	for (int i = 0; i < allEnemies.size(); i++)
	{
		allEnemies[i]->Render();
	}
}

void CEnemyManager::Update(float deltaTime)
{
	for (int i = 0; i < allEnemies.size(); i++)
	{
		allEnemies[i]->Update(deltaTime);
	}
}

void CEnemyManager::NewEnemy()
{
	CEnemy* newEnemy = new CEnemy(enemyCamera, enemyProgram, enemyMesh);
	newEnemy->objPosition = vec3(0.0f, 0.f, 1.0f);
	newEnemy->Update(0.0f);
	allEnemies.push_back(newEnemy);
}