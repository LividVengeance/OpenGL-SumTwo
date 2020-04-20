#pragma once
#include <glew.h>
#include <freeglut.h>
#include <SOIL.h>
#include <fmod.hpp>
#include <iostream>

#include "glm.hpp"
#include "gtc/matrix_transform.hpp"
#include "gtc/type_ptr.hpp"


class CInput
{
public:
	CInput();
	~CInput();

	enum InputState
	{
		INPUT_UP,
		INPUT_DOWN,
		INPUT_UP_FIRST,
		INPUT_DOWN_FIRST,
	};

	InputState KeyState[255];
	InputState MouseState[3];

	void ProcessInput();

	// KeyBoard Inputs
	void KeyboardDown(unsigned char key, int x, int y);
	void KeyboardUp(unsigned char key, int x, int y);

	// Mosue Inputs
	void MousePassiveMove(int x, int y);
	void MouseClick(int button, int state, int x, int y);
	void MouseMove(int x, int y);
private:
	

};

