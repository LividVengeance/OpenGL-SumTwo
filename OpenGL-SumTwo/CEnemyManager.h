#pragma once
#include "CEnemy.h"
#include "CPlayer.h"
#include "CTextLabel.h"
#include "CAudio.h"

class CEnemyManager
{
public:
	CEnemyManager(CCamera* camera, GLint program);
	~CEnemyManager();

	void Render();
	void Update(float deltaTime, CPlayer* player, bool* playersDead, FMOD::System* audioSystem);
	void NewEnemy();

	CMesh* enemyMesh;
	CCamera* enemyCamera;
	GLint enemyProgram;

	std::vector<CEnemy*> allEnemies;
private:

};

