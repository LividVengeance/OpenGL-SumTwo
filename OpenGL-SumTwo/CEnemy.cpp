#include "CEnemy.h"

CEnemy::CEnemy(CCamera* camera, GLint program, CMesh* Mesh)
{
	enemyCamera = camera;
	enemyProgram = program;
	enemyMesh = Mesh;

	int randomX = rand() % Utils::SCR_WIDTH - 400;

	enemyMesh->objPosition.x = randomX;
	enemyMesh->objPosition.y = 400;
}

CEnemy::~CEnemy()
{
}

void CEnemy::Render()
{
	enemyMesh->Render(modelMatrix);
}
 
void CEnemy::Update(float deltaTime)
{ 
	objPosition.y -= 100 * deltaTime;

	glm::mat4 translationMatrix = glm::translate(glm::mat4(), objPosition);
	glm::mat4 rotationMatrix = glm::rotate(glm::mat4(), glm::radians(angle), rotationAxis);
	glm::mat4 scaleMatrix = scale(glm::mat4(), objScale * scaleAmount);

	// Create model matrix to combine them
	modelMatrix = translationMatrix * rotationMatrix * scaleMatrix;
}
