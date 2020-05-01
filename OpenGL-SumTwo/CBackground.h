#pragma once

#include "CObject.h"

class CBackground
{
public:
	CBackground(CObject backgroundObj);
	~CBackground();

	glm::mat4 GetModelMatrix();
	glm::mat4 model;

private:

};

