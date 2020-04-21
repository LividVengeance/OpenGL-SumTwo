#include "CTextLabel.h"

CTextLabel::CTextLabel(	std::string text,
						std::string font,
						glm::vec2 pos,
						glm::vec3 colour = glm::vec3(1.0f, 1.0f, 1.0f),
						float scale = 1.0f)
{
	text = newText;
	SetColour(colour);
	SetScale(scale);
	SetPosition(pos);

	GLfloat halfWidth = (GLfloat)Utilities::SCR_WIDTH * 0.5;
	GLfloat halfHeight = (GLfloat)Utilities::SCR_HEIGHT * 0.5;
	proj = glm::ortho(-halfWidth, halfWidth, -halfHeight, halfHeight);
	program = CShaderLoader::GetInstance()->CreateProgram("Text.vs", "Text.fs");

	FT_Library ft;
	FT_Face face;

	// Initiate the font Lib
	if (FT_Init_FreeType(&ft) != 0)
	{
		std::cout << "ERROR - FREETYPE: Could not init FreeType Libaray" << std::endl;
	}

	// Load dont as face
	if (FT_New_Face(ft, newFont.c_str(), 0, &face) != 0)
	{
		std::cout << "ERROR - FREETYPE: Faild to load font" << std::endl;
	}

	FT_Set_Pixel_Sizes(face, 0, 48);		// Set size to load glyph as
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1); // Disavle byte-alignment restriction

	// Load the first 128 characters of the ASCII set
	for (GLubyte character = 0; character < 128; character++)
	{
		// Load the character glyph into face
		if (FT_Load_Char(face, character, FT_LOAD_RENDER))
		{
			std::cout << "ERROR - FREETYPE: Failded to load glyph" << std::endl;
			continue;
		}

		GLuint texture = GenerateTexture(face); // Generate a texture for each char (glyph)

		// Now to store character for later use
		FontChar fontChar = { texture,
		glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
		glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
		(GLfloat)face->glyph->advance.x
		};
		Characters.insert(std::pair<GLchar, FontChar>(character, fontChar));
	}

	// Destroy FreeType objects once we are finished
	FT_Done_Face(face);
	FT_Done_FreeType(ft);

	// Configure VAO/VBO for texture quads
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 6 * 4, NULL, GL_DYNAMIC_DRAW);

	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), 0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	// Enable blending
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

CTextLabel::~CTextLabel()

{
}

void CTextLabel::Render()
{
	// Interate through the Characters
	glm::vec2 textPos = position;
	for (std::string::const_iterator character = text.begin(); character != text.end(); character++)
	{
		FontChar fontChar = Characters[*character];
		GLfloat xpos = textPos.x + fontChar.Bearing.x * scale;
		GLfloat ypos = textPos.y - (fontChar.Size.y - fontChar.Bearing.y) * scale;
		GLfloat charWidth = fontChar.Size.x * scale;
		GLfloat charHeight = fontChar.Size.y * scale;

		// Update VBO for each character
		GLfloat vertices[6][4] = {
			{xpos, ypos + charHeight, 0.0, 0.0}, {xpos, ypos, 0.0, 1.0}, {xpos + charWidth, ypos, 1.0, 1.0},
			{xpos, ypos + charHeight, 0.0, 0.0}, {xpos + charWidth, ypos, 1.0, 1.0}, {xpos + charWidth, ypos + charHeight, 1.0, 0.0},
		};
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);

		// Render the glyph texture over the quad
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, fontChar.TextureID);
		glUniform1i(glGetUniformLocation(program, "tex"), 0);
		glDrawArrays(GL_TRIANGLES, 0, 6);

		textPos.x += (fontChar.Advance >> 6)* scale; // Advance cursors for the next glyph

		// Unbind rendering data used and blending
		glUseProgram(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
		glBindTexture(GL_TEXTURE_2D, 0);

		glDisable(GL_CULL_FACE);
		glDisable(GL_BLEND);
	}
}

GLuint CTextLabel::GenerateTexture(FT_Face face)
{
	GLuint texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	glTexImage2D(	GL_TEXTURE_2D, 
					0, GL_RED, 
					face->glyph->bitmap.width, 
					face->glyph->bitmap.rows, 
					0, 
					GL_RED, GL_UNSIGNED_BYTE, 
					face->glyph->bitmap.buffer);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	return(texture);
}
