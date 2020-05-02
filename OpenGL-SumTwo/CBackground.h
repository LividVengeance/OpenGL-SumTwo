#pragma once
#include "CMesh.h"

class CBackground
{
public:
	CBackground(GLint program, CCamera* camera);
	~CBackground();

	glm::mat4 GetModelMatrix();
	void Render();
	glm::mat4 model;

	CMesh* backgroundMesh;

private:

};

