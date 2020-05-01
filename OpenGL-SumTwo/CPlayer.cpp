#include "CPlayer.h"

CPlayer::CPlayer(CInput* GameInputs, CObject* playerObj)
{
	PlayerInputs = GameInputs;
	playersObject = playerObj;
}

CPlayer::~CPlayer()
{
}

void CPlayer::test()
{
	// Move Right
	if (PlayerInputs->getKeyState('D') == true || PlayerInputs->getKeyState('d') == true)
	{
		std::cout << "Player Move Right" << std::endl;
	}
	// Move Left
	if (PlayerInputs->getKeyState('A') == true || PlayerInputs->getKeyState('a') == true)
	{
		std::cout << "Player Move Left" << std::endl;
	}
	// Jump
	if (PlayerInputs->getKeyState(' ') == true)
	{
		std::cout << "Player Jump" << std::endl;
	}
}