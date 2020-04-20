#include "CInput.h"

CInput::CInput()
{
	
}

CInput::~CInput()
{
}

void CInput::ProcessInput()
{
	if (KeyState['w'] == INPUT_DOWN)
	{
		std::cout << "move object";
	}
}

void CInput::MouseClick(int button, int state, int x, int y)
{
	if (button >= 3)
	{
		return;
	}

	MouseState[button] = ((state == GLUT_DOWN) ? INPUT_DOWN : INPUT_UP);
}

void CInput::KeyboardDown(unsigned char key, int x, int y)
{
	KeyState[key] = INPUT_DOWN;
}

void CInput::KeyboardUp(unsigned char key, int x, int y)
{
	KeyState[key] = INPUT_UP;
}

void MousePassiveMove(int x, int y)
{
	std::cout << "Passive x: " << x << " | y: " << y << std::endl;
}

void MouseMove(int x, int y)
{
	std::cout << "Clicked x: " << x << " | y: " << y << std::endl;
}