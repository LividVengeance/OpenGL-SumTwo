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
#include "CCamera.h"
#include "CInput.h"
#include "CObject.h"
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
	GLint GenerateTextures();

private:
	GLuint VBO;
	GLuint EBO;
	GLuint VAO;

	GLuint texture;
	GLuint texture1;

	FMOD::System* audioSystem;
	
	CInput* GameInputs;
	CTextLabel* label;

	GLfloat currentTime;
	GLint program;
};