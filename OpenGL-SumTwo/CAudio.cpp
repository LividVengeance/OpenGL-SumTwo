#include "CAudio.h"

CAudio::CAudio(const char* givenFileLocation)
{
	AudioInit();
	fileLocation = givenFileLocation;
	
	FMOD_RESULT result;
	result = audioSystem->createSound(fileLocation, FMOD_DEFAULT, 0, &newSound);
	if (result != FMOD_OK)
	{
		cout << "Failed to create sound from file location: " << fileLocation << endl;
	}
}

CAudio::~CAudio()
{
	newSound->release();
}

bool CAudio::AudioInit()
{
	FMOD_RESULT result;
	result = System_Create(&audioSystem);
	if (result != FMOD_OK)
	{
		return(false);
	}

	result = audioSystem->init(100, FMOD_INIT_NORMAL | FMOD_INIT_3D_RIGHTHANDED, 0);
	if (result != FMOD_OK)
	{
		return(false);
	}
	return(true);
}

void CAudio::PlaySound()
{
	audioSystem->playSound(newSound, 0, false, 0);
}
