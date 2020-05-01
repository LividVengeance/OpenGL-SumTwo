#include "CInput.h"
#include "CMesh.h"
#include "CObject.h"

class CPlayer
{
public:
	CPlayer(CInput* GameInputs, CObject* playerObj, CCamera* camera, GLint program);
	~CPlayer();

	void Update(GLfloat deltaTime);

	vec3 playerPostion;
	vec3 playerRotation;
	vec3 playerScale;

private:
	CInput* PlayerInputs;
	CObject* playersObject;
};