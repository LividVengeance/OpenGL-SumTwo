#pragma once
#include <glew.h>
#include <freeglut.h>
#include <SOIL.h>
#include <iostream>

#include "glm.hpp"
#include "gtc/matrix_transform.hpp"
#include "gtc/type_ptr.hpp"

#include "CCamera.h"
#include "CObject.h"

class CMesh
{
public:
	CMesh(GLint program, CCamera* camera, float xSize, float ySize, const char *textureLocation, CObject object);
	~CMesh();
	void Render();
	void Update();
	CObject meshObject;

	vec3 objPosition;
	vec3 rotationAxis;
	vec3 objScale;
	float scaleAmount;

	GLint programMesh;
	glm::mat4 modelMatrix;

private:
	GLuint VBO;
	GLuint EBO;
	GLuint VAO;
	GLuint texture;
};

