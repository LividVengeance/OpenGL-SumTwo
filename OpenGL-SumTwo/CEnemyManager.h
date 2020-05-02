#pragma once
#include "CEnemy.h"

class CEnemyManager
{
public:
	CEnemyManager(CCamera* camera, GLint program);
	~CEnemyManager();

	void Render();
	void Update(float deltaTime);
	void NewEnemy();

	CMesh* enemyMesh;
	CCamera* enemyCamera;
	GLint enemyProgram;

	std::vector<CEnemy*> allEnemies;
private:

};

