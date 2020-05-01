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

	GLfloat vertices[]{
		// Position				// Color			// Texture Coords
		 0.0f,   0.0f,  0.0f,	1.0f, 1.0f, 1.0f,	0.0f,   0.0f,	// Top Left
		 1.0f,   0.0f,  0.0f,	1.0f, 1.0f, 1.0f,	1.0f,   0.0f,	// Top Right
		 0.0f,   1.0f,  0.0f,	1.0f, 1.0f, 1.0f,	0.0f,   1.0f,	// Bot Left
		 1.0f,   1.0f,  0.0f,	1.0f, 1.0f, 1.0f,	1.0f,   1.0f,	// Bot Right
	};
	GLuint indices[] = {
		0, 1, 2,	// First Triangle
		1, 3, 2,	// Second Triangle
	};
	GLfloat playerVertices[]{
		// Position				// Color			// Texture Coords
		 0.0f,   0.0f,  0.0f,	1.0f, 1.0f, 1.0f,	0.0f,   0.0f,	// Top Left
		 1.0f,   0.0f,  0.0f,	1.0f, 1.0f, 1.0f,	1.0f,   0.0f,	// Top Right
		 0.0f,   1.0f,  0.0f,	1.0f, 1.0f, 1.0f,	0.0f,   1.0f,	// Bot Left
		 1.0f,   1.0f,  0.0f,	1.0f, 1.0f, 1.0f,	1.0f,   1.0f,	// Bot Right
	};
	GLuint playerIndices[] = {
		0, 1, 2,	// First Triangle
		1, 3, 2,	// Second Triangle
	};

	// Setup and create at glut controlled window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(50, 50);
	glutInitWindowSize(Utils::SCR_WIDTH, Utils::SCR_HEIGHT);
	glutCreateWindow("OpenGL Window Title");

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
	player = new CPlayer(GameInputs, playerObj);

	// Create Audio Syetem
	CreateAudioSystem();
	// Creates and plays the background music
	CAudio backingTrack("Resources/Audio/Background.mp3", audioSystem, true);
	backingTrack.PlaySound();

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	//		Draw player		//
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(playerIndices), playerIndices, GL_STATIC_DRAW);
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(playerVertices), playerVertices, GL_STATIC_DRAW);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glVertexAttribPointer(
		0,
		3,
		GL_FLOAT,
		GL_FALSE,
		8 * sizeof(GLfloat),	// Stride of the single vertex (pos + color)
		(GLvoid*)0);			// Offset from beginning of Vertex
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(
		1,
		3,
		GL_FLOAT,
		GL_FALSE,
		8 * sizeof(GLfloat),				// Stride of the single vertex (pos + color)
		(GLvoid*)(3 * sizeof(GLfloat)));	// Offset from beginning of Vertex
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(
		2,
		2,
		GL_FLOAT,
		GL_FALSE,
		8 * sizeof(GLfloat),
		(GLvoid*)(6 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);

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

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);
	glUniform1i(glGetUniformLocation(program, "tex"), 0);

	glBindVertexArray(VAO);		// Bind VAO
	
	//		Ceate Background Image		//
	CObject backgroundObj;
	// Translation Matrix
	vec3 objPosition = vec3(500.0f, 600.0f, 0.0f);
	mat4 translationMatrix = backgroundObj.Translation(objPosition);
	// Rotation Matrix
	vec3 rotationAxis = vec3(0.0f, 0.0f, 1.0f);
	float angle = 180.0f;
	mat4 rotationMatrix = backgroundObj.Rotation(rotationAxis, angle);
	// Scale Matrix
	float scaleAmount = 1000.0f;
	vec3 objScale = vec3(1.0f, 1.0f, 1.0f);
	mat4 scaleMatrix = backgroundObj.Scale(objScale, scaleAmount);
	// Create model matrix to combine them
	mat4 model = backgroundObj.Combine(translationMatrix, rotationMatrix, scaleMatrix);

	GLuint modelLoc = glGetUniformLocation(program, "model");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, value_ptr(model));
	glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, 0); // Drawing Background

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, texture1);
	glUniform1i(glGetUniformLocation(program, "tex"), 0);

	//		Player		//
	vec3 playerObjPos = vec3(500.0f, 600.0f, 0.0f);
	mat4 playerTrans = playerObj->Translation(playerObjPos);
	vec3 playerRotation = vec3(0.0f, 0.0f, 1.0f);
	mat4 playerrotation = playerObj->Rotation(playerRotation, angle);
	vec3 playerObjScale = vec3(1.0f, 1.0f, 1.0f);
	mat4 playerScaleMat = playerObj->Scale(playerObjScale, scaleAmount);
	mat4 playerModel = playerObj->Combine(playerTrans, playerrotation, playerScaleMat);
	GLuint modelLoc1 = glGetUniformLocation(program, "playerModel");
	glUniformMatrix4fv(modelLoc1, 1, GL_FALSE, value_ptr(playerModel));
	glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, 0); 

	//		Create Camera One		//
	CCamera CamOne(program);
	mat4 view = CamOne.CameraView();

	GLuint viewLoc = glGetUniformLocation(program, "view");
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, value_ptr(view));

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

	audioSystem->update();

	// Updates the score
	//std::string scoreStr = "Score: ";
	//scoreStr += std::to_string(Utils::gameScore);
	//std::cout << scoreStr << std::endl;
	//label->SetText(scoreStr);
	
	GameInputs->ProcessInput();
	player->test();

	glutPostRedisplay();
}

GLint CGameManager::GenerateTextures()
{
	// Texture One
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	int width, height;
	unsigned char* image1 = SOIL_load_image("Resources/Textures/frogChair.jpg", &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image1);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glGenerateMipmap(GL_TEXTURE_2D);
	SOIL_free_image_data(image1);
	glBindTexture(GL_TEXTURE_2D, 0);

	// Texture Two
	glGenTextures(1, &texture1);
	glBindTexture(GL_TEXTURE_2D, texture1);

	unsigned char* image = SOIL_load_image("Resources/Textures/catz.jpg", &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glGenerateMipmap(GL_TEXTURE_2D);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 1);


	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	return (0);
}

void CGameManager::KeyBoardDown(unsigned char key, int x, int y)
{
	//Utils::gameScore++;
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

	GenerateTextures();
	glutMainLoop();
}