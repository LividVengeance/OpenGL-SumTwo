#include "CBackground.h"

CBackground::CBackground(GLint program, CCamera* camera)
{
	float xSize = Utils::SCR_WIDTH;
	float ySize = Utils::SCR_HEIGHT;

	CObject backgroundObj;
	
	const char* fileLocation = "Resources/Textures/Sprite-0002.png";
	backgroundMesh = new CMesh(program, camera, xSize, ySize, fileLocation, backgroundObj);
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