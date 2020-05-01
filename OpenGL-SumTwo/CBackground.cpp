#include "CBackground.h"

CBackground::CBackground(GLint program, CCamera* camera)
{
	float xSize = Utils::SCR_WIDTH;
	float ySize = Utils::SCR_HEIGHT;

	CObject backgroundObj;
	////		Ceate Background Image		////

	// Translation Matrix
	vec3 objPosition = vec3(0.0f, 0.0f, 1.0f);
	mat4 translationMatrix = backgroundObj.Translation(objPosition);
	// Rotation Matrix
	vec3 rotationAxis = vec3(0.0f, 0.0f, 1.0f);
	mat4 rotationMatrix = backgroundObj.Rotation(rotationAxis, 0.0f); // 0.0f is rotaition angle
	// Scale Matrix
	float scaleAmount = 1.0f;
	vec3 objScale = vec3(1.0f, 1.0f, 1.0f);
	mat4 scaleMatrix = backgroundObj.Scale(objScale, scaleAmount);
	// Create model matrix to combine them
	model = translationMatrix * rotationMatrix * scaleMatrix;

	const char* fileLocation = "Resources/Textures/Sprite-0002.png";
	//CMesh backgroundMesh(GLint program, CCamera* camera, GLfloat vertices[], GLuint indices[], const char* fileLocation, glm::mat4 model);
	
	backgroundMesh = new CMesh(program, camera, xSize, ySize, fileLocation, model);
}

CBackground::~CBackground()
{
	delete backgroundMesh;
}

mat4 CBackground::GetModelMatrix()
{
	return(model);
}

void CBackground::Render()
{
	backgroundMesh->Render();
}