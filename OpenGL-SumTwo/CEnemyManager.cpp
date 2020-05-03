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

void CEnemyManager::Update(float deltaTime, CPlayer* player, bool* playersDead)
{
	// Half the screen height plus half CEnemy sprite height 
	int enemyLimit = (Utils::SCR_HEIGHT / 2) + 25;

	for (int i = 0; i < allEnemies.size(); i++)
	{
		// CEnemy outside screen space
		if (allEnemies[i]->objPosition.y < -enemyLimit)
		{
			// Deletes CEnemy if out of screen space
			delete allEnemies[i];
			allEnemies.erase(allEnemies.begin() + i);
			i--;
		}



		if (!*playersDead)
		{
			// Collision check CPlayer with CEnemy
			if (allEnemies[i]->objPosition.x + 75 > player->playerMesh->objPosition.x&&
				allEnemies[i]->objPosition.x		< player->playerMesh->objPosition.x + 50 &&
				allEnemies[i]->objPosition.y + 50	> player->playerMesh->objPosition.y&&
				allEnemies[i]->objPosition.y < player->playerMesh->objPosition.y + 50)
			{
				player->playerLives--;
				if (player->playerLives <= 0)
				{
					*playersDead = true;
					delete player;
				}
				// Deletes CEnemy on collision
				delete allEnemies[i];
				allEnemies.erase(allEnemies.begin() + i);
				i--;
			}
			else
			{
				// Updates all CEnemys positions
				allEnemies[i]->Update(deltaTime);
			}
		}		
	}
}

void CEnemyManager::NewEnemy()
{
	CEnemy* newEnemy = new CEnemy(enemyCamera, enemyProgram, enemyMesh);
	int randomX = rand() % Utils::SCR_WIDTH - 400;
	newEnemy->objPosition = vec3(randomX, 400.f, 1.0f);

	newEnemy->Update(0.0f);
	allEnemies.push_back(newEnemy);
}