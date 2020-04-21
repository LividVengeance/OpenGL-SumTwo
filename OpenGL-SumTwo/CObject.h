#pragma once

#include <glew.h>
#include <freeglut.h>
#include <SOIL.h>
#include <iostream>

#include "glm.hpp"
#include "gtc/matrix_transform.hpp"
#include "gtc/type_ptr.hpp"

#include "CCamera.h"

class CObject
{
public:
	CObject();
	~CObject();

	glm::mat4 Translation(glm::vec3 objPosition);
	glm::mat4 Rotation(glm::vec3 rotationAxis, float angle);
	glm::mat4 Scale(glm::vec3 objScale, float scaleAmount);
	glm::mat4 Combine(glm::mat4 translationMatrix, glm::mat4 rotationMatrix, glm::mat4 scaleMatrix);

private:

};