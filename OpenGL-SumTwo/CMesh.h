#pragma once
#include <glew.h>
#include <freeglut.h>
#include <SOIL.h>
#include <iostream>

#include "glm.hpp"
#include "gtc/matrix_transform.hpp"
#include "gtc/type_ptr.hpp"

#include "CCamera.h"

class CMesh
{
public:
	CMesh(GLint program, CCamera* camera, float xSize, float ySize, const char *textureLocation, glm::mat4 model);
	~CMesh();
	void Render();

	GLint programMesh;
	glm::mat4 modelMatrix;

private:
	GLuint VBO;
	GLuint EBO;
	GLuint VAO;
	GLuint texture;
};

