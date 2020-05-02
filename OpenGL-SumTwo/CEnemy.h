#pragma once

#include <stdio.h>      
#include <stdlib.h>     
#include <time.h>     
#include <vector>

#include "CMesh.h"

class CEnemy
{
public:
	CEnemy(CCamera* camera, GLint program, CMesh* Mesh);
	~CEnemy();

	void Update(float deltaTime);
	void Render();

	float timeDelta;

	CMesh* enemyMesh;
	//vec3 enemyPosition;
	glm::mat4 model;

	vec3 objPosition;
	vec3 rotationAxis = vec3(1.0f, 1.f, 1.0f);;
	vec3 objScale = vec3(1.0f, 1.f, 1.0f);;
	float scaleAmount = 1;
	float angle;
	glm::mat4 modelMatrix;



	CCamera* enemyCamera;
	GLint enemyProgram;

private:
};