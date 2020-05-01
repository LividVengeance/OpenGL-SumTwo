#include "CEnemy.h"

CEnemy::CEnemy(CCamera* camera, GLint program)
{
	CObject enemyObj;
	float xSize = 75;
	float ySize = 50;

	// Translation Matrix
	vec3 enemyPosition = vec3(0, 0, 0);
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