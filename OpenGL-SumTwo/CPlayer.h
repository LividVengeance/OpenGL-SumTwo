#include "CInput.h"
#include "CMesh.h"

class CPlayer
{
public:
	CPlayer(CInput* GameInputs, CCamera* camera, GLint program);
	~CPlayer();

	void moveInput(GLfloat deltaTime);

	void Render();
	void Update();

	vec3 playerPostion;
	vec3 playerRotation;
	vec3 playerScale;

	CMesh* playerMesh;
	glm::mat4 model;
private:
	CInput* PlayerInputs;
	
};