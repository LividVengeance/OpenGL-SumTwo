#include "CInput.h"
#include "CObject.h"

class CPlayer
{
public:
	CPlayer(CInput* GameInputs, CObject* playerObj);
	~CPlayer();

	void test();

private:

	CInput* PlayerInputs;
	CObject* playersObject;
};