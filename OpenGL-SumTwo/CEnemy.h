#pragma once

#include <stdio.h>      
#include <stdlib.h>     
#include <time.h>       


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
	vec3 enemyPosition;
	float timeDelta;
	CMesh* playerMesh;
	void Update(float deltaTime);
	void Render();

private:

};