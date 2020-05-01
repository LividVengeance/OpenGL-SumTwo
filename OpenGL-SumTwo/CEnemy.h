#pragma once
#include "CMesh.h"
#include "CObject.h"

class CEnemy
{
public:
	CEnemy(CCamera* camera, GLint program);
	~CEnemy();

	CMesh* enemyMesh;
	glm::mat4 model;
	CObject enemysObject;

	CMesh* playerMesh;

	void Render();

private:

};