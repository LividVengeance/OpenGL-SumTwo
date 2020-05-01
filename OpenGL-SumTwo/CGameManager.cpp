#pragma once

#include "CGameManager.h"

CGameManager* globalPointerGM;

void CGameManager::CreateAudioSystem()
{
	/// Creates the audio system
	FMOD_RESULT result;
	result = System_Create(&audioSystem);
	if (result != FMOD_OK)
	{
		std::cout << "Failed to create audioSystem" << endl;
	}
	result = audioSystem->init(100, FMOD_INIT_NORMAL | FMOD_INIT_3D_RIGHTHANDED, 0);
	if (result != FMOD_OK)
	{
		cout << "Failed to initialize the audioSystem" << endl;
	}
}

CGameManager::CGameManager(int argc, char** argv)
{
	globalPointerGM = this;

	// Setup and create at glut controlled window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(50, 50);
	glutInitWindowSize(Utils::SCR_WIDTH, Utils::SCR_HEIGHT);
	glutCreateWindow("OpenGL Summative Two - GD1P04");

	// Sets up all GL function callbacks based on pc hardware
	if (glewInit() != GLEW_OK)
	{
		// If glew fails to setup will throw error message
		std::cout << "Glew Faild to initialize. Now aborting." << std::endl;
		system("pause");
	}

	// Sets the clear colour
	glClearColor(1.0, 0.0, 0.0, 1.0); // Sets to Red

	glCullFace(GL_BACK);
	glFrontFace(GL_CCW);
	glEnable(GL_CULL_FACE);

	program = CShaderLoader::CreateProgram("Resources/Shaders/Basic.vs",
		"Resources/Shaders/Basic.fs");

	// Setup the UI
	scoreLabel = new CTextLabel("Score: 0", "Resources/Fonts/arial.ttf", glm::vec2(10.0f, 570.0f), glm::vec3(0.0f, 1.0f, 0.5f), 0.5f);
	lifeLabel = new CTextLabel("Lives: 5", "Resources/Fonts/arial.ttf", glm::vec2(10.0f, 540.0f), glm::vec3(1.0f, 0.0f, 0.0f), 0.5f);

	// Setup Player
	GameInputs = new CInput();
	playerObj = new CObject;
	player = new CPlayer(GameInputs, playerObj, gameCamera, program);
	
	
	backgroundImage = new CBackground(program, gameCamera);
																															 
	// Create Audio Syetem																									  
	CreateAudioSystem();
	// Creates and plays the background music
	CAudio backingTrack("Resources/Audio/Background.mp3", audioSystem, true);
	backingTrack.PlaySound();

	

	glm::vec3 objPostion = glm::vec3(0.5f, 0.5f, 0.0f);
	glm::mat4 translationMatrix = glm::translate(glm::mat4(), objPostion);

	GLuint translateLoc = glGetUniformLocation(program, "translation");
	glUniformMatrix4fv(translateLoc, 1, GL_FALSE, glm::value_ptr(translationMatrix));
}

CGameManager::~CGameManager()
{
}

void CGameManager::Render()
{
	glClear(GL_COLOR_BUFFER_BIT);

	glUseProgram(program);

	//		Create Camera One		//
	CCamera CamOne(program);
	mat4 view = CamOne.CameraView();

	GLuint viewLoc = glGetUniformLocation(program, "view");
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, value_ptr(view));

	backgroundImage->Render();

	GLint currentTimeLoc = glGetUniformLocation(program, "currentTime");
	glUniform1f(currentTimeLoc, currentTime);

	// Render UI Elements
	scoreLabel->Render();
	lifeLabel->Render();

	glBindVertexArray(0);		// Unbinding VAO
	glUseProgram(0);

	glutSwapBuffers();
}

void CGameManager::Update()
{
	// Update information
	currentTime = glutGet(GLUT_ELAPSED_TIME);	// Get current time
	currentTime = currentTime * 0.001f;			// Converting to time seconds (From miliseconds)
	deltaTime = currentTime - previousTime;	
	previousTime = currentTime;

	// Update Audio System
	audioSystem->update();

	// Updates the score label
	std::string scoreStr = "Score: ";
	scoreStr += std::to_string(gameScore);
	scoreLabel->SetText(scoreStr);
	
	//		Player		//
	glm::mat4 playerTransMat = playerObj->Translation(player->playerPostion);
	float angle = 0.0f;
	glm::mat4 playerRotationMat = playerObj->Rotation(player->playerRotation, angle);
	float scaleAmount = 100.0f;
	glm::mat4 playerScaleMat = playerObj->Scale(player->playerScale, scaleAmount);
	playerMatModel = playerObj->Combine(playerTransMat, playerRotationMat, playerScaleMat);

	GameInputs->ProcessInput();
	player->Update(deltaTime);

	glutPostRedisplay();
}

void CGameManager::KeyBoardDown(unsigned char key, int x, int y)
{
	gameScore++;
	GameInputs->KeyboardDown(key, x, y);
}

void CGameManager::KeyBoardUp(unsigned char key, int x, int y)
{
	GameInputs->KeyboardUp(key, x, y);
}

void CGameManager::MousePassiveMove(int x, int y)
{
	GameInputs->MousePassiveMove(x, y);
}

void CGameManager::MouseClick(int button, int state, int x, int y)
{
	GameInputs->MouseClick(button, state, x, y);
}

void CGameManager::MouseMove(int x, int y)
{
	GameInputs->MouseMove(x, y);
}

void KeyboardDownRedirect(unsigned char key, int x, int y)
{
	globalPointerGM->KeyBoardDown(key, x, y);
}

void KeyboardUpRedirect(unsigned char key, int x, int y)
{
	globalPointerGM->KeyBoardUp(key, x, y);
}

void MousePassiveMoveRedirect(int x, int y)
{
	globalPointerGM->MousePassiveMove(x, y);
}

void MouseClickRedirect(int button, int state, int x, int y)
{
	globalPointerGM->MouseClick(button, state, x, y);
}

void MouseMoveRedirect(int x, int y)
{
	globalPointerGM->MouseMove(x, y);
}

void RenderRedirect()
{
	/// Allows glut to look at func in class
	globalPointerGM->Render();
}

void UpdateRedirect()
{
	/// Allows glut to look at func in class
	globalPointerGM->Update();
}

void CGameManager::ManagerMain()
{
	/// Register callbacks
	glutDisplayFunc(RenderRedirect);
	glutIdleFunc(UpdateRedirect);

	// Updating audio in audioSystem
	audioSystem->update();

	// KeyBoard Inputs
	glutKeyboardFunc(KeyboardDownRedirect);
	glutKeyboardUpFunc(KeyboardUpRedirect);
	
	// Mouse Inputs
	glutMouseFunc(MouseClickRedirect);
	glutMotionFunc(MouseMoveRedirect);
	glutPassiveMotionFunc(MousePassiveMoveRedirect);

	glutMainLoop();
}