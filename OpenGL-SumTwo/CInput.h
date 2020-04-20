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

private:
	

	// Mosue Inputs
	void MouseClick(int button, int state, int x, int y);

	// KeyBoard Inputs
	void KeyboardDown(unsigned char key, int x, int y);
	void KeyboardUp(unsigned char key, int x, int y);
};

