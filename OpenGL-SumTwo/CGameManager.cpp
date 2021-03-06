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

	// Enabling Culling
	glCullFace(GL_BACK);
	glFrontFace(GL_CCW);
	glEnable(GL_CULL_FACE);

	program = CShaderLoader::CreateProgram("Resources/Shaders/Basic.vs",
		"Resources/Shaders/Basic.fs");

	// Setup the UI
	scoreLabel = new CTextLabel("Score: 0", "Resources/Fonts/arial.ttf", glm::vec2(10.0f, 570.0f), glm::vec3(0.0f, 1.0f, 0.5f), 0.5f);
	lifeLabel = new CTextLabel("Lives: 5", "Resources/Fonts/arial.ttf", glm::vec2(10.0f, 540.0f), glm::vec3(1.0f, 0.0f, 0.0f), 0.5f);
	gameEndLabel = new CTextLabel("You are dead! - ", "Resources/Fonts/arial.ttf", glm::vec2((Utils::SCR_WIDTH/2) - 75, Utils::SCR_HEIGHT/2), glm::vec3(1.0f, 1.0f, 1.5f), 0.5f);
	endPressLabel = new CTextLabel("Press 'SPACE' to start new game", "Resources/Fonts/arial.ttf", glm::vec2((Utils::SCR_WIDTH / 2) - 150, (Utils::SCR_HEIGHT / 2) - 25), glm::vec3(1.0f, 1.0f, 1.5f), 0.5f);

	// Setup Enemy
	enemyManager = new CEnemyManager(gameCamera, program);

	// Setup Player
	GameInputs = new CInput();
	player = new CPlayer(GameInputs, gameCamera, program);
	
	// Setup Background
	backgroundImage = new CBackground(program, gameCamera);
																													 
	// Create Audio Syetem																									  
	CreateAudioSystem();
	// Creates and plays the background music
	CAudio backingTrack("Resources/Audio/Background.mp3", audioSystem, true);
	backingTrack.PlaySound();
}

CGameManager::~CGameManager()
{
}

void CGameManager::Render()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glUseProgram(program);

	// Create Camera One
	CCamera CamOne(program);
	mat4 view = CamOne.CameraView();

	GLuint viewLoc = glGetUniformLocation(program, "view");
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, value_ptr(view));

	backgroundImage->Render();

	GLint currentTimeLoc = glGetUniformLocation(program, "currentTime");
	glUniform1f(currentTimeLoc, currentTime);

	
	if (playersDead)
	{
		gameEndLabel->Render();
		endPressLabel->Render();
	}
	else
	{
		// Render UI Elements
		scoreLabel->Render();
		lifeLabel->Render();

		player->Render();
		enemyManager->Render();
	}

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

	timer += deltaTime;
	// Adds another enemy for every 0.4 seconds
	if (timer > 0.4f)
	{
		gameScore += 10;
		timer = 0.0f;
		enemyManager->NewEnemy();
	}

	if (!playersDead)
	{
		// Updates the score label
		std::string scoreStr = "Score: ";
		scoreStr += std::to_string(gameScore);
		scoreLabel->SetText(scoreStr);

		// Updates the lives label
		std::string livesStr = "Score: ";
		livesStr += std::to_string(player->playerLives);
		lifeLabel->SetText(livesStr);

		// Updates the death label
		std::string deathStr = "You are dead! - ";
		deathStr += std::to_string(gameScore);
		gameEndLabel->SetText(deathStr);

		player->moveInput(deltaTime);
		player->Update(&playersDead);

		enemyManager->Update(deltaTime, player, &playersDead, audioSystem);
	}
	else
	{
		if (GameInputs->getKeyState(' ') == true)
		{
			playersDead = false;
			gameScore = 0;
			player = new CPlayer(GameInputs, gameCamera, program);
			
			
		}
	}

	glutPostRedisplay();
}

void CGameManager::KeyBoardDown(unsigned char key, int x, int y)
{
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