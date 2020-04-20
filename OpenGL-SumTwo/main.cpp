#pragma once

#include <glew.h>
#include <freeglut.h>
#include <SOIL.h>
#include <iostream>

#include "glm.hpp"
#include "gtc/matrix_transform.hpp"
#include "gtc/type_ptr.hpp"

#include "CAudio.h"
#include "CCamera.h"
#include "CGameManager.h"
#include "CInput.h"
#include "CObject.h"
#include "CShaderLoader.h"


int main(int argc, char** argv)
{
	CGameManager mainGameManager(argc, argv);
	mainGameManager.ManagerMain();

	return(0);
}