#include "CInput.h"
#include "CObject.h"

class CPlayer
{
public:
	CPlayer(CInput* GameInputs, CObject* playerObj);
	~CPlayer();

	void InputsFunc();
	void Update();
	void Render();
	vec3 playerPostion;

private:
	CInput* PlayerInputs;
	CObject* playersObject;
};