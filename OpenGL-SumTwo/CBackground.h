#pragma once

#include "CObject.h"
#include "CMesh.h"

class CBackground
{
public:
	CBackground(GLint program, CCamera* camera);
	~CBackground();

	glm::mat4 GetModelMatrix();
	void Render();
	glm::mat4 model;

	CObject* backgroundObj;
	CMesh* backgroundMesh;

private:

};

