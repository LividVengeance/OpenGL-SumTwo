#pragma once
#include "CEnemy.h"
#include "CPlayer.h"
#include "CTextLabel.h"

class CEnemyManager
{
public:
	CEnemyManager(CCamera* camera, GLint program);
	~CEnemyManager();

	void Render();
	void Update(float deltaTime, CPlayer* player, bool* playersDead);
	void NewEnemy();

	CMesh* enemyMesh;
	CCamera* enemyCamera;
	GLint enemyProgram;

	std::vector<CEnemy*> allEnemies;
private:

};

