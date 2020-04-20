#include "CAudio.h"

CAudio::CAudio(const char* givenFileLocation, FMOD::System* audioSystem)
{
	classAudio = audioSystem;
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
	//newSound->release();
}


void CAudio::PlaySound()
{
	classAudio->playSound(newSound, 0, false, 0);
}