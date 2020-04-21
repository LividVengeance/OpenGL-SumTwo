#pragma once

#include "CObject.h"

CObject::CObject()
{
	GLfloat vertices[]{
		// Position				// Color			// Texture Coords
		 0.33f,  1.0f,  0.0f,	1.0f, 1.0f, 1.0f,	0.33f,  1.0f,	// Top left
		 0.66f,  1.0f,  0.0f,	1.0f, 1.0f, 1.0f,	0.66f,  1.0f,	// Mid left
		 1.0f,   0.5f,  0.0f,	1.0f, 1.0f, 1.0f,	1.0f,   0.5f,	// Bot left
		 0.66f,  0.0f,  0.0f,	1.0f, 1.0f, 1.0f,	0.66f,  0.0f,	// Top Right
		 0.33f,  0.0f,  0.0f,	1.0f, 1.0f, 1.0f,	0.33f,  0.0f,	// Mid Right
		 0.0f,   0.5f,  0.0f,	1.0f, 1.0f, 1.0f,	0.0f,   0.5f,	// Bot Right
	};
	GLuint indices[] = {
		4, 1, 0,	// First Triangle
		4, 3, 1,	// Second Triangle
		3, 2, 1,	// Third Triangle
		5, 4, 0, 	// Fourth Triangle
	};
}

CObject::~CObject()
{
}

glm::mat4 CObject::Translation(glm::vec3 objPosition)
{
	/// Creates Translation Matrax of Objects Postion
	mat4 translationMatrix = translate(glm::mat4(), objPosition);
	return(translationMatrix);
}

glm::mat4 CObject::Rotation(glm::vec3 rotationAxis, float angle)
{
	/// Creates Rotation Matrix Given Angle and Rotation Axis
	glm::mat4 rotationMatrix = rotate(glm::mat4(), radians(angle), rotationAxis);
	return(rotationMatrix);
}

glm::mat4 CObject::Scale(glm::vec3 objScale, float scaleAmount)
{
	/// Create Scale Matrix of Object
	glm::mat4 scaleMatrix = scale(glm::mat4(), objScale * scaleAmount);
	return(scaleMatrix);
}

glm::mat4 CObject::Combine(glm::mat4 translationMatrix, glm::mat4 rotationMatrix, glm::mat4 scaleMatrix)
{
	// Create model matrix to combine them
	glm::mat4 model = translationMatrix * rotationMatrix * scaleMatrix;
	return(model);
}