#include "CInput.h"
#include "CMesh.h"
#include "CObject.h"

class CPlayer
{
public:
	CPlayer(CInput* GameInputs, CCamera* camera, GLint program);
	~CPlayer();

	void Update(GLfloat deltaTime);

	void Render();

	vec3 playerPostion;
	vec3 playerRotation;
	vec3 playerScale;

	CMesh* playerMesh;
	glm::mat4 model;
	CObject playersObject;
private:
	CInput* PlayerInputs;
	
};