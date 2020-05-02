#pragma once

#include <stdio.h>      
#include <stdlib.h>     
#include <time.h>     
#include <vector>

#include "CMesh.h"

class CEnemy
{
public:
	CEnemy(CCamera* camera, GLint program);
	~CEnemy();

	void Update(float deltaTime);
	void Render();
	void Spawn();

	float timeDelta;

	CMesh* enemyMesh;
	vec3 enemyPosition;
	glm::mat4 model;

	CCamera* enemyCamera;
	GLint enemyProgram;

private:
};