#include "CEnemy.h"

CEnemy::CEnemy(CCamera* camera, GLint program)
{
	srand(time(NULL));

	CObject enemyObj;
	float xSize = 75;
	float ySize = 50;

	int randomX = rand() % Utils::SCR_WIDTH;
	// Translation Matrix
	enemyPosition = vec3(randomX, 0, 0);

	mat4 translationMatrix = enemyObj.Translation(enemyPosition);
	// Rotation Matrix
	vec3 enemyRotation = vec3(1.0f, 1.0f, 1.0f);
	mat4 rotationMatrix = enemyObj.Rotation(enemyRotation, 0.0f); // 0.0f is rotaition angle
	// Scale Matrix
	float scaleAmount = 1.0f;
	vec3 enemyScale = vec3(1.0f, 1.0f, 1.0f);
	mat4 scaleMatrix = enemyObj.Scale(enemyScale, scaleAmount);
	// Create model matrix to combine them
	model = translationMatrix * rotationMatrix * scaleMatrix;

	const char* fileLocation = "Resources/Textures/Sprite-0004.png";
	enemyMesh = new CMesh(program, camera, xSize, ySize, fileLocation, model);
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