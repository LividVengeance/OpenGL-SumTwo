#pragma once

#include <glew.h>
#include <freeglut.h>
#include <SOIL.h>
#include <fmod.hpp>
#include <iostream>

#include "glm.hpp"
#include "gtc/matrix_transform.hpp"
#include "gtc/type_ptr.hpp"

#include "CCamera.h"
#include "CObject.h"
#include "CShaderLoader.h"


class CAudio
{
public:
	CAudio(const char* fileLocation);
	~CAudio();

	void PlaySound();

private:
	System* audioSystem;
	Sound* newSound;

	const char* fileLocation;
	bool AudioInit();
};

