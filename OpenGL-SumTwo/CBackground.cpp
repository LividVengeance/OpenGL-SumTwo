#include "CBackground.h"

CBackground::CBackground(CObject backgroundObj)
{
	////		Ceate Background Image		//

	// Translation Matrix
	vec3 objPosition = vec3(500.0f, 600.0f, 0.0f);
	mat4 translationMatrix = backgroundObj.Translation(objPosition);
	// Rotation Matrix
	vec3 rotationAxis = vec3(0.0f, 0.0f, 1.0f);
	float angle = 180.0f;
	mat4 rotationMatrix = backgroundObj.Rotation(rotationAxis, angle);
	// Scale Matrix
	float scaleAmount = 1000.0f;
	vec3 objScale = vec3(1.0f, 1.0f, 1.0f);
	mat4 scaleMatrix = backgroundObj.Scale(objScale, scaleAmount);
	// Create model matrix to combine them
	model = backgroundObj.Combine(translationMatrix, rotationMatrix, scaleMatrix);
}

CBackground::~CBackground()
{
}

mat4 CBackground::GetModelMatrix()
{
	return(model);
}