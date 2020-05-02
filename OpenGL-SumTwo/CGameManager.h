#pragma once

#include <glew.h>
#include <freeglut.h>
#include <SOIL.h>
#include <fmod.hpp>
#include <iostream>

#include "glm.hpp"
#include "gtc/matrix_transform.hpp"
#include "gtc/type_ptr.hpp"

#include "CAudio.h"
#include "CBackground.h"
#include "CCamera.h"
#include "CEnemy.h"
#include "CInput.h"
#include "CMesh.h"
#include "CPlayer.h"
#include "CShaderLoader.h"
#include "CTextLabel.h"
#include "Utilities.h"


using namespace glm;
using namespace std;

class CGameManager
{
public:
	CGameManager(int argc, char** argv);
	~CGameManager();

	void KeyBoardDown(unsigned char key, int x, int y);
	void KeyBoardUp(unsigned char key, int x, int y);
	void MousePassiveMove(int x, int y);
	void MouseClick(int button, int state, int x, int y);
	void MouseMove(int x, int y);

	void CreateAudioSystem();
	void Update();
	void Render();
	void ManagerMain();

private:
	int gameScore = 0;

	GLuint VBO, EBO, VAO;
	FMOD::System* audioSystem;
	glm::mat4 playerMatModel;
	
	CInput* GameInputs;
	CPlayer* player;
	CCamera* gameCamera;
	CEnemy* enemy;
	CBackground* backgroundImage;

	CTextLabel* scoreLabel;
	CTextLabel* lifeLabel;

	GLfloat currentTime, previousTime, deltaTime;
	GLint program;
};