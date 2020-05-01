#include "CMesh.h"

CMesh::CMesh(GLint program, CCamera* camera, GLfloat xSize, GLuint ySize, const char *textureLocation, glm::mat4 model)
{
	programMesh = program;
	modelMatrix = model;

	GLfloat vertices[] {
		// Position							// Color						// Texture Coords
		 -0.5f * xSize,    0.5f * ySize,	0.0f,	1.0f, 1.0f,	 1.0f,		0.0f,   0.0f,	// Top Right
		  0.5f * xSize,    0.5f * ySize,	0.0f,	1.0f, 1.0f,	 1.0f,		1.0f,   0.0f,	// Bot Left
		 -0.5f * xSize,   -0.5f * ySize,	0.0f,	1.0f, 1.0f,	 1.0f,		0.0f,   1.0f,	// Top Left
		  0.5f * xSize,   -0.5f * ySize,	0.0f,	1.0f, 1.0f,	 1.0f,		1.0f,   1.0f,	// Bot Right
	};
	GLuint indices[] = {
		0, 1, 2,	// First Triangle
		1, 3, 2,	// Second Triangle
	};

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

	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	// Gen Textures
	int width, height;
	unsigned char* image1 = SOIL_load_image(textureLocation, &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image1);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glGenerateMipmap(GL_TEXTURE_2D);
	SOIL_free_image_data(image1);
	glBindTexture(GL_TEXTURE_2D, 0);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

CMesh::~CMesh()
{
}

void CMesh::Render()
{
	glUseProgram(programMesh);

	glBindVertexArray(VAO);		// Bind VAO

	//		Background		//
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);
	glUniform1i(glGetUniformLocation(programMesh, "tex"), 0);

	GLuint modelLoc = glGetUniformLocation(programMesh, "model");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, value_ptr(modelMatrix));
	glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, 0); // Drawing Background
}